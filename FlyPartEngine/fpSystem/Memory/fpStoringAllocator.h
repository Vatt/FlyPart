#ifndef _FP_STORING_ALLOCATOR_
#define _FP_STORING_ALLOCATOR_
#include <stddef.h>
#include "fpAllocator.h"
#include "../fpSystemInterface.h"
class fpStoringAllocator: public fpAllocator
{
    enum {PAGES_IN_POOL = 8};
	
	struct MemPage{
		void* firstFreePtr;
        void* firstPtr;
		uint32 used;
		uint32 avail;
    };

    struct MemPool
    {
		uint32 pageSize;
		uint32 granularity;
        uint32 total;
        uint32 used;
        uint32 avail;
	
		MemPool()
		{
			 pageSize = fpMemoryStats::PageSize();
			 granularity = fpMemoryStats::Granularity();
		}
        void AllocNewPage()
        {

			//MemPage* newPage = (MemPage*)fpMemorySystem::PlatformMemory()->SystemAlloc(pageSize);
        }
		void link(MemPage* after, MemPage* target)
		{
		
		}
		void unlink(MemPage* target)
		{

		}
    };

public:
	fpStoringAllocator(fpPlatformMemory* impl) :fpAllocator(impl)
    {

    }

    virtual void* allocate(size_t size);
    virtual void  free(void* ptr);
private:

private:
	

};


#endif
