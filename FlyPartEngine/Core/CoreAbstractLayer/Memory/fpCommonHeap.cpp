#include "fpCommonHeap.h"
#include <new>
#include <iostream>
const static SIZE_T PAGE_SIZE = 4096;
const static uint8 LENGTH_TABLE = 45;
const static uint8 HALF_LENGTH_TABLE = LENGTH_TABLE / 2;
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
	SIZE_T TableIndex;
	PoolHeader* Next;
	static void LinkPoolAfter(PoolHeader* after,PoolHeader* target)
	{
		//TODO: следующий может быть нулевым указателем
		PoolHeader* temp_next = after->Next;
		if (temp_next != nullptr)
		{
			target->Next = temp_next;
		}
		after->Next = target;	
	}
#ifdef PLATFORM_32
	/* Выравнивание до 16 байт на 32  битной платформе*/
	uint32 align[2];
#endif

};
class fpCommonHeap::PoolList
{
public:
	static_assert(sizeof(PoolHeader) == 16, "PoolHeader size should be equal to 16");
	static_assert(sizeof(FreeMemory) <= 16, "FreeMemory size should be no more than 16");
	static_assert(POOL_SIZE % PAGE_SIZE == 0, "Enum value POOL_SIZE % PAGE_SIZE(4096) != 0");
	struct TempPoolData {
		PoolHeader* header;
		FreeMemory* first;
		FreeMemory* last;
		FORCEINLINE TempPoolData() :header(nullptr), first(nullptr), last(nullptr)
		{}
		FORCEINLINE TempPoolData(PoolHeader* _header,FreeMemory* _first, FreeMemory* _last)
			:header(_header),first(_first), last(_last)
		{}
		TempPoolData(const TempPoolData& other)
			:header(other.header), first(other.first), last(other.last)
		{
			/*
			other.header = nullptr;
			other.first = nullptr;
			other.last = nullptr;
			*/
		}
		TempPoolData operator= (const TempPoolData& other)
		{
			if (this != &other)
			{
				this->header = other.header;
				this->first = other.first;
				this->last = other.last;
				/*other.header = nullptr;
				other.first = nullptr;
				other.last = nullptr;
				*/

			}
			return *this;
		}

	};

	/*
	* Global pointer of free memory blocks in this list
	*/
	FreeMemory* ListFreeMemory;
	PoolHeader* Front;
	PoolHeader* Last;
	uint32 TableIndex;
	uint32 BlockSize;
	uint32 PoolCount;
	uint32 BlocksNumPerPool;
	uint32 ListFreeBlocksCount;
	PoolList() {};
	PoolList(uint32 block_size, uint32 table_index);
	TempPoolData makeNewPool();
	FORCEINLINE SIZE_T PoolDataSizeCalc();
	FORCEINLINE TempPoolData  MapThePoolOfFreeBlocks(PoolHeader* pool);
	FORCEINLINE void* GetPoolRawData(PoolHeader *pool)const;
	FORCEINLINE void* PoolAllocate();
	FORCEINLINE void  PoolFree(void *inPtr);
	FORCEINLINE void  ExtendPoolsCount();
	FORCEINLINE void  CleanupList();
	FORCEINLINE TempPoolData  CleanupPool(PoolHeader* pool);
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
    this->TableIndex = table_index;
    this->BlockSize = block_size;
	this->BlocksNumPerPool = this->PoolDataSizeCalc() / this->BlockSize;
	this->Front = nullptr;
	this->Last = nullptr;
	this->ListFreeBlocksCount = 0;
	this->PoolCount = 0;
	this->ExtendPoolsCount();
}
FORCEINLINE void fpCommonHeap::PoolList::ExtendPoolsCount()
{

	TempPoolData data[EXTEND_NUMBER];
	for (uint32 i = 0; i < EXTEND_NUMBER; i++)
	{
		data[i] = makeNewPool();
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
		this->Last = data[EXTEND_NUMBER - 1].header;
	}
	else {
		PoolHeader::LinkPoolAfter(this->Last, data[0].header);
		this->Last = data[EXTEND_NUMBER - 1].header;
	}	
}
FORCEINLINE SIZE_T fpCommonHeap::PoolList::PoolDataSizeCalc()
{
	return POOL_SIZE - sizeof(PoolHeader);
}
FORCEINLINE void* fpCommonHeap::PoolList::GetPoolRawData(PoolHeader *pool)const
{
	return (void*)((UINTPTR)pool + (UINTPTR)sizeof(PoolHeader));
}
FORCEINLINE fpCommonHeap::PoolList::TempPoolData fpCommonHeap::PoolList::MapThePoolOfFreeBlocks(PoolHeader* pool)
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
	return  TempPoolData(pool, free_ptr, last_ptr);
}
fpCommonHeap::PoolList::TempPoolData fpCommonHeap::PoolList::makeNewPool()
{
	PoolHeader* pool;
	void* memory = fpMemory::SystemAlloc((UINTPTR)POOL_SIZE);

	/*первые 16 бита информация о самом пуле*/
	pool = new(memory)PoolHeader();
    pool->Next = nullptr;
	pool->TableIndex = this->TableIndex;
	this->PoolCount++;
	this->ListFreeBlocksCount += this->BlocksNumPerPool;
	auto data = this->MapThePoolOfFreeBlocks(pool);
    /*if (this->TableIndex == 0)
    {
        std::cout<<"makeNewPool data.header: \t"<<data.header<<std::endl;
        std::cout<<"makeNewPool data.first: \t"<<data.first<<std::endl;
        std::cout<<"makeNewPool data.last: \t\t"<<data.last<<std::endl;
    }
    */
	return data;//this->MapThePoolOfFreeBlocks(pool);
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
	TempPoolData* temp_data = new TempPoolData[this->PoolCount];
	PoolHeader* iterator = this->Front;
	uint32 index = 0;
	this->ListFreeBlocksCount = 0;
	while (iterator != nullptr)
	{
		temp_data[index] = CleanupPool(iterator);
		this->ListFreeBlocksCount += this->BlocksNumPerPool;
		iterator = iterator->Next;
		++index;
	}
	for (auto index = 1; index < this->PoolCount; index++)
	{
		*&(temp_data[index - 1].last->next) = temp_data[index].first;
	}
	delete[] temp_data;
}
FORCEINLINE fpCommonHeap::PoolList::TempPoolData  fpCommonHeap::PoolList::CleanupPool(PoolHeader* pool)
{
	return this->MapThePoolOfFreeBlocks(pool);
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
    fpMemory::SystemFree((void *) pool, POOL_SIZE);
}



