#include "game.h"

#include <wildcard/core/logging.h>
#include <wildcard/internal/wldc_mem.h>
#include <wildcard/rendering/vertex_array.h>
#include <wildcard/rendering/buffers.h>
#include <wildcard/rendering/rendering_util.h>

struct game_state {
    vertex_array va;
};

static struct game_state s_state;

void game_init() {
    wldc_zero_mem(&s_state, sizeof(s_state));
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f};

    u32 indices[] = {0, 1, 2, 2, 3, 0};

    s_state.va = create_vertex_array();

    vertex_buffer vb = create_vertex_buffer_no_data(sizeof(vertices));
    set_vertex_buffer_data(&vb, vertices, sizeof(vertices));

    index_buffer ib = create_index_buffer(indices, sizeof(indices) / sizeof(u32));

    vertex_array_set_index_buffer(&s_state.va, &ib);

    set_vertex_buffer_layout_attribute(0, 3, sizeof(float) * 3, NULLPTR, FALSE, GL_FLOAT);
}

void game_update(f64 dt) {
    draw_indexed_vertex_array(&s_state.va);
}

void game_shutdown() {
    WLDC_ERROR("Shuting %s", "down.");
}