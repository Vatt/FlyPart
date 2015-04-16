#ifndef _FP_STORING_ALLOCATOR_
#define _FP_STORING_ALLOCATOR_
#include <stddef.h>
#include "fpAllocator.h"
#include "../fpSystemInterface.h"
class fpStoringAllocator: public fpAllocator
{
    enum {PAGES_IN_POOL = 4};
    struct MemPageInfo{
        uint32 used;
        uint32 avail;
        MemPage* ptr;
    };
    struct MemPage{
        uint32 size;
        void* beginPtr;
    };
    struct MemPool
    {
        uint32 total;
        uint32 used;
        uint32 avail;
        MemPageInfo** table;
        void AllocNewPage()
        {
            MemPage* newPage = fpSystem::Memory()->GlobalMemory()->SystemAlloc(pageSize);
            MemPageInfo* newPageInfo;
        }
    };

public:
    fpStoringAllocator()
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
