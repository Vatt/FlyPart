#include "fpCommonHeap.h"
#include "../../fpCommon/CommonHelperFunctions.h"
#include <new>

const static uint8 LENGTH_TABLE = 45;
const static uint32 POOL_SIZES[45] = { 16, 32, 48, 64, 80, 96, 112, 128, 160, 192, 224, 256, 
									   288, 320, 384, 448, 496, 560, 640, 704, 768,896, 1008,
									   1168, 1360, 1632, 2032, 2336, 2720, 3264, 4080, 4368, 
									   4672, 5040, 5456, 5952, 6544, 7280, 8176, 9360, 10912, 
									   13104, 16368, 21840, 32752 };
//FIXIT: Заглушка
const static SIZE_T DefaultAlign = 16; 
//FIXIT: Заглушка
FORCEINLINE static SIZE_T ALIGN(SIZE_T size)
{
    SIZE_T test = size%DefaultAlign;
    return test == 0 ? size : (size = size + (DefaultAlign - test));
}
struct fpCommonHeap::FreeMemory
{
	FreeMemory* next;	
	FORCEINLINE FreeMemory() :next(nullptr)
	{}
#ifdef PLATFORM_32
	/* Выравнивание до 8 байт на 32 битной платформе*/
	uint32 _allign;
#endif		
};

struct fpCommonHeap::PoolHeader
{
	PoolHeader* Prev;
	PoolHeader* Next;
	static void LinkPoolAfter(PoolHeader* after,PoolHeader* target)
	{
		//TODO: следующий может быть нулевым указателем
		PoolHeader* temp_next = after->Next;
		if (temp_next != nullptr)
		{
			temp_next->Prev = target;
			target->Next = temp_next;
		}		
		
		after->Next = target;
		target->Prev = after;		
	}
	static void LinkPoolBefore(PoolHeader* before, PoolHeader* target)
	{
		//TODO: предыдущий может быть нулевым указателем
		PoolHeader* temp_prev = before->Prev;
		if (temp_prev != nullptr)
		{
			temp_prev->Next = target;
			target->Prev = temp_prev;
		}
		target->Next = before;		
		before->Prev = target;
		
	}
#ifdef PLATFORM_32
	/* Выравнивание до 16 байт на 32  битной платформе*/
	uint32 align[2];
#endif

};
class fpCommonHeap::PoolList
{
public:
	struct TempPoolData {
		PoolHeader* header;
		FreeMemory* first;
		FreeMemory* last;
		FORCEINLINE TempPoolData() :header(nullptr), first(nullptr), last(nullptr)
		{}
		FORCEINLINE TempPoolData(PoolHeader* _header,FreeMemory* _first, FreeMemory* _last)
			:header(_header),first(_first), last(_last)
		{}
	};

	/*
	* Global pointer of free memory blocks in this list
	*/
	FreeMemory* ListFreeMemory;
	PoolHeader*  Front;
	uint32 TableIndex;
	uint32 BlockSize;
	uint32 PoolCount;
	uint32 BlocksNumPerPool;
	uint32 ListFreeBlocksCount;
	PoolList() {};
	PoolList(uint32 block_size, uint32 table_index);
	const TempPoolData&& makeNewPool();
	FORCEINLINE SIZE_T PoolSizeCalc();
	FORCEINLINE SIZE_T PoolDataSizeCalc();
	FORCEINLINE const TempPoolData&&  MapThePoolOfFreeBlocks(PoolHeader* pool);
	FORCEINLINE void* GetPoolRawData(PoolHeader *pool)const;
	FORCEINLINE void* PoolAllocate();
	FORCEINLINE void  PoolFree(void *inPtr);
	FORCEINLINE void  ExtendPoolsCount();
	FORCEINLINE void  CleanupList();
	FORCEINLINE void  CleanupPool(PoolHeader* pool);
	FORCEINLINE void  ListDestroy();
	FORCEINLINE void  PoolDestroy(PoolHeader* pool);
	/*
	* This method only for validate list;
	* */
	FORCEINLINE uint32 CalcRealNumFreeBlocks()const;
	FORCEINLINE uint32 CalcRealNumPools()const;
	/*
	* This method only for validate list;
	* */
	FORCEINLINE bool  ValidateList()const;


};



