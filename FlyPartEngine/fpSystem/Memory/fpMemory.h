#pragma once
#ifndef _FP_MEMORY_
#define	_FP_MEMORY_

#include "fpMemoryStats.h"
#include "fpAllocator.h"


class fpPlatformMemory
{
private:
	fpAllocator* _allocator;
public:
	fpPlatformMemory(fpAllocator* default) :_allocator(default){}
	virtual void* SystemAlloc(size_t size) = 0;
	virtual void SystemFree(void* ptr) = 0;
	virtual fpAllocator* DefaultAllocator(){ return _allocator; }
	virtual void UpdateMemoryStats() = 0;

};

#endif