#pragma once

#include "internal/wldc_def.h"

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

WLDC_API f64 app_get_delta_time();