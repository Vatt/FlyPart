
#ifndef _FP_ALLOCATOR_
#define _FP_ALLOCATOR_
#include "../../GenericPlatform/fpPlatform.h"
#include "fpHeapInterface.h"
class fpMemorySystem;
class fpHeapInterface;
class fpAllocatorInterface
{
protected:
    fpHeapInterface* _heap;
public:
	fpAllocatorInterface(fpHeapInterface* heap) :_heap(heap)
	{}
	virtual void* Allocate(SIZE_T size) = 0;
	virtual void Free(void *ptr, SIZE_T size) = 0;
	virtual void* Realloc(void* ptr, SIZE_T size) = 0;
	virtual ~fpAllocatorInterface() {}
};
#endif
