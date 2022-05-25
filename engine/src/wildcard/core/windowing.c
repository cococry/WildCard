#include "windowing.h"

#include "internal/wldc_mem.h"
#include "asserts.h"
#include "rendering/rendering_util.h"

#include "io/keyboard.h"
#include "io/mouse.h"
#include "logging.h"
#include <glad/glad.h>

void windowing_init() {
    WLDC_ASSERT_MSG(glfwInit(), "Failed to intialize GLFW!");
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
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

    WLDC_ASSERT_MSG(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "Failed to intialize Glad!");

    glfwSetFramebufferSizeCallback(window.glfw_instance, viewport_resize_callback);
    glfwSetKeyCallback(window.glfw_instance, keyboard_callback);
    glfwSetCursorPosCallback(window.glfw_instance, mouse_cursor_pos_callback);
    glfwSetScrollCallback(window.glfw_instance, mouse_wheel_callback);
    glfwSetMouseButtonCallback(window.glfw_instance, mouse_button_callback);

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
}
bool8 window_is_open(wldc_window* window) {
    return !glfwWindowShouldClose(window->glfw_instance);
}
void viewport_resize_callback(GLFWwindow* window, int width, int height) {
    resize_viewport(width, height);
}