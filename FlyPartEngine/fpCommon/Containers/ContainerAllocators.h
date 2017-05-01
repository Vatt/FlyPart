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
	template <typename OtherElemType,typename OtherAllocatorType> friend class fpArray;
public:
	fpDefaultArrayAllocator()
	{
		_allocator = fpMemory::GetCommonHeap()->MakeAllocator();
		_size = 0;
		Allocate(_size);
	}
	fpDefaultArrayAllocator(uint32 Count)
	{
		_allocator = fpMemory::GetCommonHeap()->MakeAllocator();
		Allocate(Count);
	}
	template<typename OtherType>
	fpDefaultArrayAllocator(fpDefaultArrayAllocator<OtherType>&& other)
	{
		this->_data = other._data;
		this->_size = other._size;
		this->_allocator = other._allocator;		
	}

	fpDefaultArrayAllocator(fpDefaultArrayAllocator<ElemType>&& other)
	{
		this->_data = other._data;
		this->_size = other._size;
		this->_allocator = other._allocator;
	}
	template<typename OtherType>
	SelfRef operator=(fpDefaultArrayAllocator<OtherType>&)
	{
		return *this;
	}
	FORCEINLINE void Allocate(uint32 Count)
	{
		uint32 realNewSize = Count * RESIZE_COEFFICIENT;
		if (Count == realNewSize) { realNewSize += 1; }
		_size = realNewSize;
		_data = static_cast<ElemType*>(_allocator->Allocate(_size*sizeof(ElemType)));
	}
	FORCEINLINE void ReallocateData(uint32 inNewSize)
	{
		uint32 realNewSize = inNewSize * RESIZE_COEFFICIENT;
		if (realNewSize == _size) { return; }
		if (inNewSize == realNewSize) { realNewSize += 1; }
		_size = realNewSize;
		_data = static_cast<ElemType*>(_allocator->Realloc(_data, _size*sizeof(ElemType)));
	}
	FORCEINLINE void FreeData()
	{
		if (_allocator != nullptr && _size > 0 && _data != nullptr)
		{
			_allocator->Free(_data, _size * sizeof(ElemType));
			_size = 0;
			_data = nullptr;
		}
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
	* _size = Container.Length()+1 
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

		assert(_size > RealLength+1);
		_size = RealLength+1;
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
	/*Лютый костыль чтобы в Rvalue непохерились указатели*/
	~fpDefaultArrayAllocator()
	{
		if (_size)
		{
			_allocator->Free(_data, _size);
		}
		_data = nullptr;
		_size = 0;
	}
private:
	constexpr static float RESIZE_COEFFICIENT = 1.5;
	fpAllocatorInterface* _allocator;
	ElemType* _data;
	uint32 _size;
};
#endif