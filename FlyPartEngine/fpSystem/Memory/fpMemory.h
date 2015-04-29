#pragma once
#ifndef _FP_MEMORY_
#define	_FP_MEMORY_

#include "fpMemoryStats.h"

class fpPlatformMemory
{

public:
	fpPlatformMemory();
	virtual void* SystemAlloc(size_t size) = 0;
	virtual void SystemFree(void* ptr) = 0;
	virtual void UpdateMemoryStats() = 0;

};

#endif
