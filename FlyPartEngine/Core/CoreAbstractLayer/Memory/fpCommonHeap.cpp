#include "fpCommonHeap.h"
#include <new>
const uint32 POOL_SIZES[9] = { 16,24,32,64,128,256,512,1024,2048 };

fpCommonHeap::PoolList::PoolList(uint32 block_size)
{
    this->BlockSize = block_size;
    this->BlocksNumPerPool = ((fpMemory::Stats.PageSize * PAGES_IN_POOL)- sizeof(PoolHeader))/this->BlockSize;
    for (uint32 index = 0; index < START_POOL_COUNT;index++)
    {
        if (!this->Front)
        {
            Front = makeNewPool();
        }else{
            LinkPoolToFront(makeNewPool());
        }
        this->ListFreeBlocksCount += this->BlocksNumPerPool;
    }
    this->ListFreeMemory = Front->FreeMem;
    

}
FORCEINLINE void fpCommonHeap::PoolList::LinkPoolToFront(PoolHeader *target)
{
    target->Next = this->Front;
    this->Front = target;
    this->PoolCount++;
    this->ListFreeBlocksCount+=this->BlocksNumPerPool;
}
FORCEINLINE void fpCommonHeap::PoolList::ExtendPoolsCount(uint32 num)
{
    PoolHeader* pools = makeNewPool();
    PoolHeader* prev_pool = pools;
    for(uint32 i = 0;i<num-1;i++)
    {
        PoolHeader* new_pool  = makeNewPool();
        prev_pool->Next = new_pool;
        prev_pool = new_pool;
    }
    LinkPoolToFront(pools);
    this->ListFreeBlocksCount += (this->BlocksNumPerPool*num);
}

FORCEINLINE void* fpCommonHeap::PoolList::GetPoolRawData(PoolHeader *pool)const
{
	return (void*)((UINTPTR)pool + (UINTPTR)sizeof(PoolHeader));
}
FORCEINLINE void fpCommonHeap::PoolList::MapThePoolOfFreeBlocks(PoolHeader* pool)
{
	void* raw = this->GetPoolRawData(pool);
	SIZE_T size_alloc = fpMemory::Stats.PageSize * PAGES_IN_POOL;
	SIZE_T pool_size = size_alloc - sizeof(PoolHeader);
	FreeMemory* free_ptr = new(raw)FreeMemory;
	SIZE_T limit = (UINTPTR)((UINTPTR)pool + size_alloc);
	for (UINTPTR offset = (UINTPTR)free_ptr + pool->BlockSize;
		offset < limit;
		offset = offset + pool->BlockSize)
	{
		FreeMemory* ptr = new ((void*)offset)FreeMemory;
		FreeMemory* prev = (FreeMemory*)((UINTPTR)ptr - pool->BlockSize);
		prev->next = ptr;
	}
	pool->FreeMem = free_ptr;
}
fpCommonHeap::PoolHeader* fpCommonHeap::PoolList::makeNewPool()
{
	PoolHeader* pool;
	SIZE_T size_alloc = fpMemory::Stats.PageSize * PAGES_IN_POOL;
    SIZE_T pool_size = size_alloc - sizeof(PoolHeader);
    uint32 blocks_count = pool_size / this->BlockSize;
	void* memory = fpMemory::SystemAlloc(size_alloc);

	/*первые 32 бита информация о самом пуле*/
	pool = new(memory)PoolHeader();
    pool->Next = nullptr;
	pool->BlockSize = this->BlockSize;
	/*void* pool_raw_ptr = GetPoolRawData(nullptr);
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
	*/
	this->MapThePoolOfFreeBlocks(pool);
	return pool;
}
FORCEINLINE void* fpCommonHeap::PoolList::PoolAllocate()
{
    void* free_block = nullptr;
    PoolHeader* iterator = this->Front;
    if (!this->ListFreeMemory)
    {
        do{
            if (iterator->Next&&iterator->Next->FreeMem!=nullptr)
            {
                this->ListFreeMemory = iterator->FreeMem->next;
                free_block = iterator->FreeMem;
                return free_block;
            }
            iterator = iterator->Next;
        }while(iterator->Next);
        ExtendPoolsCount(static_cast<uint32>(this->PoolCount*1.3));
    }
    free_block = this->ListFreeMemory;
    this->ListFreeMemory = this->ListFreeMemory->next;
    this->ListFreeBlocksCount--;
    return free_block;
}
FORCEINLINE void fpCommonHeap::PoolList::PoolFree(void *inPtr)
{
    FreeMemory* temp = this->ListFreeMemory;
    this->ListFreeMemory = static_cast<FreeMemory*>(inPtr);
    this->ListFreeMemory->next = temp;
    this->ListFreeBlocksCount++;
}

