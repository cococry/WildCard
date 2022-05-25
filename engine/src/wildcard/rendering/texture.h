#pragma once

#include "internal/wldc_def.h"

typedef struct texture {
    u32 gl_id;
    i32 width, height, number_of_channels;
} texture;

WLDC_API texture create_texture(const char* filepath, bool8 flipped);

WLDC_API void bind_texture(texture* tex);

WLDC_API void active_texture_slot(i32 slot);

WLDC_API void unbind_texture(texture* tex);

WLDC_API void delete_texture(texture* tex);