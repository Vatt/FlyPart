#ifndef _FPARRAY_H_
#define _FPARRAY_H_
#include "../ClassMemoryOps.h"
#include "../../Core/CoreAbstractLayer/Memory/fpHeapInterface.h"
#include "Iterators.h"
template <typename ElemType>
class fpArray
{
	const float RESIZE_COEFFICIENT = 1.5;
	typedef fpArray<ElemType> SelfType;
public:
	fpArray() :_data(nullptr), _allocator(nullptr), _arrayMax(0), _length(0)
	{}
	fpArray(uint32 inSize)
		:_arrayMax(inSize*RESIZE_COEFFICIENT),
	     _allocator( fpMemory::GetCommonHeap()->MakeAllocator()),
		 _length(inSize)
	{
		_data = static_cast<ElemType*>(_allocator->Allocate(_arrayMax));
		ConstructItems<ElemType>(0, inSize);
	}
	fpArray(uint32 inSize, fpHeapInterface* HeapPtr)
		:_arrayMax(inSize*RESIZE_COEFFICIENT),_allocator(HeapPtr->MakeAllocator())
	{
		_data = static_cast<ElemType*>(_allocator->Allocate(_arrayMax));
		ConstructItems(0, inSize);
		_length = inSize;
	}
	fpArray(SelfType&& other)
	{
		this->_data = other._data;
		this->_arrayMax = other._arrayMax;
		this->_allocator = other._allocator;
		this->_length = other._length;
		other._data = nullptr;
		other._arrayMax = 0;
		other._allocator = nullptr;
		other._length = 0;
	}
	fpArray(const SelfType& other)
	{
		this->_data = other._data;
		this->_arrayMax = other._arrayMax;
		this->_allocator = other._allocator;
		this->_length = other._length;
	}
	template<typename OtherElemType>
	fpArray(const fpArray<OtherElemType>& other)
	{
		this->_data = other._data;
		this->_arrayMax = other._arrayMax;
		this->_allocator = other._allocator;
		this->_length = other._length;
	}
	template<typename OtherElemType>
	fpArray(fpArray<OtherElemType>&& other)
	{
		this->_data = other._data;
		this->_arrayMax = other._arrayMax;
		this->_allocator = other._allocator;
		this->_length = other._length;
		other._data = nullptr;
		other._arrayMax = 0;
		other._allocator = nullptr;
		other._length = 0;
	}
	FORCEINLINE ElemType& operator[](uint32 index)
	{
		return *((ElemType*)((UINTPTR)_data + index * sizeof(ElemType)));
	}
	FORCEINLINE ElemType const & operator[](uint32 index)const
	{
		return *((ElemType*)((UINTPTR)_data + index * sizeof(ElemType)));
	}
	FORCEINLINE void  Resize(uint32 inNewLen)
	{
		ReallocateDataSize(inNewLen*RESIZE_COEFFICIENT);
		_length = inNewLen;
	}
	FORCEINLINE bool IsValidIndex(uint32 Index)
	{
		return Index >= 0 && Index < _length;
	}
	FORCEINLINE const ElemType& Top() const 
	{
		return At(0);
	}
	FORCEINLINE ElemType& Top() 
	{
		return At(0);
	}
	FORCEINLINE bool IsEmpty()
	{
		return _length > 0;
	}
	FORCEINLINE uint32 Length()
	{
		return _length;
	}
	FORCEINLINE ElemType Pop()
	{
		RangeCheck(0, 1);
		ElemType top = At(0);
		RemovePrivate(0, 1, true);
		--_length;
		return top;
	}
	FORCEINLINE void Push(ElemType inElement)
	{

	}
	~fpArray()
	{
		_allocator->Free(_data, _arrayMax);
		_data = nullptr;
	};
private:
	FORCEINLINE ElemType& At(uint32 Index)
	{
		return this->operator[](Index);
	}
	FORCEINLINE const ElemType& At(uint32 Index)const
	{
		return this->operator[](Index);
	}
	FORCEINLINE void RemovePrivate(uint32 Index, uint32 inCount, bool bShrinkAlowed = true)
	{
		if (!inCount) { return; }
		RangeCheck(Index, Index + inCount);
		DestroyItems(_data + Index, inCount);
		int32 MoveCount = _arrayMax - Index - inCount;
		if (MoveCount > 0)
		{
			fpPlatformMemory::MemMove
			(
				(uint8*)_data + (Index * sizeof(ElemType)),
				((uint8*)_data + ((Index + inCount) * sizeof(ElemType))),
				sizeof(ElemType)*inCount
			);
		}
		if (bShrinkAlowed)
		{
			Shrink((_arrayMax - Index - MoveCount) * sizeof(ElemType));
		}
	}
	FORCEINLINE void RangeCheck(uint32 inStart, uint32 inEnd)
	{
		assert((inStart + (inEnd - inStart)) <= _length);
	}
	FORCEINLINE void Shrink(uint32 NumOfBytes)
	{
		auto NewSizeInBytes = _arrayMax * sizeof(ElemType) - NumOfBytes;
		ReallocateDataSize(NewSizeInBytes);
		_arrayMax = NewSizeInBytes / sizeof(ElemType);
	}
	FORCEINLINE void  ReallocateDataSize(uint32 inNewSize)
	{
		_data = static_cast<ElemType*>(_allocator->Realloc(_data, inNewSize * sizeof(ElemType)));
		_arrayMax = inNewSize;
	}
private:	
	ElemType* _data;
	fpAllocatorInterface* _allocator;
	uint32 _arrayMax;
	uint32 _length;
};
#endif //FLYPARTENGINE_FPARRAY_H
