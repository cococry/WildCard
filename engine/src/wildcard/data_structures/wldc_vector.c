#include "wldc_vector.h"

#include "core/logging.h"
#include "internal/wldc_mem.h"

void* _create_vector(u64 element_count, u64 element_stride) {
    u64 variables_size = vector_variables_length * sizeof(u64);
    u64 vector_size = element_count * element_stride;
    u64* new_array = wldc_malloc(variables_size + vector_size, mem_type_vector);
    wldc_set_mem(new_array, 0, variables_size + vector_size);
    new_array[vector_capacity] = element_count;
    new_array[vector_element_count] = 0;
    new_array[vector_element_stride] = element_stride;

    return (void*)(new_array + vector_variables_length);
}
void _destroy_vector(void* vec) {
    u64* vector_variables = (u64*)vec - vector_variables_length;
    u64 vector_variables_size = vector_variables_length * sizeof(u64);
    u64 total_vector_size = vector_variables_size + vector_variables[vector_capacity] * vector_variables[vector_element_stride];
    wldc_free(vector_variables, total_vector_size, mem_type_vector);
}
u64 _get_vector_variable(void* vec, u64 variable) {
    u64* vector_variables = (u64*)vec - vector_variables_length;
    return vector_variables[variable];
}
void _set_vector_variable(void* vec, u64 variable, u64 value) {
    u64* vector_variables = (u64*)vec - vector_variables_length;
    vector_variables[variable] = value;
}
void* _resize_vector(void* vec) {
    u64 element_count = get_vector_element_count(vec);
    u64 stride = get_vector_stride(vec);
    void* ret = _create_vector(
        (VECTOR_RESIZE_FACTOR * get_vector_capacity(vec)),
        stride);
    wldc_copy_mem(ret, vec, element_count * stride);

    _set_vector_variable(ret, vector_element_count, element_count);
    _destroy_vector(vec);
    return ret;
}
void* _push_to_vector(void* vec, void* val_ptr) {
    u64 element_count = get_vector_element_count(vec);
    u64 stride = get_vector_stride(vec);
    if (element_count >= get_vector_capacity(vec)) {
        vec = _resize_vector(vec);
    }

    u64 vec_addr = (u64)vec;

    vec_addr += (element_count * stride);
    wldc_copy_mem((void*)vec_addr, val_ptr, stride);
    _set_vector_variable(vec, vector_element_count, element_count + 1);
    return vec;
}
void _pop_from_vector(void* vec, void* dst) {
    u64 element_count = get_vector_element_count(vec);
    u64 stride = get_vector_stride(vec);

    u64 vec_addr = (u64)vec;

    vec_addr += ((element_count - 1) * stride);
    wldc_copy_mem(dst, (void*)vec_addr, stride);
    _set_vector_variable(vec, vector_element_count, element_count - 1);
}
void* _insert_at_vector(void* vec, u64 index, void* val_ptr) {
    u64 element_count = get_vector_element_count(vec);
    u64 stride = get_vector_stride(vec);
    if (index >= element_count) {
        WLDC_ERROR("Vector insert at: Vector index out of bounds: Vector size: %d, Indexed at: %d", element_count, index);
        return vec;
    }
    if (element_count >= get_vector_capacity(vec)) {
        vec = _resize_vector(vec);
    }

    u64 vec_addr = (u64)vec;

    if (index != element_count - 1) {
        wldc_copy_mem(
            (void*)(vec_addr + ((index + 1) * stride)),
            (void*)(vec_addr + index * stride),
            stride * (element_count - index));
    }
    wldc_copy_mem((void*)(vec_addr + (index * stride)), val_ptr, stride);

    _set_vector_variable(vec, vector_element_count, element_count + 1);
    return vec;
}
void* _pop_at_vector(void* vec, u64 index, void* dst) {
    u64 element_count = get_vector_element_count(vec);
    u64 stride = get_vector_stride(vec);
    if (index >= element_count) {
        WLDC_ERROR("Vector pop at: Vector index out of bounds: Vector size: %d, Indexed at: %d", element_count, index);
        return vec;
    }

    u64 vec_addr = (u64)vec;
    wldc_copy_mem(dst, (void*)(vec_addr + (index * stride)), stride);

    if (index != element_count - 1) {
        wldc_copy_mem(
            (void*)(vec_addr + (index * stride)),
            (void*)(vec_addr + (index + 1) * stride),
            stride * (element_count - index));
    }

    _set_vector_variable(vec, vector_element_count, element_count - 1);
    return vec;
}