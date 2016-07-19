
#pragma once
#ifndef _FP_MEMORY_SYSTEM
#	define _FP_MEMORY_SYSTEM
#include "fpPlatformMemory.h"
#include "../defines.h"
class fpMemorySystem
{
#if defined(PLATFORM_WINDOWS) 
		friend class fpWindowsMemory;
#endif 
#if defined(PLATFORM_LINUX) 
		friend class fpLinuxPlatformMemory;
#endif	
private:
    static fpPlatformMemory* platformMemory;
//    static fpAllocator* gAllocator;
	static bool isInit;
public:
	//static void					Init(fpPlatformMemory* memory, fpAllocator* gAllocator);
    static fpPlatformMemory*    PlatformMemory()			   { return platformMemory; }
   // static fpAllocator*			GlobalAllocator()			   { return gAllocator; }
};



#endif
