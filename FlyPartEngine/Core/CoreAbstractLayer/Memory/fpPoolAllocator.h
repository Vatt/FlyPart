#ifndef _FP_POOL_ALLOCATOR_
#define _FP_POOL_ALLOCATOR_
#include <stddef.h>
#include "fpAllocator.h"
#include "../../GenericPlatform/fpPlatform.h"
#include <new>

#include <cstdint>

class fpPoolAllocator
{
private:
    enum {PAGES_IN_POOL = 1}; //FIXIT: testing value, set 16
	
	struct FreeMem
	{
		FreeMem* next;
	};
/*32 byte pool structure*/
    struct MemPool
    {
		FreeMem* freeMem;
		void* ptr;
        uint32 used;
		uint32 total;		
		uint64 ForAllign;
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
		/*первые 32 байта информация о самом пуле*/
		new(memory)MemPool();

		pool->ptr = (void*)((uint8)memory + sizeof(MemPool));
		pool->total = fpMemory::Stats.PageSize * PAGES_IN_POOL - sizeof(MemPool);
		pool->used = 0;

		return pool;
	}
public:
    fpPoolAllocator()
    {
		
    }

    virtual void* allocate(size_t size);
    virtual void  free(void* ptr);


private:
	

};


#endif
