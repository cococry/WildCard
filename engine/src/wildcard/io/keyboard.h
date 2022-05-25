#pragma once

#include "internal/wldc_def.h"

#include <GLFW/glfw3.h>

WLDC_API void keyboard_io_init();

WLDC_API void keyboard_io_shutdown();

void keyboard_callback(GLFWwindow* window, i32 key, i32 scancode, i32 action, i32 mods);

WLDC_API bool8 is_key_down(i32 key);

WLDC_API bool8 is_key_changed(i32 key);

WLDC_API bool8 is_key_released(i32 key);

WLDC_API bool8 is_key_typed(i32 key);