#ifndef _FP_STORING_ALLOCATOR_
#define _FP_STORING_ALLOCATOR_
#include <stddef.h>
#include "fpAllocator.h"
class fpStoringAllocator: public fpAllocator
{
    enum {PAGES_IN_POOL = 4};
	
	struct MemPage{
		char* firstFreePtr;
        void* firstPtr;
		uint32 used; 
		uint32 avail;
    };
	struct FreeMem
	{

	};
    struct MemPool
    {
		uint32 pageSize;
        uint32 total;
        uint32 used;
        uint32 avail;
		uint16 pageIndex;
		
		MemPage* pages[];
		MemPool()
		{
			 pageSize = fpMemoryStats::PageSize();
			 for (int16 index = 0;index < PAGES_IN_POOL;index++)
			 {
				 pages[index] = (MemPage*)platform->SystemAlloc(sizeof(MemPage));
				 pages[index]->avail = pageSize;
				 pages[index]->firstPtr = platform->SystemAlloc(pageSize);
				 pages[index]->firstFreePtr = (char*)pages[index]->firstPtr;
				 pages[index]->used = 0;
			 }
			 pageIndex = 0;
			 total = pageSize * PAGES_IN_POOL;
			 used = 0;
			 avail = total;
		}
		void* getMem(uint32  size)
		{
			void* retPtr = nullptr;
			if (pages[pageIndex]->avail >= size)
			{
				retPtr =  pages[pageIndex]->firstFreePtr;
				pages[pageIndex]->used += size;
				pages[pageIndex]->avail -= size;
				pages[pageIndex]->firstFreePtr += size;
			}
			if (++pageIndex < PAGES_IN_POOL)
			{
				retPtr = pages[pageIndex]->firstFreePtr;
				pages[pageIndex]->used += size;
				pages[pageIndex]->avail -= size;
				pages[pageIndex]->firstFreePtr += size;
			}
			return retPtr;
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
