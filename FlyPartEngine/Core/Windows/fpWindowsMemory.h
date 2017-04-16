#pragma once
#ifndef _FP_WINDOWS_MEMORY_
#define _FP_WINDOWS_MEMORY_
#include "../GenericPlatform/Memory/fpPlatformMemory.h"

class fpWindowsPlatformMemory : public fpGenericMemory
{
public:

	static void* SystemAlloc(SIZE_T size);
	static void SystemFree(void* ptr,SIZE_T size);
	static void UpdateMemoryStats();
	static void* MemMove(void* Dest, const void* Src, size_t size);
	static int32 MemCmp(void* const Buf1, const void* Buf2, size_t size);
	static void  MemSwap(void* ptr1, void* ptr2, size_t size);
	static void*  MemCopy(void* dest, const void* src, SIZE_T size);
	static void*  MemSet(void* dest, uint8 value, SIZE_T count);
};
typedef fpWindowsPlatformMemory fpPlatformMemory;
#endif
