#ifndef _FP_POOL_ALLOCATOR_
#define _FP_POOL_ALLOCATOR_
#include <stddef.h>
#include "fpAllocator.h"
#include <new>
class fpPoolAllocator: public fpAllocator
{
private:
    enum {PAGES_IN_POOL = 1};
	
	struct FreeMem
	{
		FreeMem* next;
		uint32 numFreeBlocks;
	};

    struct MemPool
    {
        uint32 used;
		uint32 total;		
		FreeMem* freeMem;
		void* ptr;
    };
	struct PoolTable
	{
		MemPool* firstPool;
		MemPool* lastUsedPool;
		uint32 elemSize;
	};
	struct PoolNode
	{
		uintptr_t key;
		MemPool* pool;
		PoolNode* next;
		PoolNode* prev;
	};
private:
	MemPool* makeNewPool()
	{
		MemPool* pool;
		void* memory = platform->SystemAlloc(fpMemoryStats::PageSize()* PAGES_IN_POOL);
		new(memory)MemPool();

		pool->ptr = (void*)((char)memory + sizeof(MemPool));//todo: this is shit
		pool->total = fpMemoryStats::PageSize()* PAGES_IN_POOL - sizeof(MemPool);
		pool->used = 0;
		return pool;
	}
public:
    fpPoolAllocator() :fpAllocator()
    {
		
    }

    virtual void* allocate(size_t size);
    virtual void  free(void* ptr);


private:
	

};


#endif