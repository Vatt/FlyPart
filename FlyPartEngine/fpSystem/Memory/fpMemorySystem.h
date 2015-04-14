
#pragma once
#ifndef _FP_MEMORY_SYSTEM
#	define _FP_MEMORY_SYSTEM
#include "fpMemory.h"

class fpMemorySystem
{
private:
	static fpPlatformMemory* _globalMem;
public:
	static void					Init(fpPlatformMemory* memory) { _globalMem = memory; }
	static fpPlatformMemory*    GlobalMemory()				   { return _globalMem; }
};



#endif
