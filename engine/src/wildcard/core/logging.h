#pragma once

#include "internal/wldc_def.h"

#define LOG_LEVEL_WARN 1
#define LOG_LEVEL_INFO 1
#define LOG_LEVEL_DEBUG 1
#define LOG_LEVEL_TRACE 1

#if WLDC_RELEASE == 1
#define LOG_LEVEL_DEBUG 0
#define LOG_LEVEL_TRACE 0
#endif

typedef enum log_level {
    log_level_fatal = 0,
    log_level_error,
    log_level_warn,
    log_level_info,
    log_level_debug,
    log_level_trace
} log_level;

bool8 log_init();

bool8 log_shutdown();

WLDC_API void log_message(log_level level, const char* msg, ...);

#ifndef WLDC_FATAL
#define WLDC_FATAL(fmt_msg, ...) log_message(log_level_fatal, fmt_msg, ##__VA_ARGS__)
#endif

#ifndef WLDC_ERROR
#define WLDC_ERROR(fmt_msg, ...) log_message(log_level_error, fmt_msg, ##__VA_ARGS__)
#endif

#if LOG_LEVEL_WARN == 1
#define WLDC_WARN(fmt_msg, ...) log_message(log_level_warn, fmt_msg, ##__VA_ARGS__)
#else
#define WLDC_WARN(fmt_msg, ...)
#endif

#if LOG_LEVEL_INFO == 1
#define WLDC_INFO(fmt_msg, ...) log_message(log_level_info, fmt_msg, ##__VA_ARGS__)
#else
#define WLDC_INFO(fmt_msg, ...)
#endif

#if LOG_LEVEL_DEBUG == 1
#define WLDC_DEBUG(fmt_msg, ...) log_message(log_level_debug, fmt_msg, ##__VA_ARGS__);
#else
#define WLDC_DEBUG(fmt_msg, ...)
#endif

#if LOG_LEVEL_TRACE == 1
#define WLDC_TRACE(fmt_msg, ...) log_message(log_level_trace, fmt_msg, ##__VA_ARGS__)
#else
#define WLDC_TRACE(fmt_msg, ...)
#endif