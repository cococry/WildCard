#include "logging.h"

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
        "[ERROR]: ",
        "[FATAL]: ",
        "[WARN]: ",
        "[INFO]: ",
        "[TRACE]: ",
        "[DEBUG]: "};

    char msg_buff[32000];
    memset(msg_buff, 0, sizeof(msg_buff));

    va_list arg_list;
    va_start(arg_list, msg);
    vsnprintf(msg_buff, 32000, msg, arg_list);
    va_end(arg_list);

    char out_msg[32000];
    sprintf(out_msg, "%s%s\n", level_str[level], msg_buff);

    printf("%s", out_msg);
}