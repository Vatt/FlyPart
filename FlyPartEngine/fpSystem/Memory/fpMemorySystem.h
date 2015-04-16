
#pragma once
#ifndef _FP_MEMORY_SYSTEM
#	define _FP_MEMORY_SYSTEM
#include "fpMemory.h"

class fpMemorySystem
{
private:
	static fpPlatformMemory* globalMem;
	static fpAllocator* globalAllocator;
	static bool isInit;
public:
	static void					Init(fpPlatformMemory* memory, fpAllocator* gAllocator);
	static fpPlatformMemory*    PlatformMemory()			   { return globalMem; }
	static fpAllocator*			GlobalAllocator()			   { return globalAllocator; }
};



#endif
