#pragma once

#include "internal/wldc_def.h"

typedef struct vertex_buffer {
    u32 gl_id;
} vertex_buffer;

typedef struct index_buffer {
    u32 gl_id;
    u32 count;
} index_buffer;

WLDC_API vertex_buffer
create_vertex_buffer(const void* data, u64 size);

WLDC_API vertex_buffer create_vertex_buffer_no_data(u64 size);

WLDC_API void set_vertex_buffer_data(vertex_buffer* buffer, const void* data, u64 size);

WLDC_API void bind_vertex_buffer(vertex_buffer* buffer);

WLDC_API void unbind_vertex_buffer(vertex_buffer* buffer);

WLDC_API void delete_vertex_buffer(vertex_buffer* buffer);

WLDC_API index_buffer create_index_buffer(u32* data, u32 count);

WLDC_API index_buffer create_index_buffer_no_data(u64 count);

WLDC_API void set_index_buffer_data(index_buffer* buffer, u32* data, u32 count);

WLDC_API void bind_index_buffer(index_buffer* buffer);

WLDC_API void unbind_index_buffer(index_buffer* buffer);

WLDC_API void delete_index_buffer(index_buffer* buffer);
