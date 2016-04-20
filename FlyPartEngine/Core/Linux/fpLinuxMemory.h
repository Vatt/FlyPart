#pragma once
#ifndef _FP_WINDOWS_MEMORY_
#define _FP_WINDOWS_MEMORY_
#include "../GenericPlatform/Memory/fpPlatformMemory.h"

class fpLinuxMemory : public fpPlatformMemory
{
public:
	fpLinuxMemory();
	inline void* SystemAlloc(size_t size) override;
	inline void SystemFree(void* ptr) override;
	inline void UpdateMemoryStats() override;
	inline void* MemMove(void* Dest, const void* Src, size_t size) override;
	inline int32 MemCmp(void* const Buf1, const void* Buf2, size_t size) override;
	inline void  MemSwap(void* ptr1, void* ptr2, size_t size) override;
};
#endif
