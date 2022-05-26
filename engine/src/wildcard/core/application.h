#pragma once

#include "internal/wldc_def.h"
#include "io/event_system.h"

typedef struct application_props {
    i32 width, height;
    const char* title;

    void (*app_init_pfn)();
    void (*app_update_pfn)(f64 dt);
    void (*app_shtdown_pfn)();
} application_props;

WLDC_API void app_init(application_props* props);

WLDC_API void app_run();

WLDC_API void app_shutdown();

WLDC_API void app_close();

WLDC_API void suspend_app();

WLDC_API void unsuspend_app();

WLDC_API f64 app_get_delta_time();

void app_default_init_pfn();

void app_default_update_pfn(f64 dt);

void app_defaulft_sutdown_pfn();

bool8 app_on_event(u16 code, void* sender, void* linstener_inst, event_context context);

bool8 app_on_key_event(u16 code, void* sender, void* linstener_inst, event_context context);