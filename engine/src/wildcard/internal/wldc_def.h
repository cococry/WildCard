
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef signed char i8;
typedef signed short i16;
typedef signed int i32;
typedef signed long long i64;

typedef float f32;
typedef double f64;

typedef unsigned char bool8;
typedef unsigned short bool16;
typedef unsigned int bool32;
typedef unsigned long long bool64;

#define TRUE 1
#define FALSE 0
#define NULLPTR (void*)0

#if defined(__clang__) || defined(__gcc__)
#define WLDC_STATIC_ASSERT _Static_assert
#else
#define WLDC_STATIC_ASSERT static_assert
#endif

WLDC_STATIC_ASSERT(sizeof(u8) == 1, "Byte size of unsigned char has to be 1 byte to run the program.");
WLDC_STATIC_ASSERT(sizeof(u16) == 2, "Byte size of unsigned short has to be 2 bytes to run the program.");
WLDC_STATIC_ASSERT(sizeof(u32) == 4, "Byte size of unsigned int has to be 4 bytes to run the program.");
WLDC_STATIC_ASSERT(sizeof(u64) == 8, "Byte size of unsigned long long has to be 8 bytes to run the program.");

WLDC_STATIC_ASSERT(sizeof(i8) == 1, "Byte size of signed char has to be 1 byte to run the program.");
WLDC_STATIC_ASSERT(sizeof(i16) == 2, "Byte size of signed short has to be 2 bytes to run the program.");
WLDC_STATIC_ASSERT(sizeof(i32) == 4, "Byte size of signed int has to be 4 bytes to run the program.");
WLDC_STATIC_ASSERT(sizeof(i64) == 8, "Byte size of signed long long has to be 8 bytes to run the program.");

WLDC_STATIC_ASSERT(sizeof(f32) == 4, "Byte size of float has to be 4 bytes to run the program.");
WLDC_STATIC_ASSERT(sizeof(f64) == 8, "Byte size of double has to be 8 bytes to run the program.");

#if defined(__WIN32__) || defined(_WIN32) || defined(WIN32)
#ifdef _WIN64
#define WLDC_WINDOWS 1
#else
#error Failed to run program. Could not detect x64 Windows OS.
#endif
#elif defined(__linux__) || defined(__gnu_linux__)
#define WLDC_LINUX 1
#if defined(__ANDROID__)
#define WLDC_ANDROID 1
#endif
#elif defined(__unix__)
#define WLDC_UNIX 1
#elif defined(_POSIX_VERSION)
#define WLDC_POSIX 1
#elif __APPLE__
#define WLDC_APPLE 1
#include <TargetConditionals.h>
#if TARGET_IPHONE_SIMULATOR
#define WLDC_IOS 1
#define WLDC_IOS_SIMULATOR 1
#elif TARGET_OS_IPHONE
#define WLDC_IOS 1
#elif TARGET_OS_MAC
#define WLDC_MAC
#else
#error "Tried to run programm with unkown Apple OS!"
#endif
#else
#error "Tried to run program with unknown OS!"
#endif

#ifdef WLDC_EXPORT
#ifdef _MSC_VER
#define WLDC_API __declspec(dllexport)
#else
#define WLDC_API __attribute__((visibility("default")))
#endif

#else
#ifdef _MSC_VER
#define WLDC_API __declspec(dllimport)
#else
#define WLDC_API
#endif
#endif