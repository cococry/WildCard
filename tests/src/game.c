#include "game.h"

#include <wildcard/core/logging.h>
#include <wildcard/internal/wldc_mem.h>
#include <wildcard/rendering/vertex_array.h>
#include <wildcard/rendering/buffers.h>
#include <wildcard/rendering/rendering_util.h>
#include <wildcard/rendering/shader.h>
#include <wildcard/rendering/texture.h>

#include <stdio.h>

struct game_state {
    vertex_array va;
    shader shader_inst;
    texture tex;
};

static struct game_state s_state;

void game_init() {
    wldc_zero_mem(&s_state, sizeof(s_state));
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
        0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f};

    u32 indices[] = {0, 1, 2, 2, 3, 0};

    s_state.va = create_vertex_array();

    vertex_buffer vb = create_vertex_buffer_no_data(sizeof(vertices));
    set_vertex_buffer_data(&vb, vertices, sizeof(vertices));

    index_buffer ib = create_index_buffer(indices, sizeof(indices) / sizeof(u32));

    vertex_array_set_index_buffer(&s_state.va, &ib);

    set_vertex_buffer_layout_attribute(0, 3, sizeof(float) * 5, NULLPTR, FALSE, GL_FLOAT);
    set_vertex_buffer_layout_attribute(1, 2, sizeof(float) * 5, (void*)(sizeof(float) * 3), FALSE, GL_FLOAT);

    s_state.shader_inst = create_shader("../engine/assets/shaders/core_vertex2D.glsl", "../engine/assets/shaders/core_fragment2D.glsl");

    s_state.tex = create_texture("../engine/assets/images/git-cococry-pixelart.png", true);

    shader_set_int(&s_state.shader_inst, "u_Texture", 0);
}

void game_update(f64 dt) {
    active_texture_slot(0);
    bind_texture(&s_state.tex);
    use_shader(&s_state.shader_inst);
    draw_indexed_vertex_array(&s_state.va);
}

void game_shutdown() {
}