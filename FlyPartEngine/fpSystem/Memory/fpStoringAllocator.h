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
		MemPage* pages[];
		MemPool()
		{
			 pageSize = fpMemoryStats::PageSize();
			 granularity = fpMemoryStats::Granularity();
			// pages[] = (MemPage*)platform->SystemAlloc(sizeof(MemPage)*PAGES_IN_POOL);
			 for (int16 index = 0;index < PAGES_IN_POOL;index++)
			 {
				 pages[index] = (MemPage*)platform->SystemAlloc(sizeof(MemPage));
				 pages[index]->avail = pageSize;
				 pages[index]->firstPtr = platform->SystemAlloc(pageSize);
				 pages[index]->firstFreePtr = pages[index]->firstPtr;
				 pages[index]->used = 0;
			 }
		}

    };

public:
    fpStoringAllocator() :fpAllocator()
    {

    }

    virtual void* allocate(size_t size);
    virtual void  free(void* ptr);
private:

private:
	

};


#endif
