
#ifndef _FP_ALLOCATOR_
#define _FP_ALLOCATOR_
#include "fpMemory.h"
class fpAllocator
{
public:
	fpAllocator();
	virtual ~fpAllocator();
	virtual void* allocate(size_t size) = 0;
	virtual void  free(void* ptr) = 0;
public:
	//fpPlatformMemory* platform;
};
#endif
