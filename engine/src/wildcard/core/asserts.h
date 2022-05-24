#pragma once

#include "../internal/wldc_def.h"

#define HLOW_ASSERTS_ENABLED

#ifdef HLOW_ASSERTS_ENABLED
#if _MSC_VER
#include <intrin.h>
#define debugBreak() __debugbreak()
#else
#define debugBreak() __builtin_trap()
#endif

WLDC_API void assertion_log(const char* expr, const char* msg, const char* file, i32 line);

#define WLDC_ASSERT(expr)                                 \
    {                                                     \
        if (expr) {                                       \
        } else {                                          \
            assertion_log(#expr, "", __FILE__, __LINE__); \
            debugBreak();                                 \
        }                                                 \
    }

#define WLDC_ASSERT_MSG(expr, msg)                         \
    {                                                      \
        if (expr) {                                        \
        } else {                                           \
            assertion_log(#expr, msg, __FILE__, __LINE__); \
            debugBreak();                                  \
        }                                                  \
    }

#ifdef _DEBUG
#define WLDC_ASSERT_DEBUG(expr)                           \
    {                                                     \
        if (expr) {                                       \
        } else {                                          \
            assertion_log(#expr, "", __FILE__, __LINE__); \
            debugBreak();                                 \
        }                                                 \
    }
#endif
#else

#define WLDC_ASSERT(expr)
#define WLDC_ASSERT_MSG(expr, msg)
#define WLDC_ASSERT_DEBUG(expr)

#endif