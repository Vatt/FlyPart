#pragma once
#ifndef _FP_WINDOWS_MEMORY_
#define _FP_WINDOWS_MEMORY_
#include "../GenericPlatform/Memory/fpPlatformMemory.h"

class fpWindowsPlatformMemory : public fpPlatformMemory
{
public:

	static FORCEINLINE void* SystemAlloc(size_t size);
	static FORCEINLINE void SystemFree(void* ptr);
	static FORCEINLINE void UpdateMemoryStats();
	static FORCEINLINE void* MemMove(void* Dest, const void* Src, size_t size);
	static FORCEINLINE int32 MemCmp(void* const Buf1, const void* Buf2, size_t size);
	static FORCEINLINE void  MemSwap(void* ptr1, void* ptr2, size_t size);
};
typedef fpWindowsPlatformMemory fpMemory;
#endif
