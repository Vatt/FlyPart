#ifndef _FP_COMMON_HEAP_INCLUDE_
#define _FP_COMMON_HEAP_INCLUDE_
#pragma once
#include "fpHeapInterface.h"
#include "../../GenericPlatform/fpPlatform.h"
class fpCommonHeap : public fpHeapInterface
{
	enum 
	{	
		POOL_SIZE = 65536,
		START_POOL_COUNT = 2, //FIXIT: This is test value replace after
		EXTEND_NUMBER = 2,
		   
	};

	struct FreeMemory;
	struct PoolHeader;
	class PoolList;

//public:
	class CommonAllocator :public fpAllocatorInterface
	{
	public:
		CommonAllocator(fpCommonHeap* heap);
		FORCEINLINE virtual void* Allocate(SIZE_T size)override final;
		FORCEINLINE virtual void Free(void *ptr, SIZE_T size)override final;
		FORCEINLINE virtual void* Realloc(void* ptr, SIZE_T size)override final;
		virtual ~CommonAllocator();
	};

public:

	virtual void  HeapInit() override;
	virtual void* HeapAlloc(SIZE_T size)override;
	virtual void  HeapFree(void* target, SIZE_T size)override;
	virtual void* HeapRealloc(void* target, SIZE_T size)override;
	virtual void  HeapCleanup()override;
	
	virtual void  HeapDestroy()override;
	virtual bool  ValidateHeap()override;
	
	virtual FORCEINLINE fpAllocatorInterface* MakeAllocator();
	fpCommonHeap();
	virtual ~fpCommonHeap();
private:
	FORCEINLINE void HeapFreeFast(uint32 inTableIndex, void* inPtr);
	FORCEINLINE PoolHeader* GetPoolHeaderFromPtr(void* inPtr);
	FORCEINLINE uint32 GetTableIndexFromSize(uint32 size);
private:
    fpCommonHeap(const fpCommonHeap&) = delete;
    fpCommonHeap(fpCommonHeap&&) = delete;
    fpCommonHeap& operator=(const fpCommonHeap&) = delete;
    fpCommonHeap& operator=(fpCommonHeap&&) = delete;
private:
	PoolList* PoolTable[45];

};

#endif
