
#ifndef _FP_ALLOCATOR_
#define _FP_ALLOCATOR_
#include "../../GenericPlatform/fpPlatform.h"
#include "fpHeapInterface.h"

class fpHeapInterface;
class fpAllocatorInterface
{
protected:
    fpHeapInterface* HeapPtr;
public:
	fpAllocatorInterface(fpHeapInterface* heap) :HeapPtr(heap)
	{}
	virtual void* Allocate(SIZE_T size) = 0;
	virtual void Free(void *ptr, SIZE_T size) = 0;
	virtual void* Realloc(void* ptr, SIZE_T size) = 0;
	virtual ~fpAllocatorInterface() {}
};
#endif