FORCEINLINE uint32 fpCommonHeap::PoolList::CalcRealNumFreeBlocks() const
{
    uint32 count = 0;
    FreeMemory* free_mem_iterator = this->ListFreeMemory;
    PoolHeader* pool_iterator = this->Front;
    if (free_mem_iterator == nullptr)
    {
        free_mem_iterator = pool_iterator->Next->FreeMem;
        pool_iterator = pool_iterator->Next;
    }
    while(free_mem_iterator != nullptr)
    {
        free_mem_iterator = free_mem_iterator->next;
        count++;
        if (free_mem_iterator == nullptr)
        {
            free_mem_iterator = pool_iterator->Next->FreeMem;
            pool_iterator = pool_iterator->Next;
        }
    }

    return count;
}
FORCEINLINE bool fpCommonHeap::PoolList::ValidateList()const
{
    uint32 real_free_blocks_count = this->CalcRealNumFreeBlocks();
    return real_free_blocks_count == this->ListFreeBlocksCount;
}
FORCEINLINE void fpCommonHeap::PoolList::CleanupList()
{
	PoolHeader* iterator = this->Front;
	this->ListFreeBlocksCount = 0;
	while (iterator != nullptr)
	{
		CleanupPool(iterator);
		this->ListFreeBlocksCount += this->BlocksNumPerPool;
		iterator = iterator->Next;
	}
}
FORCEINLINE void fpCommonHeap::PoolList::CleanupPool(PoolHeader* pool)
{
	this->MapThePoolOfFreeBlocks(pool);
}

void fpCommonHeap::PoolList::ListDestroy()
{
	PoolHeader* iterator = this->Front;
	this->ListFreeBlocksCount = 0;
	while (iterator != nullptr)
	{
		PoolHeader* temp = iterator->Next;
		this->PoolDestroy(iterator);
		iterator = temp;
	}
}

void fpCommonHeap::PoolList::PoolDestroy(PoolHeader * pool)
{
	fpMemory::SystemFree((void*) pool);
}


fpAllocatorInterface *fpCommonHeap::MakeDefaultAllocator() {
    return  new CommonAllocator(this);
}

fpCommonHeap::CommonAllocator::CommonAllocator(fpCommonHeap* heap)
        :fpAllocatorInterface((fpHeapInterface*) heap),TableIndex(NO_INIT_TABLE_INDEX)
{}
void* fpCommonHeap::CommonAllocator::Allocate(SIZE_T size)
{
	return nullptr;
}

void fpCommonHeap::HeapInit()
{
	for (uint8 i = 0; i < 9;i++)
	{
		PoolTable[i] = new PoolList(POOL_SIZES[i]);
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
	for (uint8 i = 0; i < 9;i++)
	{
		this->PoolTable[i]->CleanupList();
	}
}

void* fpCommonHeap::HeapRealloc(void * target, SIZE_T size)
{
	return nullptr;
}
void fpCommonHeap::HeapDestroy()
{
	for (uint8 i = 0; i < 9; i++)
	{
		this->PoolTable[i]->ListDestroy();
	}
}


bool fpCommonHeap::ValidateHeap()
{
	for (uint16 i = 0;i<9;i++)
	{
		if (!PoolTable[i]->ValidateList())
		{
			return false;
		}
	}
	return true;
}
fpCommonHeap::~fpCommonHeap()
{
	this->HeapDestroy();
}