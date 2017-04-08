#ifndef _DEFINES_H
#define _DEFINES_H
#pragma once
#define USED_TAGGED_POINTER

#if defined(_WIN32) || defined(_WIN64)
    #define PLATFORM_WINDOWS
#endif
#if defined(__linux__ )
    #define PLATFORM_LINUX
#endif
#if defined(__clang__)
    #define CLANG_COMPILER
#endif

#if defined(__MINGW32__)
    #define MINGW_COMPILER
#endif
#if defined(__GNUC__)
	#ifndef MINGW_COMPILER
		#define DEBUG_BUILD
		#define GCC_COMPILER
		#if defined(_DEBUG)
			#define DEBUG_BUILD
		#elif defined(_RELEASE)//<- set in project configuration settings
			#define RELEASE_BUILD
		#else
			//static_assert(false,"Failed to detect build type");
		#endif
	#endif
#endif
#if defined(GCC_COMPILER)|| defined(CLANG_COMPILER) || defined(MINGW_COMPILER)
    #define CONSTEXPR constexpr
    #define FORCEINLINE inline __attribute__((always_inline))
#endif
#if defined(_MSC_VER)
    #define MSVS_COMPILER
    //#define FORCEINLINE __forceinline
	#define FORCEINLINE inline
    #define CONSTEXPR constexpr
	#if defined(_DEBUG)
		#define DEBUG_BUILD
	#elif defined(_RELEASE)//<- set in project configuration settings
		#define RELEASE_BUILD
	#else
//		static_assert(false,"Failed to detect build type");
	#endif

#endif
#if  defined(__LP64__) || defined(_M_IA64) || defined(_WIN64) 
    #define PLATFORM_64
#endif
#if defined(_WIN32)
	#ifndef _WIN64
		#define PLATFORM_32
	#endif
#endif

#endif //_DEFINES_H
