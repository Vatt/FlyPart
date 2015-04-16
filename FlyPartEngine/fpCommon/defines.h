#ifndef _DEFINES_H
#define _DEFINES_H

#if defined(_WIN32) || defined(_WIN64)
#define PLATFORM_WINDOWS
#endif

#if defined(_GCC_) || defined(__MINGW32__)
#define GCC_COMPILER
#endif
#if defined(__MSVCRT__) && defined(_MSC_VER)
#define MSVS_COMPILER
#endif
#if defined(__LP64__) || defined(_M_IA64)
#define PLATFORM_64
#endif

#ifdef _WIN32
#define PLATFORM_32
#endif
