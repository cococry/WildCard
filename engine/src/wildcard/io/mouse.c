#include "mouse.h"

#include "internal/wldc_mem.h"

struct mouse_state {
    f64 x_pos;
    f64 y_pos;
    f64 last_x_pos;
    f64 last_y_pos;
    f64 x_pos_delta;
    f64 y_pos_delta;
    f64 x_scroll_delta;
    f64 y_scroll_delta;

    bool8 first_mouse;

    bool8* buttons;
    bool8* buttons_changed;
};

static struct mouse_state s_state;

void mouse_io_init() {
    wldc_zero_mem(&s_state, sizeof(s_state));
    s_state.first_mouse = TRUE;
    s_state.buttons = wldc_malloc(sizeof(bool8) * GLFW_KEY_LAST, mem_type_array);
    s_state.buttons_changed = wldc_malloc(sizeof(bool8) * GLFW_KEY_LAST, mem_type_array);
}

void mouse_io_shudown() {
    wldc_zero_mem(&s_state, sizeof(s_state));
}

void mouse_cursor_pos_callback(GLFWwindow* window, f64 xpos, f64 ypos) {
    s_state.x_pos = xpos;
    s_state.y_pos = ypos;

    if (s_state.first_mouse) {
        s_state.last_x_pos = xpos;
        s_state.last_y_pos = ypos;
        s_state.first_mouse = FALSE;
    }

    s_state.x_pos_delta = xpos - s_state.last_x_pos;
    s_state.y_pos_delta = ypos = s_state.last_y_pos;
    s_state.last_x_pos = xpos;
    s_state.last_y_pos = ypos;
}

void mouse_button_callback(GLFWwindow* window, i32 button, i32 action, i32 mods) {
    if (action != GLFW_RELEASE) {
        if (!s_state.buttons[button]) {
            s_state.buttons[button] = TRUE;
        }
    } else {
        s_state.buttons[button] = FALSE;
    }

    s_state.buttons_changed[button] = action != GLFW_REPEAT;
}

void mouse_wheel_callback(GLFWwindow* window, f64 delta_x, f64 delta_y) {
    s_state.x_scroll_delta = delta_x;
    s_state.y_scroll_delta = delta_y;
}

f64 mouse_x_pos() {
    return s_state.x_pos;
}
f64 mouse_y_pos() {
    return s_state.y_pos;
}
f64 mouse_x_pos_delta() {
    f64 tmp = s_state.x_pos_delta;
    s_state.x_pos_delta = 0;
    return tmp;
}
f64 mouse_y_pos_delta() {
    f64 tmp = s_state.y_pos_delta;
    s_state.y_pos_delta = 0;
    return tmp;
}
bool8 is_mouse_button_down(i32 button) {
    return s_state.buttons[button];
}
bool8 is_mouse_button_changed(i32 button) {
    bool8 tmp = s_state.buttons_changed[button];
    s_state.buttons_changed[button] = FALSE;
    return tmp;
}
bool8 is_moused_button_released(i32 button) {
    return !s_state.buttons[button] && is_mouse_button_changed(button);
}
bool8 is_mouse_button_pressed(i32 button) {
    return s_state.buttons[button] && is_mouse_button_changed(button);
}