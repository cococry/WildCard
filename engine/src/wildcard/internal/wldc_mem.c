#include "core/logging.h"
#include "wldc_mem.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char* mem_type_str[mem_type_max_types] = {
    "unknown",
    "non_specific",
    "number",
    "string",
    "char",
    "struct",
    "array"};

struct mem_stats {
    u64 mem_allocated_count;
    u64 categoriesed_allocations[mem_type_max_types];
};

static struct mem_stats s_stats;

void mem_system_init() {
    memset(&s_stats, 0, sizeof(s_stats));
}
void mem_system_shutdown() {
}
void* wldc_malloc(u64 size, mem_type type) {
    if (type == mem_type_unknown) {
        WLDC_WARN("Allocated memory with unknown memory %s", "type");
    }

    s_stats.mem_allocated_count += size;
    s_stats.categoriesed_allocations[type] += size;

    void* block = malloc(size);
    memset(block, 0, size);

    return block;
}
void wldc_free(void* block, u64 size, mem_type type) {
    if (type == mem_type_unknown) {
        WLDC_WARN("wldc_free was called with unknown memory %s", "type");
    }

    s_stats.mem_allocated_count -= size;
    s_stats.categoriesed_allocations[type] -= size;

    free(block);
}
void* wldc_zero_mem(void* block, u64 size) {
    return memset(block, 0, size);
}
void* wldc_copy_mem(void* dst, void* src, u64 size) {
    return memcpy(dst, src, size);
}
void* wldc_set_mem(void* dst, i32 value, u64 size) {
    return memset(dst, value, size);
}
char* get_mem_stats_str() {
    char buff[2560];

    const u64 gb = 1024 * 1024 * 1024;
    const u64 mb = 1024 * 1024;
    const u64 kb = 1024;

    u64 offset = strlen(buff);
    for (u32 i = 0; i < mem_type_max_types; i++) {
        char byteLabel[4] = "-B";
        float size = 0.0f;
        if (s_stats.categoriesed_allocations[i] >= gb) {
            byteLabel[0] = 'g';
            size = (s_stats.categoriesed_allocations[i] / (float)gb);
        } else if (s_stats.categoriesed_allocations[i] >= mb) {
            byteLabel[0] = 'm';
            size = (s_stats.categoriesed_allocations[i] / (float)mb);
        } else if (s_stats.categoriesed_allocations[i] >= mb) {
            byteLabel[0] = 'k';
            size = (s_stats.categoriesed_allocations[i] / (float)kb);
        } else {
            byteLabel[0] = 'B';
            byteLabel[1] = 0;
            size = (float)s_stats.categoriesed_allocations[i];
        }

        i32 str_length = snprintf(buff + offset, 16000, "  %s:\t\t%.2f%s\n", mem_type_str[i], size, byteLabel);
        offset += str_length;
    }

    char* o_str = _strdup(buff);

    return o_str;
}