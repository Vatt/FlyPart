#pragma once
#ifndef _FP_PLATFORM_MEMORY_
#define	_FP_PLATFORM_MEMORY_
#include "../typedefs.h"
#include "../defines.h"
class fpPlatformMemory
{

public:
	FORCEINLINE static void* SystemAlloc(size_t size);
	FORCEINLINE static void SystemFree(void* ptr);
	FORCEINLINE static void UpdateMemoryStats();
	FORCEINLINE static void* MemMove(void* Dest, const void* Src, size_t size);
	FORCEINLINE static int32 MemCmp( void* const Buf1, const void* Buf2, size_t size);
	FORCEINLINE static void  MemSwap(void* ptr1, void* ptr2, size_t size);

};

#endif
