#ifndef _TYPE_DEFS_
#define _TYPE_DEFS_
#pragma once
#include "defines.h"
#include <wchar.h>
#include <stdint.h>
#if defined (PLATFORM_64) && defined(PLATFORM_WINDOWS)
typedef uint32_t				uint32; //4 unsigned int
typedef int32_t			        int32;  //4 signed int
typedef uint64_t				uint64; //8 unsigned long long int
typedef int64_t					int64;  //8 signed long long int 
typedef uint16_t	            uint16; //2 unsigned short  
typedef int16_t                 int16;  //2 signed short
typedef int8_t					int8;   //1 char
typedef uint8_t			        uint8;  //1 unsigned char
typedef uintptr_t			    UINTPTR;
typedef size_t					SIZE_T;
typedef char					ASCICHAR; //1
typedef wchar_t					WIDECHAR; //16

#endif
#if defined (PLATFORM_64) && defined(PLATFORM_LINUX)
typedef uint32_t				uint32; //4 unsigned int
typedef int32_t			        int32;  //4 signed int
typedef uint64_t				uint64; //8 unsigned long long int
typedef int64_t					int64;  //8 signed long long int 
typedef uint16_t	            uint16; //2 unsigned short  
typedef int16_t                 int16;  //2 signed short
typedef int8_t					int8;   //1 char
typedef uint8_t			        uint8;  //1 unsigned char
typedef uintptr_t			    UINTPTR;
typedef size_t					SIZE_T;
typedef char					ASCICHAR; //1
typedef wchar_t					WIDECHAR; //32(1)
/*typedef unsigned int            uint32; //4
typedef signed int              int32;  //4
typedef unsigned long long int  uint64; //8
typedef signed long long int    int64;  //8
typedef unsigned short          uint16; //2
typedef signed short            int16;  //2
typedef unsigned char			uint8;  //1
typedef char					int8;   //1
typedef char					ASCICHAR; //1
typedef wchar_t					WIDECHAR; //32(!)*/

#endif
#if defined(PLATFORM_32) || defined(GCC_COMPILER)
typedef uint32_t				uint32; //4 unsigned int
typedef int32_t			        int32;  //4 signed int
typedef uint64_t				uint64; //8 unsigned long long int
typedef int64_t					int64;  //8 signed long long int 
typedef uint16_t	            uint16; //2 unsigned short  
typedef int16_t                 int16;  //2 signed short
typedef int8_t					int8;   //1 char
typedef uint8_t			        uint8;  //1 unsigned char
typedef uintptr_t			    UINTPTR;
typedef size_t					SIZE_T;
typedef char					ASCICHAR; //1
typedef wchar_t					WIDECHAR; //16

#endif

#endif
