#ifndef _FP_POOL_ALLOCATOR_
#define _FP_POOL_ALLOCATOR_
#include <stddef.h>
#include "fpAllocator.h"
#include "../GenericPlatform/fpPlatform.h"
#include <new>

#include <cstdint>

class fpPoolAllocator: public fpAllocator
{
private:
    enum {PAGES_IN_POOL = 1}; //FIXIT: testing value, set 16
	
	struct FreeMem
	{
		FreeMem* next;
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
		void* memory = fpMemory::SystemAlloc(fpMemory::Stats.PageSize* PAGES_IN_POOL);
		new(memory)MemPool();

		pool->ptr = (void*)((int8)memory + sizeof(MemPool));
		pool->total = fpMemory::Stats.PageSize * PAGES_IN_POOL - sizeof(MemPool);
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
