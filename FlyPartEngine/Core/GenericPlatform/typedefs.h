#ifndef _TYPE_DEFS_
#define _TYPE_DEFS_
#pragma once
#include "defines.h"
#include <wchar.h>
#if defined (PLATFORM_64) && defined(PLATFORM_WINDOWS)
typedef unsigned int            uint32; //4
typedef signed int              int32;  //4
typedef unsigned long long int  uint64; //8
typedef signed long long int    int64;  //8
typedef unsigned short          uint16; //2
typedef signed short            int16;  //2
typedef char					int8;   //1
typedef char					ASCICHAR; //1
typedef wchar_t					WIDECHAR; //16

#endif
#if defined (PLATFORM_64) && defined(PLATFORM_LINUX)
typedef unsigned int            uint32; //4
typedef signed int              int32;  //4
typedef unsigned long long int  uint64; //8
typedef signed long long int    int64;  //8
typedef unsigned short          uint16; //2
typedef signed short            int16;  //2
typedef char					int8;   //1
typedef char					ASCICHAR; //1
typedef wchar_t					WIDECHAR; //32(!)

#endif
#if defined(PLATFORM_32) || defined(GCC_COMPILER)
typedef unsigned int            uint32; //4
typedef signed int              int32;  //4
typedef unsigned long long int  uint64; //8
typedef signed long long int    int64;  //8
typedef unsigned short          uint16; //2
typedef signed short            int16;  //2
typedef char					int8;   //1
typedef char					ASCICHAR; //1
typedef wchar_t					WIDECHAR;

#endif

#endif
