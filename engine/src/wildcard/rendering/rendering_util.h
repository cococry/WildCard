#pragma once

#include "internal/wldc_def.h"

#include "vertex_array.h"

void rendering_init();

WLDC_API void resize_viewport(u32 x, u32 y);

WLDC_API void draw_indexed_vertex_array(vertex_array* va);

WLDC_API void draw_indexed(u32 count);