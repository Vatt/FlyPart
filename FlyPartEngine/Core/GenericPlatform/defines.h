#ifndef _DEFINES_H
#define _DEFINES_H
#pragma once
#if defined(_WIN32) || defined(_WIN64)
    #define PLATFORM_WINDOWS
#endif
#if defined(__linux__ )
    #define PLATFORM_LINUX
#endif
#if defined(__clang__)
    #define CLANG_COMPILER
#endif
#if defined(__GNUC__) || defined(__MINGW32__)
    #define GCC_COMPILER
#endif
#if defined(GCC_COMPILER)|| defined(CLANG_COMPILER)
    #define CONSTEXPR constexpr
    #define FORCEINLINE __attribute__((always_inline))
#endif
#if defined(_MSC_VER)
    #define MSVS_COMPILER
    #define FORCEINLINE __forceinline
    #define CONSTEXPR constexpr
#endif
#if defined(__LP64__) || defined(_M_IA64) || defined(_WIN64)
    #define PLATFORM_64
#endif


#endif //_DEFINES_H
