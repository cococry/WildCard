#pragma once

#include "internal/wldc_def.h"

#include <cglm/cglm.h>

#include <glad/glad.h>

typedef struct shader {
    u32 gl_id;
} shader;

WLDC_API shader create_shader(const char* vertex_file_path, const char* fragment_file_path);

WLDC_API void use_shader(shader* shader_inst);

WLDC_API void unuse_shader(shader* shader_inst);

WLDC_API void delete_shader(shader* shader_inst);

WLDC_API void shader_set_mat4(shader* shader_inst, const char* name, const mat4* value);

WLDC_API void shader_set_mat3(shader* shader_inst, const char* name, const mat3* value);

WLDC_API void shader_set_mat2(shader* shader_inst, const char* name, const mat2* value);

WLDC_API void shader_set_vec4(shader* shader_inst, const char* name, const vec4* value);

WLDC_API void shader_set_vec3(shader* shader_inst, const char* name, const vec3* value);

WLDC_API void shader_set_vec2(shader* shader_inst, const char* name, const vec2* value);

WLDC_API void shader_set_float(shader* shader_inst, const char* name, i32 value);

WLDC_API void shader_set_int(shader* shader_inst, const char* name, u32 value);

u32 _compile_shader(GLenum type, const char* filepath);

char* _get_file_contents(const char* filepath);

WLDC_API void _link_shader_program(shader* shader_inst, u32 vertex_shader, u32 fragment_shader);