#pragma once

#include "internal/wldc_def.h"

#include "buffers.h"

#include <glad/glad.h>

typedef struct vertex_array {
    u32 gl_id;
    index_buffer ib;
} vertex_array;

WLDC_API vertex_array create_vertex_array();

WLDC_API void bind_vertex_array(vertex_array* va);

WLDC_API void unbind_vertex_array(vertex_array* va);

WLDC_API void delete_vertex_array(vertex_array* va);

WLDC_API void set_vertex_buffer_layout_attribute(u32 index, i32 count, u64 stride, const void* offset, bool8 normalzied, GLenum type);

WLDC_API void vertex_array_set_index_buffer(vertex_array* va, index_buffer* ib);