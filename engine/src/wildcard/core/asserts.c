#include "asserts.h"

#include "logging.h"

void assertion_log(const char* expr, const char* msg, const char* file, i32 line) {
    WLDC_FATAL("Assertion Failed: %s : \"%s\" in file %s, line %d\n", expr, msg, file, line);
}