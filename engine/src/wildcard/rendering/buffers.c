#include "buffers.h"

#include "internal/wldc_mem.h"
#include "core/asserts.h"

#include <glad/glad.h>

vertex_buffer create_vertex_buffer(const void* data, u64 size) {
    vertex_buffer buffer;

    wldc_zero_mem(&buffer, sizeof(buffer));

    glCreateBuffers(1, &buffer.gl_id);
    glBindBuffer(GL_ARRAY_BUFFER, buffer.gl_id);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

    return buffer;
}

vertex_buffer create_vertex_buffer_no_data(u64 size) {
    vertex_buffer buffer;

    wldc_zero_mem(&buffer, sizeof(buffer));

    glCreateBuffers(1, &buffer.gl_id);
    glBindBuffer(GL_ARRAY_BUFFER, buffer.gl_id);
    glBufferData(GL_ARRAY_BUFFER, size, NULLPTR, GL_STATIC_DRAW);

    return buffer;
}

void set_vertex_buffer_data(vertex_buffer* buffer, const void* data, u64 size) {
    WLDC_ASSERT_MSG(buffer != NULLPTR, "Tried to set data of non-existend vertex buffer!");

    glBindBuffer(GL_ARRAY_BUFFER, buffer->gl_id);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}

void bind_vertex_buffer(vertex_buffer* buffer) {
    WLDC_ASSERT_MSG(buffer != NULLPTR, "Tried to bind non-existend vertex buffer!");

    glBindBuffer(GL_ARRAY_BUFFER, buffer->gl_id);
}

void unbind_vertex_buffer(vertex_buffer* buffer) {
    WLDC_ASSERT_MSG(buffer != NULLPTR, "Tried to unbind non-existend vertex buffer!");
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void delete_vertex_buffer(vertex_buffer* buffer) {
    WLDC_ASSERT_MSG(buffer != NULLPTR, "Tried to delete non-existend vertex buffer!");
    glDeleteBuffers(1, &buffer->gl_id);
}

index_buffer create_index_buffer(u32* data, u32 count) {
    index_buffer buffer;

    wldc_zero_mem(&buffer, sizeof(buffer));

    buffer.count = count;

    glCreateBuffers(1, &buffer.gl_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer.gl_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(u32), data, GL_STATIC_DRAW);

    return buffer;
}

index_buffer create_index_buffer_no_data(u64 count) {
    index_buffer buffer;

    wldc_zero_mem(&buffer, sizeof(buffer));

    buffer.count = count;

    glCreateBuffers(1, &buffer.gl_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer.gl_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(u32), NULLPTR, GL_STATIC_DRAW);

    return buffer;
}

void set_index_buffer_data(index_buffer* buffer, u32* data, u32 count) {
    WLDC_ASSERT_MSG(buffer != NULLPTR, "Tried to set data of non-existend index buffer!");

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer->gl_id);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, count * sizeof(u32), data);
}

void bind_index_buffer(index_buffer* buffer) {
    WLDC_ASSERT_MSG(buffer != NULLPTR, "Tried to bind non-existend index buffer!");
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer->gl_id);
}

void unbind_index_buffer(index_buffer* buffer) {
    WLDC_ASSERT_MSG(buffer != NULLPTR, "Tried to unbind non-existend index buffer!");
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void delete_index_buffer(index_buffer* buffer) {
    WLDC_ASSERT_MSG(buffer != NULLPTR, "Tried to delete non-existend index buffer!");
    glDeleteBuffers(1, &buffer->gl_id);
}
