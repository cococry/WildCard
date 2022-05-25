#pragma once

#include "internal/wldc_def.h"

#include <GLFW/glfw3.h>

typedef struct wldc_window_props {
    i32 width, height;
    const char* title;
} wldc_window_props;

typedef struct wldc_window {
    GLFWwindow* glfw_instance;
    wldc_window_props props;
} wldc_window;

WLDC_API void windowing_init();

WLDC_API void windowing_shutdown();

WLDC_API wldc_window
window_create(u32 width, u32 height, const char* title);

WLDC_API void window_delete(wldc_window* window);

WLDC_API void window_update(wldc_window* window);

WLDC_API bool8 window_is_open(wldc_window* window);
