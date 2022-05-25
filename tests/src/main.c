#include <wildcard/core/windowing.h>
#include <wildcard/core/logging.h>
#include <wildcard/core/asserts.h>
#include <wildcard/io/keyboard.h>
#include <wildcard/io/mouse.h>

int main(void) {
    windowing_init();
    keyboard_io_init();
    mouse_io_init();

    wldc_window win = window_create(1920, 1080, "WildCard Tests");

    while (window_is_open(&win)) {
        if (is_key_released(GLFW_KEY_W)) {
            WLDC_INFO("Released %s", "W!");
        } else if (is_key_typed(GLFW_KEY_W)) {
            WLDC_WARN("Typed %s", "W!");
        }
        if (is_mouse_button_pressed(GLFW_MOUSE_BUTTON_LEFT)) {
            WLDC_ERROR("Typed %s", "left mouse!");
        }
        else if(is_moused_button_released(GLFW_MOUSE_BUTTON_LEFT)) {
            WLDC_DEBUG("Released %s", "left mouse!");
        }

        window_update(&win);
    }

    windowing_shutdown();
}