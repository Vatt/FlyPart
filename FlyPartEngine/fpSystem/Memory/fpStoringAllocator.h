#ifndef _FP_STORING_ALLOCATOR_
#define _FP_STORING_ALLOCATOR_
#include <stddef.h>
#include "fpAllocator.h"
#include "../fpSystemInterface.h"
class fpStoringAllocator: public fpAllocator
{
    enum {PAGES_IN_POOL = 4};
	    struct MemPage{
        uint32 size;
        void* beginPtr;
    };
	struct MemPageInfo{
        uint32 used;
        uint32 avail;
        MemPage* ptr;
    };

    struct MemPool
    {
        uint32 total;
        uint32 used;
        uint32 avail;
        MemPageInfo** table;
        void AllocNewPage()
        {
            //MemPage* newPage = platform->
            //MemPageInfo* newPageInfo;
        }
		void link(MemPageInfo* after, MemPageInfo* target);
    };

public:
	fpStoringAllocator(fpPlatformMemory* impl) :fpAllocator(impl)
    {
        pageSize = fpMemoryStats::PageSize();
        granularity = fpMemoryStats::Granularity();
    }

    virtual void* allocate(size_t size);
    virtual void  free(void* ptr);
private:


private:
    uint32 pageSize;
    uint32 granularity;

};


#endif
