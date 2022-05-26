#include "application.h"

#include "internal/wldc_mem.h"
#include "windowing.h"
#include "io/keyboard.h"
#include "io/mouse.h"
#include "io/event_system.h"
#include "rendering/rendering_util.h"
#include "asserts.h"
#include "logging.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

struct application_state {
    bool8 running;
    bool8 suspended;
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

    if (!s_state.props->app_init_pfn) {
        s_state.props->app_init_pfn = app_default_init_pfn;
    }
    if (!s_state.props->app_update_pfn) {
        s_state.props->app_update_pfn = app_default_update_pfn;
    }
    if (!s_state.props->app_shtdown_pfn) {
        s_state.props->app_shtdown_pfn = app_defaulft_sutdown_pfn;
    }

    WLDC_ASSERT_MSG(initialize_event_system(), "Failed to intialize event system!");

    register_event(event_code_app_quit, 0, app_on_event);
    register_event(event_code_key_pressed, 0, app_on_key_event);
    register_event(event_code_key_released, 0, app_on_key_event);

    s_state.last_frame_time = 0.0;
    s_state.delta_time = 0.0f;
    s_state.window = window_create(s_state.props->width, s_state.props->height, s_state.props->title);
    rendering_init();

    s_state.props->app_init_pfn();
}
void app_run() {
    while (s_state.running) {
        f64 this_frame_time = glfwGetTime();
        s_state.delta_time = this_frame_time - s_state.last_frame_time;
        s_state.last_frame_time = this_frame_time;

        if (!window_is_open(&s_state.window)) {
            app_close();
        }

        if (!s_state.suspended) {
            glClear(GL_COLOR_BUFFER_BIT);
            glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

            s_state.props->app_update_pfn(s_state.delta_time);
        }

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

    unregister_event(event_code_app_quit, 0, app_on_event);
    unregister_event(event_code_key_pressed, 0, app_on_key_event);
    unregister_event(event_code_key_released, 0, app_on_key_event);

    shutdown_event_system();
}

void app_close() {
    s_state.running = FALSE;
}
f64 app_get_delta_time() {
    return s_state.delta_time;
}

void app_default_init_pfn() {
}

void app_default_update_pfn(f64 dt) {
}

void app_defaulft_sutdown_pfn() {
}

void suspend_app() {
    s_state.suspended = TRUE;
}
void unsuspend_app() {
    s_state.suspended = FALSE;
}

bool8 app_on_event(u16 code, void* sender, void* linstener_inst, event_context context) {
    switch (code) {
        case event_code_app_quit: {
            s_state.running = FALSE;
            return TRUE;
        }
    }
    return FALSE;
}

bool8 app_on_key_event(u16 code, void* sender, void* linstener_inst, event_context context) {
    if (code == event_code_key_pressed) {
        i32 key_code = context.data.i32[0];
        if (key_code == GLFW_KEY_ESCAPE) {
            event_context data;
            wldc_zero_mem(&data, sizeof(data));

            dispatch_event(event_code_app_quit, 0, data);

            return TRUE;
        } else if (key_code == GLFW_KEY_W) {
            WLDC_INFO("Pressed W %s", "(Checking explicitly)");
        } else {
            WLDC_DEBUG("'%c' key was pressed.", key_code);
        }
    } else if (code == event_code_key_released) {
        i32 key_code = context.data.i32[0];
        if (key_code == GLFW_KEY_ENTER) {
            WLDC_INFO("Released Enter %s", "(Checking explicitly)");
        } else {
            WLDC_WARN("'%c' key was released.", key_code);
        }
    }
    return TRUE;
}