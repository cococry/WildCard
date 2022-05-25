#include "shader.h"

#include <stdio.h>
#include <stdlib.h>

#include "core/asserts.h"
#include "core/logging.h"
#include "internal/wldc_mem.h"

shader create_shader(const char* vertex_file_path, const char* fragment_file_path) {
    shader shader_inst;

    wldc_zero_mem(&shader_inst, sizeof(shader_inst));

    u32 vertex_shader = _compile_shader(GL_VERTEX_SHADER, vertex_file_path);
    u32 fragment_shader = _compile_shader(GL_FRAGMENT_SHADER, fragment_file_path);

    _link_shader_program(&shader_inst, vertex_shader, fragment_shader);

    return shader_inst;
}
void use_shader(shader* shader_inst) {
    glUseProgram(shader_inst->gl_id);
}
void unuse_shader(shader* shader_inst) {
    glUseProgram(0);
}
void delete_shader(shader* shader_inst) {
    glDeleteProgram(shader_inst->gl_id);
}
void shader_set_mat4(shader* shader_inst, const char* name, const mat4* value) {
    glUniformMatrix4fv(glGetUniformLocation(shader_inst->gl_id, name), 1, GL_FALSE, (float*)value);
}
void shader_set_mat3(shader* shader_inst, const char* name, const mat3* value) {
    glUniformMatrix3fv(glGetUniformLocation(shader_inst->gl_id, name), 1, GL_FALSE, (float*)value);
}
void shader_set_mat2(shader* shader_inst, const char* name, const mat2* value) {
    glUniformMatrix2fv(glGetUniformLocation(shader_inst->gl_id, name), 1, GL_FALSE, (float*)value);
}
void shader_set_vec4(shader* shader_inst, const char* name, const vec4* value) {
    glUniform4fv(glGetUniformLocation(shader_inst->gl_id, name), 1, (float*)value);
}
void shader_set_vec3(shader* shader_inst, const char* name, const vec3* value) {
    glUniform3fv(glGetUniformLocation(shader_inst->gl_id, name), 1, (float*)value);
}
void shader_set_vec2(shader* shader_inst, const char* name, const vec2* value) {
    glUniform2fv(glGetUniformLocation(shader_inst->gl_id, name), 1, (float*)value);
}
void shader_set_float(shader* shader_inst, const char* name, i32 value) {
    glUniform1f(glGetUniformLocation(shader_inst->gl_id, name), value);
}
void shader_set_int(shader* shader_inst, const char* name, u32 value) {
    glUniform1i(glGetUniformLocation(shader_inst->gl_id, name), value);
}
u32 _compile_shader(GLenum type, const char* filepath) {
    int success;
    char info_log[512];
    u32 shader;
    shader = glCreateShader(type);

    const char* shader_source = _get_file_contents(filepath);
    glShaderSource(shader, 1, &shader_source, NULLPTR);
    glCompileShader(shader);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(shader, 512, NULLPTR, info_log);
        const char* shader_type_str = (type == GL_FRAGMENT_SHADER) ? "fragment" : "vertex";
        WLDC_ERROR("Failed to compile %s shader:\n%s", shader_type_str, info_log);
    }
    return shader;
}
char* _get_file_contents(const char* filepath) {
    char* buffer = NULLPTR;
    long length;

    FILE* file = fopen(filepath, "rb");

    char msg[256];
    sprintf(msg, "Failed to open shader file at location '%s'!", filepath);
    WLDC_ASSERT_MSG(file != NULL, msg);

    fseek(file, 0, SEEK_END);
    length = ftell(file);
    fseek(file, 0, SEEK_SET);
    buffer = malloc(length);
    if (buffer) {
        fread(buffer, 1, length, file);
    }
    fclose(file);

    buffer[length] = 0;

    return buffer;
}
void _link_shader_program(shader* shader_inst, u32 vertex_shader, u32 fragment_shader) {
    int success;
    char info_log[512];

    shader_inst->gl_id = glCreateProgram();
    glAttachShader(shader_inst->gl_id, vertex_shader);
    glAttachShader(shader_inst->gl_id, fragment_shader);
    glLinkProgram(shader_inst->gl_id);

    glGetProgramiv(shader_inst->gl_id, GL_LINK_STATUS, &success);

    if (!success) {
        glGetProgramInfoLog(shader_inst->gl_id, 512, NULLPTR, info_log);
        WLDC_ERROR("Failed to link shader program:\n%s", info_log);
    }
}