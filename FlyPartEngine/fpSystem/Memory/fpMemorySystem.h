
#pragma once
#ifndef _FP_MEMORY_SYSTEM
#	define _FP_MEMORY_SYSTEM
#include "fpMemory.h"
#include "fpAllocator.h"
class fpMemorySystem
{
private:
    static fpPlatformMemory* platformMemory;
    static fpAllocator* gAllocator;
	static bool isInit;
public:
	static void					Init(fpPlatformMemory* memory, fpAllocator* gAllocator);
    static fpPlatformMemory*    PlatformMemory()			   { return platformMemory; }
    static fpAllocator*			GlobalAllocator()			   { return gAllocator; }
};



#endif