fpCommonHeap::PoolList::PoolList(uint32 block_size, uint32 table_index)
{
	static_assert(sizeof(PoolHeader) == 16, "PoolHeader size should be equal to 16");
	static_assert(sizeof(FreeMemory) <= 16, "FreeMemory size should be no more than 16");
    this->TableIndex = table_index;
    this->BlockSize = block_size;
	this->BlocksNumPerPool = this->PoolDataSizeCalc() / this->BlockSize;
	this->Front = nullptr;
	this->ListFreeBlocksCount = 0;
	this->PoolCount = 0;
	/*TempPoolData data[START_POOL_COUNT];
	for (uint32 i = 0; i < START_POOL_COUNT; i++)
	{
		data[i] = fpTemplate::Move(makeNewPool());
	}
	for (uint32 i = 1; i < START_POOL_COUNT; i++)
	{
		*&(data[i-1].last->next) = data[i].first;
		PoolHeader::LinkPoolAfter(data[i - 1].header, data[i].header);
	}
	this->ListFreeMemory = data[0].first;
	this->Front = data[0].header;*/	
	this->ExtendPoolsCount();
}
FORCEINLINE void fpCommonHeap::PoolList::ExtendPoolsCount()
{

	TempPoolData data[EXTEND_NUMBER];
	for (uint32 i = 0; i < EXTEND_NUMBER; i++)
	{
		data[i] = fpTemplate::Move(makeNewPool());
	}
	for (uint32 i = 1; i < EXTEND_NUMBER; i++)
	{
		*&(data[i - 1].last->next) = data[i].first;
		PoolHeader::LinkPoolAfter(data[i - 1].header, data[i].header);
	}
	this->ListFreeMemory = data[0].first;
	if (this->Front == nullptr)
	{
		this->Front = data[0].header;
	}
	else {
		PoolHeader::LinkPoolBefore(this->Front, data[EXTEND_NUMBER -1].header);
		this->Front = data[0].header;
	}	
}
FORCEINLINE SIZE_T fpCommonHeap::PoolList::PoolSizeCalc()
{
	return (fpMemory::Stats.PageSize * PAGES_IN_POOL);
}
FORCEINLINE SIZE_T fpCommonHeap::PoolList::PoolDataSizeCalc()
{
	return this->PoolSizeCalc() - sizeof(PoolHeader);
}
FORCEINLINE void* fpCommonHeap::PoolList::GetPoolRawData(PoolHeader *pool)const
{
	return (void*)((UINTPTR)pool + (UINTPTR)sizeof(PoolHeader));
}
FORCEINLINE const fpCommonHeap::PoolList::TempPoolData&& fpCommonHeap::PoolList::MapThePoolOfFreeBlocks(PoolHeader* pool)
{
	void* raw = this->GetPoolRawData(pool);
	SIZE_T pool_size  = PoolDataSizeCalc();
	FreeMemory* free_ptr = new(raw)FreeMemory;
	SIZE_T limit = (UINTPTR)((UINTPTR)pool + PoolDataSizeCalc());
	for (UINTPTR index = 1; index < this->BlocksNumPerPool; index++)
	{
		FreeMemory* ptr = new ((void*)((UINTPTR)raw+(UINTPTR)(index*this->BlockSize)))FreeMemory();
		FreeMemory* prev = (FreeMemory*)((UINTPTR)ptr - this->BlockSize);
		prev->next = ptr;
	}
	FreeMemory* last_ptr = (FreeMemory*)((UINTPTR)free_ptr + (this->BlocksNumPerPool-1)*this->BlockSize);
	return TempPoolData(pool,free_ptr,last_ptr);
}
const fpCommonHeap::PoolList::TempPoolData&& fpCommonHeap::PoolList::makeNewPool()
{
	PoolHeader* pool;
	SIZE_T size_alloc = PoolSizeCalc();
	void* memory = fpMemory::SystemAlloc(size_alloc);

	/*первые 16 бита информация о самом пуле*/
	pool = new(memory)PoolHeader();
    pool->Next = nullptr;
	pool->Prev = nullptr;
	this->PoolCount++;
	this->ListFreeBlocksCount += this->BlocksNumPerPool;
	return this->MapThePoolOfFreeBlocks(pool);
}

FORCEINLINE void* fpCommonHeap::PoolList::PoolAllocate()
{
    void* free_block = nullptr;
    PoolHeader* iterator = this->Front;
	/*TODO: тут возвожно не инициализированый указатель будет считаться валидным */
    if (!this->ListFreeMemory)
    {
        ExtendPoolsCount();//static_cast<uint32>(this->PoolCount*1.3)
    }
    free_block = this->ListFreeMemory;
    this->ListFreeMemory = this->ListFreeMemory->next;
    this->ListFreeBlocksCount--;
    return free_block;
}
FORCEINLINE void fpCommonHeap::PoolList::PoolFree(void* inPtr)
{
    FreeMemory* temp = this->ListFreeMemory;
    this->ListFreeMemory = static_cast<FreeMemory*>(inPtr);
    this->ListFreeMemory->next = temp;
    this->ListFreeBlocksCount++;
}

FORCEINLINE uint32 fpCommonHeap::PoolList::CalcRealNumFreeBlocks() const
{
    uint32 count = 0;
	FreeMemory* iterator = this->ListFreeMemory;
	while (iterator != nullptr)
	{
		iterator = iterator->next;
		count++;
	}
    return count;
}
FORCEINLINE uint32 fpCommonHeap::PoolList::CalcRealNumPools()const
{
	PoolHeader* iterator = this->Front;
	uint32 count = 0;
	while (iterator != nullptr)
	{
		iterator = iterator->Next;
		count++;
	}
	return count;
}
FORCEINLINE bool fpCommonHeap::PoolList::ValidateList()const
{
    uint32 real_free_blocks_count = this->CalcRealNumFreeBlocks();
	uint32 real_num_pools = this->CalcRealNumPools();
    return (real_free_blocks_count == this->ListFreeBlocksCount) && (real_num_pools==this->PoolCount);
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
    fpMemory::SystemFree((void *) pool, 0);
}



