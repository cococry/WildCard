#pragma once

#include "internal/wldc_def.h"

#include <GLFW/glfw3.h>

WLDC_API void mouse_io_init();

WLDC_API void mouse_io_shudown();

void mouse_cursor_pos_callback(GLFWwindow* window, f64 xpos, f64 ypos);

void mouse_button_callback(GLFWwindow* window, i32 button, i32 action, i32 mods);

void mouse_wheel_callback(GLFWwindow* window, f64 delta_x, f64 delta_y);

WLDC_API f64 mouse_x_pos();

WLDC_API f64 mouse_y_pos();

WLDC_API f64 mouse_x_pos_delta();

WLDC_API f64 mouse_y_pos_delta();

WLDC_API bool8 is_mouse_button_down(i32 button);

WLDC_API bool8 is_mouse_button_changed(i32 button);

WLDC_API bool8 is_moused_button_released(i32 button);

WLDC_API bool8 is_mouse_button_pressed(i32 button);
