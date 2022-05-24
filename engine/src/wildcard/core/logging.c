#include "logging.h"
#include "../internal/wldc_windows_log.h"

#include <stdio.h>
#include <string.h>
#include <stdarg.h>

bool8 log_init() {
    return TRUE;
}

bool8 log_shutdown() {
    return TRUE;
}

void log_message(log_level level, const char* msg, ...) {
    const char* level_str[6] = {
        "[FATAL]: ",
        "[ERROR]: ",
        "[WARN]: ",
        "[INFO]: ",
        "[DEBUG]: ",
        "[TRACE]: "};

    bool8 msg_is_err = level < log_level_warn;

    char msg_buff[32000];
    memset(msg_buff, 0, sizeof(msg_buff));

    va_list arg_list;
    va_start(arg_list, msg);
    vsnprintf(msg_buff, 32000, msg, arg_list);
    va_end(arg_list);

    char out_msg[32000];
    sprintf(out_msg, "%s%s\n", level_str[level], msg_buff);

    if (!msg_is_err) {
        windows_print_console(out_msg, level);
    } else {
        windows_print_console_error(out_msg, level);
    }
}