#include "keyboard.h"

#include "internal/wldc_mem.h"

struct keyboard_state {
    bool8* keys;
    bool8* keys_changed;
};

static struct keyboard_state s_state;

void keyboard_io_init() {
    wldc_zero_mem(&s_state, sizeof(s_state));
    s_state.keys = wldc_malloc(sizeof(bool8) * GLFW_KEY_LAST, mem_type_array);
    s_state.keys_changed = wldc_malloc(sizeof(bool8) * GLFW_KEY_LAST, mem_type_array);
}
void keyboard_callback(GLFWwindow* window, i32 key, i32 scancode, i32 action, i32 mods) {
    if (action != GLFW_RELEASE) {
        if (!s_state.keys[key]) {
            s_state.keys[key] = TRUE;
        }
    } else {
        s_state.keys[key] = FALSE;
    }
    s_state.keys_changed[key] = action != GLFW_REPEAT;
}

bool8 is_key_down(i32 key) {
    return s_state.keys[key];
}
bool8 is_key_changed(i32 key) {
    bool8 tmp = s_state.keys_changed[key];
    s_state.keys_changed[key] = FALSE;
    return tmp;
}
bool8 is_key_released(i32 key) {
    return !s_state.keys[key] && is_key_changed(key);
}
bool8 is_key_typed(i32 key) {
    return s_state.keys[key] && is_key_changed(key);
}