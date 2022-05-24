#include <wildcard/core/windowing.h>
#include <wildcard/core/logging.h>
#include <wildcard/core/asserts.h>

int main(void) {
    windowing_init();

    wldc_window win = window_create(1920, 1080, "WildCard Tests");

    while (window_is_open(&win)) {
        window_update(&win);
    }

    windowing_shutdown();
}