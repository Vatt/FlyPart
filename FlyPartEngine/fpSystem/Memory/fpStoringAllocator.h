#ifndef _FP_STORING_ALLOCATOR_
#define _FP_STORING_ALLOCATOR_
#include "fpAllocator.h"
#include <stddef.h>
class fpStoringAllocator: public fpAllocator
{
    struct MemPage{
        size_t used;
        size_t avail;
        void* beginPtr;
    };
    struct PagePool{
        MemPage* first;
        MemPage* last;
        MemPage** pages;
    };

public:
    virtual void* allocate(size_t size);
    virtual void  free(void* ptr);
private:

};


#endif
