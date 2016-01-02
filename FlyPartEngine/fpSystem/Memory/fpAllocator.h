
#ifndef _FP_ALLOCATOR_
#define _FP_ALLOCATOR_
#include "fpMemory.h"
#include "../../fpCommon/typedefs.h"
class fpMemorySystem;
class fpAllocator
{

public:
    /*fpAllocator(fpPlatformMemory* impl){
    //	platform = impl;
    }*/
	virtual ~fpAllocator();
	virtual void* allocate(size_t size) = 0;
	virtual void  free(void* ptr) = 0;
protected:
    friend class fpMemorySystem;
    static fpPlatformMemory* platform;
};
#endif
