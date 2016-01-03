#ifndef _TYPE_DEFS_
#define _TYPE_DEFS_
#pragma once
#include "defines.h"
#if defined (PLATFORM_64) && defined(PLATFORM_WINDOWS)
typedef unsigned int            uint32; //4
typedef int                     int32;  //4
typedef unsigned long long int  uint64; //8
typedef long long int           int64;  //8
typedef unsigned short          uint16; //2
typedef short                   int16;  //2

#endif
#if defined (PLATFORM_64) && defined(PLATFORM_LINUX)
typedef unsigned int            uint32; //4
typedef int                     int32;  //4
typedef unsigned long long int  uint64; //8
typedef long long int           int64;  //8
typedef unsigned short          uint16; //2
typedef short                   int16;  //2

#endif
#if defined(PLATFORM_32) || defined(GCC_COMPILER)
typedef unsigned int            uint32; //4
typedef int                     int32;  //4
typedef unsigned long long int  uint64; //8
typedef long long int           int64;  //8
typedef unsigned short          uint16; //2
typedef short                   int16;  //2

#endif

#endif
