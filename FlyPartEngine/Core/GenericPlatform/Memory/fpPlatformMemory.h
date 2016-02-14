#pragma once
#ifndef _FP_PLATFORM_MEMORY_
#define	_FP_PLATFORM_MEMORY_
#include "../../../fpCommon/typedefs.h"
class fpPlatformMemory
{

public:
	inline virtual ~fpPlatformMemory() {};
	inline virtual void* SystemAlloc(size_t size) = 0;
	inline virtual void SystemFree(void* ptr) = 0;
	inline virtual void UpdateMemoryStats() = 0;
	inline virtual void* MemMove(void* Dest, const void* Src, size_t size) = 0;
	inline virtual int32 MemCmp( void* const Buf1, const void* Buf2, size_t size) = 0;
	inline virtual void  MemSwap(void* ptr1, void* ptr2, size_t size) = 0;

};

#endif
