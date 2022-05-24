#include "wldc_windows_log.h"

#include <Windows.h>

void windows_print_console(const char* msg, u8 color) {
    HANDLE console_handle = GetStdHandle(STD_OUTPUT_HANDLE);

    static u8 levels[6] = {64, 4, 6, 2, 1, 8};
    SetConsoleTextAttribute(console_handle, levels[color]);
    OutputDebugStringA(msg);
    u64 length = strlen(msg);
    LPDWORD chars_written = 0;
    WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE), msg, (DWORD)length, chars_written, 0);
}

void windows_print_console_error(const char* msg, u8 color) {
    HANDLE console_handle = GetStdHandle(STD_ERROR_HANDLE);

    static u8 levels[6] = {64, 4, 6, 2, 1, 8};
    SetConsoleTextAttribute(console_handle, levels[color]);
    OutputDebugStringA(msg);
    u64 length = strlen(msg);
    LPDWORD chars_written = 0;
    WriteConsoleA(GetStdHandle(STD_ERROR_HANDLE), msg, (DWORD)length, chars_written, 0);
}