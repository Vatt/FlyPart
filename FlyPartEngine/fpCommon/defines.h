#ifndef _DEFINES_H
#define _DEFINES_H
#pragma once
#if defined(_WIN32) || defined(_WIN64)
#define PLATFORM_WINDOWS
#endif
#if defined(__linux__ )
#define PLATFORM_LINUX
#endif
#if defined(_GCC_) || defined(__MINGW32__)
#define GCC_COMPILER
#define FORCEINLINE __attribute__((always_inline))
#define CONSTEXPR constexpr
#endif
#if defined(_MSC_VER)
#define MSVS_COMPILER
#define FORCEINLINE __forceinline
#define CONSTEXPR constexpr
#endif
#if defined(__LP64__) || defined(_M_IA64)
#define PLATFORM_64
#endif

#ifdef _M_AMD64
#define PLATFORM_64
#endif
#endif //_DEFINES_H