#pragma once

#include "internal/wldc_def.h"

typedef enum event_code {
    event_code_app_quit = 0x01,
    event_code_key_pressed = 0x02,
    event_code_key_released = 0x03,
    event_code_mouse_button_pressed = 0x04,
    event_code_mouse_button_released = 0x05,
    event_code_mouse_moved = 0x06,
    event_code_mousewheel = 0x07,
    event_code_window_resized = 0x08,

    event_code_number_of_events_codes = 0xFF
} event_code;

typedef struct event_context {
    union {
        i64 i64[2];
        u64 u64[2];
        f64 f64[2];

        i32 i32[4];
        u32 u32[4];
        f32 f32[4];

        i16 i16[8];
        u16 u16[8];

        i8 i8[16];
        u8 u8[16];
        char chr[16];
    } data;
} event_context;

typedef bool8 (*event_pfn)(u16 code, void* sender, void* listener_handle, event_context data);

bool8 initialize_event_system();

void shutdown_event_system();

WLDC_API bool8 register_event(u16 code, void* listener, event_pfn on_event);

WLDC_API bool8 unregister_event(u16 code, void* listener, event_pfn on_event);

WLDC_API bool8 dispatch_event(u16 code, void* sender, event_context context);