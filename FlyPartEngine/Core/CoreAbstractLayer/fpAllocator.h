
#ifndef _FP_ALLOCATOR_
#define _FP_ALLOCATOR_
#include "../GenericPlatform/Memory/fpPlatformMemory.h"
#include "../GenericPlatform/Memory/fpMemorySystem.h"
#include "../../fpCommon/typedefs.h"
class fpMemorySystem;
class fpAllocator
{

public:
	virtual ~fpAllocator();
	virtual void* allocate(size_t size) = 0;
	virtual void  free(void* ptr) = 0;
protected:
    friend class fpMemorySystem;
    static fpPlatformMemory* platform;
};
fpPlatformMemory* fpAllocator::platform = fpMemorySystem::PlatformMemory();
#endif
