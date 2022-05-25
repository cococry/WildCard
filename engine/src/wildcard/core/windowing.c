#include "windowing.h"

#include "internal/wldc_mem.h"
#include "asserts.h"

#include "io/keyboard.h"
#include "io/mouse.h"

#include <glad/glad.h>

void windowing_init() {
    WLDC_ASSERT_MSG(glfwInit(), "Failed to intialize GLFW!");
}
wldc_window
window_create(u32 width, u32 height, const char* title) {
    wldc_window window;
    wldc_zero_mem(&window, sizeof(window));

    window.glfw_instance = glfwCreateWindow(width, height, title, NULLPTR, NULLPTR);
    window.props.title = title;
    window.props.width = width;
    window.props.height = height;

    WLDC_ASSERT_MSG(window.glfw_instance, "Failed to create GLFW Window!");

    glfwMakeContextCurrent(window.glfw_instance);

    glfwSetKeyCallback(window.glfw_instance, keyboard_callback);
    glfwSetCursorPosCallback(window.glfw_instance, mouse_cursor_pos_callback);
    glfwSetScrollCallback(window.glfw_instance, mouse_wheel_callback);
    glfwSetMouseButtonCallback(window.glfw_instance, mouse_button_callback);

    // TODO:
    // glfwSetInputMode(window.glfw_instance, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    WLDC_ASSERT_MSG(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "Failed to initialize Glad!");

    return window;
}

void windowing_shutdown() {
    glfwTerminate();
}
void window_delete(wldc_window* window) {
    glfwDestroyWindow(window->glfw_instance);
}
void window_update(wldc_window* window) {
    glfwSwapBuffers(window->glfw_instance);
    glfwPollEvents();

    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
}
bool8 window_is_open(wldc_window* window) {
    return !glfwWindowShouldClose(window->glfw_instance);
}