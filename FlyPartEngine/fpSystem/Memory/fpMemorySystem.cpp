#include "fpMemorySystem.h"

void fpMemorySystem::Init(fpPlatformMemory* memory, fpAllocator* gAllocator)
{
	globalMem = memory; 
	isInit = true;
	globalAllocator = gAllocator;
}