void fpCommonHeap::HeapInit()
{
	//PoolTable = new PoolList[LENGTH_TABLE];
	for (uint8 i = 0;i < LENGTH_TABLE;i++)
	{
		PoolTable[i] = new PoolList(POOL_SIZES[i], i);
	}
}

void * fpCommonHeap::HeapAlloc(SIZE_T size)
{
    SIZE_T aligned = ALIGN(size);
    for(uint8 i = 0;i<LENGTH_TABLE;i++)
    {
        if (aligned>=POOL_SIZES[i])
        {
            
		}
		else {
			void* ptr =  PoolTable[i]->PoolAllocate();
			return ptr;
		}
    }
    //FIXIT: Заглушка
	return nullptr;
}

void fpCommonHeap::HeapFree(void * target, SIZE_T size)
{
    SIZE_T aligned = ALIGN(size);
    for(uint8 i = 0;i<LENGTH_TABLE;i++)
    {
        if (aligned>=POOL_SIZES[i])
        {           
		}
		else {
			PoolTable[i]->PoolFree(target);
			return;
		}
    }
}

void fpCommonHeap::HeapCleanup()
{
	for (uint8 i = 0; i < LENGTH_TABLE;i++)
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
	for (uint8 i = 0; i < LENGTH_TABLE; i++)
	{
		this->PoolTable[i]->ListDestroy();
	}
}


bool fpCommonHeap::ValidateHeap()
{
	for (uint16 i = 0;i<LENGTH_TABLE;i++)
	{
		if (!PoolTable[i]->ValidateList())
		{
			return false;
		}
	}
	return true;
}
fpCommonHeap::fpCommonHeap() {

}
fpCommonHeap::~fpCommonHeap()
{
	this->HeapDestroy();
}

fpAllocatorInterface *fpCommonHeap::MakeDefaultAllocator() {
    return  new CommonAllocator(this);
}
struct fpCommonHeap::CommonAllocator::ListHashBucket {
	UINTPTR Index;
	ListHashBucket* Next;
	ListHashBucket* Prev;
	PoolList* List;
};
fpCommonHeap::CommonAllocator::CommonAllocator(fpCommonHeap* heap)
        :fpAllocatorInterface((fpHeapInterface*) heap),
	     TableIndex(NO_INIT_TABLE_INDEX)
{}
FORCEINLINE void* fpCommonHeap::CommonAllocator::Allocate(SIZE_T size)
{
//    assert(TableIndex==NO_INIT_TABLE_INDEX);
    if (TableIndex>=0)
    {
        TableIndex = PERFECT_ALLOC_FREE_FAIL;
		return this->_heap->HeapAlloc(size);
	}
	else {
		if (this->TableIndex == NO_INIT_TABLE_INDEX)
		{
			uint32 aligned = ALIGN(size);
			for (uint8 i = 0;i<LENGTH_TABLE;i++)
			{
				if (aligned >= POOL_SIZES[i])
				{

				}
				else {
					this->TableIndex = i;
					return static_cast<fpCommonHeap*>(_heap)->PoolTable[this->TableIndex]->PoolAllocate();
				}
			}
		}
		else {
			return static_cast<fpCommonHeap*>(_heap)->PoolTable[this->TableIndex]->PoolAllocate();
		}

	}
}
FORCEINLINE void fpCommonHeap::CommonAllocator::Free(void *ptr, SIZE_T size)
{
    if (TableIndex > 0)
    {
        fpCommonHeap* common_heap = static_cast<fpCommonHeap*>(_heap);
        common_heap->PoolTable[TableIndex]->PoolFree(ptr);
    }else{
        _heap->HeapFree(ptr, size);
    }
	TableIndex = NO_INIT_TABLE_INDEX;
}
FORCEINLINE void* fpCommonHeap::CommonAllocator::Realloc(void *ptr, SIZE_T new_size)
{
    if (new_size==0)
    {
        _heap->HeapFree(ptr, new_size);
        return nullptr;
    }
    if (ptr == nullptr)
    {
		return this->Allocate(new_size);
    }
	assert(TableIndex != NO_INIT_TABLE_INDEX);
	assert(TableIndex != PERFECT_ALLOC_FREE_FAIL);
	void* new_mem = _heap->HeapAlloc(new_size);
	fpMemory::MemMove(new_mem, ptr, POOL_SIZES[TableIndex]);
	this->Free(ptr, POOL_SIZES[TableIndex]);
	return new_mem;
}

fpCommonHeap::CommonAllocator::~CommonAllocator()
{

}
