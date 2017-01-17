#include "fpCommonHeap.h"
#include <new>

void fpCommonHeap::HeapInit()
{
	for (uint32 index = 0; index < START_POOL_COUNT;index++)
	{
        makeNewPool(POOL_SIZES[index]);
	}
}

void * fpCommonHeap::HeapAlloc(SIZE_T size)
{
	return nullptr;
}

void fpCommonHeap::HeapFree(void * target, SIZE_T size)
{
}

void fpCommonHeap::HeapCleanup()
{
	
}

void fpCommonHeap::HeapDestroy()
{
}

void* fpCommonHeap::HeapRealloc(void * target, SIZE_T size)
{
	return nullptr;
}

void* fpCommonHeap::PoolList::getPoolRawData(Pool* pool)
{
	return (void*)((UINTPTR)pool + (UINTPTR)sizeof(Pool));
}

fpCommonHeap::Pool* fpCommonHeap::PoolList::makeNewPool(uint32 inBlockSize)
{
	Pool* pool;
	uint32 size_alloc = fpMemory::Stats.PageSize * PAGES_IN_POOL;
	uint32 pool_size = size_alloc - sizeof(Pool);
	uint32 blocks_count = pool_size / inBlockSize;
	void* memory = fpMemory::SystemAlloc(size_alloc);

	/*первые 32 байта информация о самом пуле*/
	pool = new(memory)Pool();
	pool->BlockSize = inBlockSize;
	pool->FreeBlocks = blocks_count;

	void* pool_raw_ptr = getPoolRawData(pool);	
	FreeMemory* free_ptr = new(pool_raw_ptr)FreeMemory;
	SIZE_T limit =(UINTPTR)((UINTPTR)pool+size_alloc);
	for (UINTPTR offset = (UINTPTR)free_ptr + pool->BlockSize;
		offset < limit;
		offset = offset  + pool->BlockSize)
	{
		FreeMemory* ptr = new ((void*)offset)FreeMemory;
		FreeMemory* prev = (FreeMemory*)((UINTPTR)ptr - pool->BlockSize);
		prev->next = ptr;
	}
	pool->FreeMem = free_ptr;
	//uint32 count = 0;
	//for (FreeMemory* mem = pool->FreeMem; mem != nullptr;mem = mem->next)
	//{
	//	count++;
	//}
	return pool;
}
FORCEINLINE void* fpCommonHeap::PoolList::inPoolAllocate(Pool* inPool)
{
	//FIXIT: Заглушка
	if (inPool->FreeBlocks == 0)
	{
		inPool->FreeMem = nullptr;
		return nullptr;
	}

    FreeMemory* new_free_mem = inPool->FreeMem->next;
    void* allocated = inPool->FreeMem;
    inPool->FreeMem = new_free_mem;
    inPool->FreeBlocks -= 1;
    return allocated;
}
FORCEINLINE void  fpCommonHeap::PoolList::inPoolDeallocate(Pool* inPool, void* inPtr)
{
    FreeMemory* new_free_mem = new(inPtr)FreeMemory;
    new_free_mem->next = inPool->FreeMem;
    inPool->FreeMem  = new_free_mem;
    inPool->FreeBlocks += 1;

}
