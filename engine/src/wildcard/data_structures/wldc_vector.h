#pragma once

#include "internal/wldc_def.h"

#define VECTOR_START_CAPACITY 1
#define VECTOR_RESIZE_FACTOR 2

enum {
    vector_capacity,
    vector_element_count,
    vector_element_stride,

    vector_variables_length
};

WLDC_API void* _create_vector(u64 element_count, u64 element_stride);

WLDC_API void _destroy_vector(void* vec);

WLDC_API u64 _get_vector_variable(void* vec, u64 variable);

WLDC_API void _set_vector_variable(void* vec, u64 variable, u64 value);

WLDC_API void* _resize_vector(void* vec);

WLDC_API void* _push_to_vector(void* vec, void* val_ptr);

WLDC_API void _pop_from_vector(void* vec, void* dst);

WLDC_API void* _insert_at_vector(void* vec, u64 index, void* val_ptr);

WLDC_API void* _pop_at_vector(void* vec, u64 index, void* dst);

#define create_vector(type) _create_vector(VECTOR_START_CAPACITY, sizeof(type))
#define reserve_vector(type, cap) _create_vector(cap, sizeof(type))
#define destroy_vector(vec) _destroy_vector(vec)

#define push_to_vector(vec, val)          \
    {                                     \
        typeof(val) tmp = val;            \
        vec = _push_to_vector(vec, &tmp); \
    }

#define pop_from_vector(vec, val_ptr) _pop_from_vector(vec, val_ptr)

#define insert_at_vector(vec, index, val)          \
    {                                              \
        typeof(val) tmp = val;                     \
        vec = _insert_at_vector(vec, index, &tmp); \
    }

#define resize_vector(vec) _resize_vector(vec)

#define pop_at_vector(vec, index, val_ptr) _pop_at_vector(vec, index, val_ptr)

#define clear_vector(vec) _get_vector_variable(vec, vector_element_count, 0)

#define get_vector_capacity(vec) _get_vector_variable(vec, vector_capacity)

#define get_vector_element_count(vec) _get_vector_variable(vec, vector_element_count)

#define get_vector_stride(vec) _get_vector_variable(vec, vector_element_stride)

#define set_vector_element_count(vec, val) _set_vector_variable(vec, vector_element_count, val)