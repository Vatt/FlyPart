#pragma once
#ifndef _CONTAINER_ALLOCATORS_
#define _CONTAINER_ALLOCATOR_
#include "../../Core/CoreAbstractLayer/Memory/fpHeapInterface.h"
#include "../ClassMemoryOps.h"

template <typename ElemType, typename _SizeType>
struct AllocatorBase 
{
	typedef const ElemType* ConstPointerType;
	typedef ElemType* PointerType;
	typedef ElemType& ReferenceType;
	typedef const ElemType& ConstReferenceType;
	typedef _SizeType SizeType;
	typedef ElemType ValueType;
};
template <typename ElemType>
class fpDefaultArrayAllocator:public AllocatorBase<ElemType,uint32>
{

	typedef fpDefaultArrayAllocator<ElemType>& SelfRef;
	
public:
	fpDefaultArrayAllocator()
	{
		_allocator = fpMemory::GetCommonHeap()->MakeAllocator();
		_size = 0;
		_data = nullptr;
	}
	template<typename OtherType>
	SelfRef operator=(fpDefaultArrayAllocator<OtherType>&)
	{
		return *this;
	}
	FORCEINLINE void Allocate(uint32 Count)
	{
		_size = Count * sizeof(ElemType)*RESIZE_COEFFICIENT;
		_data = _allocator->Allocate(_size);
	}
	FORCEINLINE void ReallocateData(uint32 inNewSize)
	{
		_size = inNewSize*RESIZE_COEFFICIENT;
		_data = static_cast<ElemType*>(_allocator->Realloc(_data, _size));
	}
	FORCEINLINE void FreeData()
	{
		_allocator->Free(_data, _size);
		_size = 0;
		_data = nullptr;
	}
	FORCEINLINE PointerType GetData()const
	{
		return _data;
	}
	FORCEINLINE uint32 MaxSize()const
	{
		return _size;
	}
	/*
	* Fake shrink
	* _size = Container.Length()
	* without Free or deallcoate
	*/
	FORCEINLINE void Shrink(uint32 RealLength)
	{
		//uint32 NewMax = RealLength * RESIZE_COEFFICIENT;
		//if (NewMax != _size)
		//{
		//	_size = NewMax;
		//	ResizeData(_size);
		//}

		assert(_size > RealLength);
		_size = RealLength;
	}

	FORCEINLINE PointerType address(ReferenceType Value)
	{
		return fpAddressOf(Value);
	}
	FORCEINLINE ConstPointerType address(ConstReferenceType Value)
	{
		return fpAddressOf(Value);
	}
	/*
	For fpArray never used
	*/
	FORCEINLINE void Deallocate(PointerType Ptr, uint32 Count)
	{
		assert(Count == _size);
		FreeData();
	}

private:
	constexpr static float RESIZE_COEFFICIENT = 1.5;
	fpAllocatorInterface* _allocator;
	ElemType* _data;
	uint32 _size;
};
#endif