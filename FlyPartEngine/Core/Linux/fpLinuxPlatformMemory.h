
#ifndef _FP_LINUX_MEMORY_
#define _FP_LINUX_MEMORY_
#include "../GenericPlatform/Memory/fpPlatformMemory.h"


class fpLinuxPlatformMemory : public fpPlatformMemory
{
public:
	static void* SystemAlloc(size_t size);
	static void SystemFree(void* ptr);
	static void UpdateMemoryStats();
	static void* MemMove(void* Dest, const void* Src, size_t size);
	static int32 MemCmp(void* const Buf1, const void* Buf2, size_t size);
	static void  MemSwap(void* ptr1, void* ptr2, size_t size);
};
typedef fpLinuxPlatformMemory fpMemory;

#endif
