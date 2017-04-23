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
		:_allocator( fpMemory::GetCommonHeap()->MakeAllocator()),
		 _length(inSize)
	{
		_arrayMax = inSize *RESIZE_COEFFICIENT;
		_data = static_cast<ElemType*>(_allocator->Allocate(_arrayMax));
		ConstructItems<ElemType>(_data, inSize);
	}
	fpArray(uint32 inSize, fpHeapInterface* HeapPtr)
		:_arrayMax(inSize*RESIZE_COEFFICIENT),_allocator(HeapPtr->MakeAllocator())
	{
		_data = static_cast<ElemType*>(_allocator->Allocate(_arrayMax));
		ConstructItems(_data, inSize);
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
		return At(index);
	}
	FORCEINLINE const ElemType& operator[](uint32 index)const
	{
		return (const ElemType&)At(index);
	}
	FORCEINLINE void  Resize(uint32 inNewLen)
	{
		_arrayMax = inNewLen*RESIZE_COEFFICIENT;
		ReallocateDataSize(_arrayMax);

	}
	FORCEINLINE bool IsValidIndex(uint32 Index) const
	{
		return Index >= 0 && Index < _length;
	}
	FORCEINLINE const ElemType& Front() const 
	{
		CheckIndex(0);
		return (const ElemType&)At(0);
	}
	FORCEINLINE ElemType& Front()
	{
		CheckIndex(0);
		return At(0);
	}
	FORCEINLINE ElemType& Back()
	{
		CheckIndex(_length - 1);
		return At(_length - 1);
	}
	FORCEINLINE const ElemType& Back()const
	{
		CheckIndex(_length - 1);
		return (const ElemType&)At(_length - 1);
	}
	FORCEINLINE bool IsEmpty() const
	{
		return _length > 0;
	}
	FORCEINLINE uint32 Length() const
	{
		return _length;
	}
	FORCEINLINE ElemType Pop()
	{
		CheckIndex(0);
		ElemType top = At(0);
		RemovePrivate(0, 1, true);
		--_length;
		return top;
	}
	FORCEINLINE void PushFront(const ElemType& inElement)
	{
		InsertPrivate(0, inElement);
	}
	FORCEINLINE void Insert(uint32 Index, const ElemType& inElement)
	{
		CheckIndex(Index);
		InsertPrivate(Index, inElement);
	}
	FORCEINLINE void Insert(uint32 Index, ElemType&& inElement)
	{
		CheckIndex(Index);
		InsertPrivate(Index, fpTemplate::fpMove(inElement));
	}
	FORCEINLINE void PushFront(ElemType&& inElement)
	{
		InsertPrivate(0, fpTemplate::fpMove(inElement));
	}
	FORCEINLINE void PushBack(const ElemType& inElement)
	{
		InsertPrivate(_length, inElement);
	}
	FORCEINLINE void PushBack(ElemType&& inElement)
	{
		InsertPrivate(_length, fpTemplate::fpMove(inElement));
	}
	template<typename... Args>
	FORCEINLINE uint32 EmplaceBack(Args&&... inArgs)
	{
		uint32 index = _length;
		if (GetUnusedSpace() == 0)
		{
			Resize(_length + 1);
		}
		new(_data + index)ElemType(fpTemplate::fpForward<Args>(inArgs)...);
		++_length;
		return index;
	}
	~fpArray()
	{
		_allocator->Free(_data, _arrayMax);
		_data = nullptr;
	};
private:
	FORCEINLINE ElemType& At(uint32 index)
	{	
		CheckIndex(index);
		return *((ElemType*)((UINTPTR)_data + index * sizeof(ElemType)));
	}
	FORCEINLINE const ElemType& At(uint32 index)const
	{
		CheckIndex(index);
		return *((ElemType*)((UINTPTR)_data + index * sizeof(ElemType)));
	}
	FORCEINLINE void RemovePrivate(uint32 Index, uint32 inCount, bool bShrinkAlowed = true)
	{
		if (!inCount) { return; }
		RangeCheck(Index, Index + inCount - 1);
		DestroyItems(_data + Index, inCount);
		int32 MoveCount = _arrayMax - Index - inCount;
		if (MoveCount > 0)
		{
			fpPlatformMemory::MemMove
			(
				(uint8*)_data + (Index * sizeof(ElemType)),
				((uint8*)_data + ((Index + inCount) * sizeof(ElemType))),
				sizeof(ElemType)*MoveCount
			);
		}
		if (bShrinkAlowed)
		{
			Shrink();
		}
	}
	
	FORCEINLINE uint32 GetUnusedSpace()
	{
		return _arrayMax - _length;
	}
	FORCEINLINE void CheckIndex(uint32 Index)const
	{
		assert(IsValidIndex(Index));
	}
	FORCEINLINE void RangeCheck(uint32 inStart, uint32 inEnd)
	{
		CheckIndex(inStart);
		CheckIndex(inEnd);
	}
	FORCEINLINE void Shrink()
	{
		uint32 NewMax = _length * RESIZE_COEFFICIENT; 
		if (NewMax != _arrayMax)
		{
			_arrayMax = NewMax;
			ReallocateDataSize(_arrayMax);
		}
		
	}
	FORCEINLINE void  ReallocateDataSize(uint32 inNewMaxSize)
	{
		_data = static_cast<ElemType*>(_allocator->Realloc(_data, inNewMaxSize * sizeof(ElemType)));
	}
	FORCEINLINE void InsertPrivate(uint32 Index, const ElemType& inElement)
	{
		int32 MoveCount = _length - Index;
		if (GetUnusedSpace() == 0)
		{
			Resize(_length + 1);
		}
		if (MoveCount > 0)
		{
			fpPlatformMemory::MemMove
			(
				(uint8*)_data + ((Index + 1) * sizeof(ElemType)),
				((uint8*)_data + (Index  * sizeof(ElemType))),
				sizeof(ElemType)*MoveCount
			);
		}
		*(_data+Index) = inElement;
		++_length;
	}
	FORCEINLINE void InsertPrivate(uint32 Index,ElemType&& inElement)
	{
		int32 MoveCount = _length - Index;
		if (GetUnusedSpace() == 0)
		{
			Resize(_length + 1);
		}
		
		if (MoveCount > 0)
		{
			fpPlatformMemory::MemMove
			(
				(uint8*)_data + ((Index + 1) * sizeof(ElemType)),
				((uint8*)_data + (Index * sizeof(ElemType))),
				sizeof(ElemType)*MoveCount
			);
		}
		*(_data + Index) = fpTemplate::fpMove(inElement);
		++_length;
	}
private:	
	ElemType* _data;
	fpAllocatorInterface* _allocator;
	uint32 _arrayMax;
	uint32 _length;
};
#endif //FLYPARTENGINE_FPARRAY_H
