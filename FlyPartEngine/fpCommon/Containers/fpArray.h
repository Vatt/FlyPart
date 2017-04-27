#ifndef _FPARRAY_H_
#define _FPARRAY_H_
#include "../ClassMemoryOps.h"
#include "Iterators.h"
#include "ContainerAllocators.h"

template <typename ElemType,typename AllocatorType = fpDefaultArrayAllocator<ElemType>>
class fpArray
{
	typedef fpArray<ElemType> SelfType;
public:
	fpArray() :_allocator(AllocatorType()), _length(0)
	{}
	fpArray(uint32 inSize)
		:_allocator( AllocatorType()),
		 _length(inSize)
	{
		_allocator.Allocate(inSize);
		ConstructItems<ElemType>(_allocator.GetData(), inSize);
	}

	fpArray(SelfType&& other)
	{
		this->_allocator = other._allocator;
		this->_length = other._length;
		other._allocator = nullptr;
		other._length = 0;
	}
	fpArray(const SelfType& other)
	{
		this->_allocator = other._allocator;
		this->_length = other._length;
	}
	template<typename OtherElemType>
	fpArray(const fpArray<OtherElemType>& other)
	{
		this->_allocator = other._allocator;
		this->_length = other._length;
	}
	template<typename OtherElemType>
	fpArray(fpArray<OtherElemType>&& other)
	{
		this->_allocator = other._allocator;
		this->_length = other._length;
		other._allocator = nullptr;
		other._length = 0;
	}
	fpArray(std::initializer_list<ElemType> InitList)
		:_allocator(AllocatorType())
	{		
		CreateFromRange(InitList.begin(), InitList.size());
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
		ReallocateDataSize(inNewLen);
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
	FORCEINLINE ElemType& At(uint32 index)
	{
		CheckIndex(index);
		return *((ElemType*)((UINTPTR)_allocator.GetData() + index * sizeof(ElemType)));
	}
	FORCEINLINE const ElemType& At(uint32 index)const
	{
		CheckIndex(index);
		return *((ElemType*)((UINTPTR)_allocator.GetData() + index * sizeof(ElemType)));
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
		assert(!(GetUnusedSpace() < 0));
		uint32 index = _length;
		if (GetUnusedSpace() == 0)
		{
			Resize(_length + 1);
		}
		new(_allocator.GetData() + index)ElemType(fpTemplate::fpForward<Args>(inArgs)...);
		++_length;
		return index;
	}
	bool operator!=(const fpArray& Rhs) const
	{
		return !(*this == Rhs);
	}
	bool operator==(const fpArray& Rhs) const
	{
		return this->_allocator.GetData() == Rhs._allocator.GetData() &&
			   this->_length == Rhs._length;
	}
	fpIndexedIterator<SelfType,ElemType, uint32>& begin()
	{
		return fpIndexedIterator<SelfType, ElemType, uint32>(*this, 0);
	}
	fpIndexedIterator<SelfType, ElemType, uint32>& end()
	{
		/*fpIndexedIterator<SelfType, ElemType, uint32>(*this, _length-1);*/
		return fpIndexedIterator<SelfType, ElemType, uint32>(*this, _length);
	}

	~fpArray()
	{
		_allocator.FreeData();
	};
private:

	FORCEINLINE void RemovePrivate(uint32 Index, uint32 inCount, bool bShrinkAlowed = true)
	{
		if (!inCount) { return; }
		RangeCheck(Index, Index + inCount - 1);
		DestroyItems(_allocator.GetData() + Index, inCount);
		int32 MoveCount = _allocator.MaxSize() - Index - inCount;
		if (MoveCount > 0)
		{
			fpPlatformMemory::MemMove
			(
				(uint8*)_allocator.GetData() + (Index * sizeof(ElemType)),
				((uint8*)_allocator.GetData() + ((Index + inCount) * sizeof(ElemType))),
				sizeof(ElemType)*MoveCount
			);
		}
		if (bShrinkAlowed)
		{
			_allocator.Shrink(_length);
		}
	}
	
	FORCEINLINE int32 GetUnusedSpace()
	{
		return _allocator.MaxSize() - _length;
	}
	FORCEINLINE void CheckIndex(uint32 Index)const
	{
		assert(IsValidIndex(Index));
	}
	FORCEINLINE void RangeCheck(uint32 Start, uint32 End)
	{
		CheckIndex(Start);
		CheckIndex(End);
	}
	FORCEINLINE void  ReallocateDataSize(uint32 NewLen)
	{
		_allocator.ReallocateData(NewLen);
	}
	FORCEINLINE void InsertPrivate(uint32 Index, const ElemType& inElement)
	{
		int32 MoveCount = _length - Index;
		assert(!(GetUnusedSpace() < 0));
		if (GetUnusedSpace() == 0)
		{
			Resize(_length + 1);
		}
		if (MoveCount > 0)
		{
			fpPlatformMemory::MemMove
			(
				(uint8*)_allocator.GetData() + ((Index + 1) * sizeof(ElemType)),
				((uint8*)_allocator.GetData() + (Index  * sizeof(ElemType))),
				sizeof(ElemType)*MoveCount
			);
		}
		*(_allocator.GetData() +Index) = inElement;
		++_length;
	}
	FORCEINLINE void InsertPrivate(uint32 Index,ElemType&& inElement)
	{
		assert(!(GetUnusedSpace() < 0));
		int32 MoveCount = _length - Index;
		if (GetUnusedSpace() == 0)
		{
			Resize(_length + 1);
		}
		
		if (MoveCount > 0)
		{
			fpPlatformMemory::MemMove
			(
				(uint8*)_allocator.GetData() + ((Index + 1) * sizeof(ElemType)),
				((uint8*)_allocator.GetData() + (Index * sizeof(ElemType))),
				sizeof(ElemType)*MoveCount
			);
		}
		*(_allocator.GetData() + Index) = fpTemplate::fpMove(inElement);
		++_length;
	}
	FORCEINLINE void CreateFromRange(const ElemType* BeginPtr, uint32 inCount)
	{
		assert(_allocator.GetData() == nullptr);
		_length = inCount;
		Resize(_length);
		ConstructItems<ElemType>(_allocator.GetData(), BeginPtr, _length);
	}

private:	
	AllocatorType _allocator;
	uint32 _length;
};
#endif //FLYPARTENGINE_FPARRAY_H