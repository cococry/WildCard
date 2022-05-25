#include "vertex_array.h"

#include "internal/wldc_mem.h"

vertex_array create_vertex_array() {
    vertex_array va;

    wldc_zero_mem(&va, sizeof(va));

    glCreateVertexArrays(1, &va.gl_id);
    glBindVertexArray(va.gl_id);

    return va;
}

void bind_vertex_array(vertex_array* va) {
    glBindVertexArray(va->gl_id);
}

void unbind_vertex_array(vertex_array* va) {
    glBindVertexArray(0);
}

void delete_vertex_array(vertex_array* va) {
    glDeleteVertexArrays(1, &va->gl_id);
}

void set_vertex_buffer_layout_attribute(u32 index, i32 count, u64 stride, const void* offset, bool8 normalzied, GLenum type) {
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, count, type, normalzied, stride, offset);
}

void vertex_array_set_index_buffer(vertex_array* va, index_buffer* ib) {
    glBindVertexArray(va->gl_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib->gl_id);

    va->ib = *ib;
}
