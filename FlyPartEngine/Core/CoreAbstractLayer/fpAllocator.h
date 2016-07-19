
#ifndef _FP_ALLOCATOR_
#define _FP_ALLOCATOR_
#include "../GenericPlatform/fpPlatform.h"
class fpMemorySystem;
class fpAllocator
{

public:
	virtual ~fpAllocator();
	virtual void* allocate(size_t size) = 0;
	virtual void  free(void* ptr) = 0;
};

#endif