void fpCommonHeap::HeapInit()
{
	//PoolTable = new PoolList[LENGTH_TABLE];
	for (uint8 i = 0;i < LENGTH_TABLE;i++)
	{
		PoolTable[i] = new PoolList(POOL_SIZES[i], i);
	}
}

void* fpCommonHeap::HeapAlloc(SIZE_T size)
{
    SIZE_T aligned = ALIGN(size);
    for(uint8 i = 0;i<LENGTH_TABLE;i++)
    {
        if (aligned<=POOL_SIZES[i])
        {
			void* ptr = PoolTable[i]->PoolAllocate();
			return ptr;
		}
    }
    //FIXIT: Заглушка
	return nullptr;
}
FORCEINLINE void fpCommonHeap::HeapFreeFast(uint32 inTableIndex, void* inPtr)
{
	PoolTable[inTableIndex]->PoolFree(inPtr);
}
FORCEINLINE fpCommonHeap::PoolHeader* fpCommonHeap::GetPoolHeaderFromPtr(void* inPtr)
{
	return (PoolHeader*)(((int64)inPtr) & ~((int64)POOL_SIZE - 1));
}
void fpCommonHeap::HeapFree(void * target, SIZE_T size)
{
	HeapFreeFast(GetPoolHeaderFromPtr(target)->TableIndex, target);
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
	//FIXIT: FIX this hack
	return MakeAllocator()->Realloc(target,size);
}
void fpCommonHeap::HeapDestroy()
{
	if (this->PoolTable == nullptr) { return; }
	for (uint8 i = 0; i < LENGTH_TABLE; i++)
	{
		this->PoolTable[i]->ListDestroy();
		delete this->PoolTable[i];
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

fpAllocatorInterface *fpCommonHeap::MakeAllocator() {
    return  new CommonAllocator(this);
}

fpCommonHeap::CommonAllocator::CommonAllocator(fpCommonHeap* heap)
	:fpAllocatorInterface((fpHeapInterface*)heap)
{
}
FORCEINLINE void* fpCommonHeap::CommonAllocator::Allocate(SIZE_T size)
{
	return this->HeapPtr->HeapAlloc(size);
}
FORCEINLINE void fpCommonHeap::CommonAllocator::Free(void *inPtr, SIZE_T inSize)
{
	uint32 TableIndex = static_cast<fpCommonHeap*>(HeapPtr)->GetPoolHeaderFromPtr(inPtr)->TableIndex;
	static_cast<fpCommonHeap*>(HeapPtr)->PoolTable[TableIndex]->PoolFree(inPtr);
}
FORCEINLINE void* fpCommonHeap::CommonAllocator::Realloc(void *ptr, SIZE_T new_size)
{	
	uint32 TableIndex = static_cast<fpCommonHeap*>(HeapPtr)->GetPoolHeaderFromPtr(ptr)->TableIndex;

    if (new_size==0)
    {
        Free(ptr, POOL_SIZES[TableIndex]);
        return nullptr;
    }
    if (ptr == nullptr || !ptr)
    {
		return this->Allocate(new_size);
    }
	void* new_mem = HeapPtr->HeapAlloc(new_size);
	if (POOL_SIZES[TableIndex] < new_size)
	{
		fpMemory::MemMove(new_mem, ptr, POOL_SIZES[TableIndex]);
	}else{
		fpMemory::MemMove(new_mem, ptr, new_size);
	}
	
	this->Free(ptr, POOL_SIZES[TableIndex]);
	return new_mem;
}

fpCommonHeap::CommonAllocator::~CommonAllocator()
{

}
