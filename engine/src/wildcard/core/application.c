#include "application.h"

#include "internal/wldc_mem.h"
#include "windowing.h"
#include "io/keyboard.h"
#include "io/mouse.h"
#include "rendering/rendering_util.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

struct application_state {
    bool8 running;
    f64 last_frame_time;
    f64 delta_time;
    wldc_window window;
    application_props* props;
};

static struct application_state s_state;

void app_init(application_props* props) {
    windowing_init();
    keyboard_io_init();
    mouse_io_init();

    wldc_zero_mem(&s_state, sizeof(s_state));

    s_state.running = TRUE;
    s_state.props = props;

    s_state.last_frame_time = 0.0;
    s_state.delta_time = 0.0f;
    s_state.window = window_create(s_state.props->width, s_state.props->height, s_state.props->title);
    rendering_init();

    s_state.props->app_init_pfn();
}
void app_run() {
    while (s_state.running) {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

        f64 this_frame_time = glfwGetTime();
        s_state.delta_time = this_frame_time - s_state.last_frame_time;
        s_state.last_frame_time = this_frame_time;

        if (!window_is_open(&s_state.window)) {
            app_close();
        }
        s_state.props->app_update_pfn(s_state.delta_time);

        window_update(&s_state.window);
    }
    app_shutdown();
}
void app_shutdown() {
    s_state.props->app_shtdown_pfn();

    wldc_zero_mem(&s_state, sizeof(s_state));

    keyboard_io_shutdown();
    mouse_io_shudown();
    windowing_shutdown();
}

void app_close() {
    s_state.running = FALSE;
}
f64 app_get_delta_time() {
    return s_state.delta_time;
}