#include "wldc_def.h"

typedef enum mem_type {
    mem_type_unknown = 0,
    mem_type_non_specific,
    mem_type_number,
    mem_type_string,
    mem_type_char,
    mem_type_struct,
    mem_type_array,
    mem_type_vector,

    mem_type_max_types
} mem_type;

WLDC_API void mem_system_init();

WLDC_API void mem_system_shutdown();

WLDC_API void* wldc_malloc(u64 size, mem_type type);

WLDC_API void wldc_free(void* block, u64 size, mem_type type);

WLDC_API void* wldc_zero_mem(void* block, u64 size);

WLDC_API void* wldc_copy_mem(void* dst, void* src, u64 size);

WLDC_API void* wldc_set_mem(void* dst, i32 value, u64 size);

WLDC_API char* get_mem_stats_str();