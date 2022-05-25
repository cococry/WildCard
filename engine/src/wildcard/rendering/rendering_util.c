#include "rendering_util.h"

#include <glad/glad.h>

void resize_viewport(u32 x, u32 y) {
    glViewport(0, 0, x, y);
}

void draw_indexed_vertex_array(vertex_array* va) {
    glDrawElements(GL_TRIANGLES, va->ib.count, GL_UNSIGNED_INT, NULLPTR);
}

void draw_indexed(u32 count) {
    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, NULLPTR);
}