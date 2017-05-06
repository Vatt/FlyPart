#ifndef _FPARRAY_H_
#define _FPARRAY_H_
#include "../ClassMemoryOps.h"
#include "Iterators.h"
#include "ContainerAllocators.h"

template <typename ElemType,typename AllocatorType = fpDefaultArrayAllocator<ElemType>>
class fpArray
{
private:
	typedef fpArray<ElemType,AllocatorType> SelfType;
	typedef fpIndexedAraryIterator<		 fpArray<ElemType>,       ElemType, uint32> IteratorType;
	typedef fpIndexedAraryIterator<const fpArray<ElemType>, const ElemType, uint32> ConstIteratorType;
	template<typename ElemType>
	class fpRangedForIterator
	{
	public:
		explicit fpRangedForIterator(ElemType* inPtr, uint32 inIndex)
			:_itPtr(inPtr),
			_currentIndex(inIndex),
			_initialIndex(inIndex)
		{}
		FORCEINLINE ElemType& operator*()const
		{
			return *_itPtr;
		}
		FORCEINLINE fpRangedForIterator& operator++()
		{
			++_itPtr;
			return *this;
		}
		FORCEINLINE fpRangedForIterator& operator--()
		{
			--_itPtr;
			return *this;
		}
	private:
		ElemType* _itPtr;
		const uint32 _initialIndex;
		uint32 _currentIndex;

		FORCEINLINE friend bool operator !=(const fpRangedForIterator& Lhs, const fpRangedForIterator& Rhs)
		{
			/*TODO: запилить ошибку куданибудь в лог*/
			assert(Lhs._currentIndex == Lhs._initialIndex);
			return Lhs._itPtr != Rhs._itPtr;
		}
	};
	typedef fpRangedForIterator<ElemType>		RangedForIterator;
	typedef fpRangedForIterator<const ElemType> ConstRangedForIterator;
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
	template<typename OtherType,typename OtherAllocatorType>
	fpArray(fpArray<OtherType,OtherAllocatorType>&& other)
		:_allocator(fpMove(other._allocator)),_length(other._length)
	{
		/*Лютый костыль чтобы в Rvalue непохерились указатели,
		* иначе деструктор уносит в АД выделнную память под массив
		*/
		other._length = 0;
		other._allocator._size = 0;
	}
	fpArray(const SelfType& other)
		:_allocator(other._length)
	{
		//this->_allocator = other._allocator;
		this->_length = other._length;
		CreateFromRange(other._allocator.GetData(), other._length);
	}
	template<typename OtherElemType, typename OtherAllocatorType>
	explicit fpArray(const fpArray<OtherElemType, OtherAllocatorType>& other)
		:_allocator(AllocatorType(other._length))
	{
		//this->_allocator = other._allocator;
		this->_length = other._length;
		CreateFromRange(other._allocator.GetData(), other._length);
	}
	fpArray(std::initializer_list<ElemType> InitList)
		:_allocator(AllocatorType(InitList.size())),_length(InitList.size())
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
		_allocator.ReallocateData(inNewLen);;
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
	FORCEINLINE uint32 Insert(const fpArray<ElemType>& Other, const uint32 inIndex)
	{
		assert(this != &Other);	
		InsertEmptyPrivate(inIndex, Other._length);
		auto dataPtr = _allocator.GetData();
		uint32 index = inIndex;
		for (auto it = Other.CreateConstIterator(); it; ++it)
		{
			new(dataPtr + index) ElemType(fpTemplate::fpMove(*it));
			index++;
		}
		return inIndex;
	}
	FORCEINLINE uint32 Insert(std::initializer_list<ElemType> InitList, const uint32 inIndex)
	{
		InsertEmptyPrivate(inIndex, InitList.size());
		auto dataPtr = _allocator.GetData();
		uint32 index = inIndex;
		for (const ElemType& elem:InitList)
		{
			new(dataPtr + index) ElemType(elem);
			index++;
		}
		return inIndex;
	}
	FORCEINLINE uint32 Insert(const ElemType* RawData, uint32 Count, uint32 Index)
	{
		assert(RawData != nullptr);
		InsertEmptyPrivate(Index, Count);
		ConstructItems(_allocator.GetData() + Index, RawData, Count);
		return Index;
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
	template<typename... Args>
	FORCEINLINE void Emplace(uint32 Index, Args&&... inArgs)
	{
		InsertEmptyPrivate(Index, 1);
		new(_allocator.GetData() + Index)ElemType(fpTemplate::fpForward<Args>(inArgs)...);
	}
	FORCEINLINE void Remove(uint32 Index)
	{
		RemovePrivate(Index, 1, true);
	}
	FORCEINLINE void Remove(uint32 Index, uint32 Count, bool ShrinkAllowed = true)
	{
		RemovePrivate(Index, Count, ShrinkAllowed);
	}
	RangedForIterator& begin()			 { return RangedForIterator(_allocator.GetData(), 0); }
	RangedForIterator& end()			 { return RangedForIterator(_allocator.GetData()+_length, _length); }
	ConstRangedForIterator& cbegin()const{ return ConstRangedForIterator(_allocator.GetData(), 0); }
	ConstRangedForIterator& cend()  const{ return ConstRangedForIterator(_allocator.GetData() + _length, _length); }
	FORCEINLINE void FullDestroy()
	{
		DestroyItems(_allocator.GetData(), _length);
		_allocator.FreeData();
	}
	~fpArray()
	{
		DestroyItems(_allocator.GetData(), _length);
		_length = 0;
	};
	FORCEINLINE bool operator==(fpArray& Other)
	{
		#ifdef FAST_EQUAL_OPERATOR_FOR_FPARRAY
				return this->_allocator.GetData() == Other._allocator.GetData() &&
					   this->_length == Other._length &&
					   this->_allocator.MaxSize() == Other._allocator.MaxSize();
		#else
				auto thisData = this->_allocator.GetData();
				auto otherData = Other._allocator.GetData();
				return this->_length == other._length && CompareItems(thisData, OtherData, _length);
		#endif

	}
	FORCEINLINE bool operator!=(fpArray& Other)
	{
		return !(*this == Other);
	}

	IteratorType CreateIterator() 
	{
		return IteratorType(*this, 0);
	}
	ConstIteratorType CreateConstIterator()const
	{
		return ConstIteratorType(*this, 0);
	}
	IteratorType CreateReverseIterator()
	{
		return IteratorType(*this, _length-1);
	}
	ConstIteratorType CreateReverseConstIterator()const
	{
		return ConstIteratorType(*this, _length);
	}
	const ElemType* GetData()
	{
		return static_cast<const ElemType*>(_allocator.GetData());
	}

	FORCEINLINE bool Find(const ElemType& Element, uint32& Index)const
	{
		Index = this->Find(Element);
		return Index != -1;
	}
	FORCEINLINE int32 Find(const ElemType& Element)const
	{
		const ElemType* RESTRICT Data = _allocator.GetData();
		for (const ElemType* RESTRICT It = Data, *RESTRICT End = Data + _length;
			It != End;
			++It)
		{
			if (*It == Element)
			{
				return static_cast<int32>(It - Data);
			}
		}
		return -1;
	}
	template<typename PredicateType>
	FORCEINLINE bool Find(PredicateType Predicate, uint32& Index)const
	{
		Index = this->Find(Predicate);
		return Index != -1;
	}
	template<typename PredicateType>
	FORCEINLINE int32 Find(PredicateType Predicate)const
	{
		const ElemType* RESTRICT Data = _allocator.GetData();
		for (const ElemType* RESTRICT It = Data, *RESTRICT End = Data + _length;
			It != End;
			++It)
		{
			if (Predicate(*It))
			{
				return static_cast<int32>(It - Data);
			}
		}
		return -1;
	}
	template<typename PredicateType>
	FORCEINLINE int32 Find(PredicateType Predicate,uint32 StartIndex)const
	{
		const ElemType* RESTRICT Data = _allocator.GetData();
		for (const ElemType* RESTRICT It = Data+StartIndex, *RESTRICT End = Data + _length;
			It != End;
			++It)
		{
			if (Predicate(*It))
			{
				return static_cast<int32>(It - Data);
			}
		}
		return -1;
	}
	FORCEINLINE bool FindLast(const ElemType& Element, uint32& Index)const
	{
		Index = this->FindLast(Element);
		return Index != -1;
	}
	FORCEINLINE int32 FindLast(const ElemType& Element)const
	{
		const ElemType* RESTRICT Data = _allocator.GetData();
		for (const ElemType* RESTRICT Start = Data, *RESTRICT It = Start + _length; It != Start; )
		{
			--It;
			if (*It == Element)
			{
				return static_cast<int32>(It - Data);
			}
		}
		return -1;
	}
	template<typename PredicateType>
	FORCEINLINE bool FindLast(PredicateType Predicate, uint32& Index)const
	{
		Index = this->FindLast(Predicate);
		return Index != -1;
	}
	template<typename PredicateType>
	FORCEINLINE int32 FindLast(PredicateType Predicate)const
	{
		const ElemType* RESTRICT Data = _allocator.GetData();
		for (const ElemType* RESTRICT Start = Data, *RESTRICT It = Start + _length; It != Start; )
		{
			--It;
			if (Predicate(*It))
			{
				return static_cast<int32>(It - Data);
			}
		}
		return -1;
	}
	template<typename PredicateType>
	fpArray<ElemType> Filter(PredicateType Predicate)
	{
		fpArray<ElemType> Filtered;
		const ElemType* RESTRICT Data = _allocator.GetData();
		for (const ElemType* RESTRICT It = Data, *RESTRICT End = Data + _length;
			It != End;
			++It)
		{
			if (Predicate(*It))
			{
				Filtered.PushBack(*It);
			}
		}
		return Filtered;
	}
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
		CheckState();
	}
	FORCEINLINE void InsertPrivate(uint32 Index, const ElemType& inElement)
	{
		int32 MoveCount = _length - Index;
		assert(!(GetUnusedSpace() < 0));
		if (GetUnusedSpace() < 2)
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
		if (GetUnusedSpace() < 2)
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
	FORCEINLINE void InsertEmptyPrivate(uint32 Index, uint32 Count)
	{
		assert(!(GetUnusedSpace() < 0));
		assert((Count >= 0) & (Index >= 0) & (Index <= _length));
		int32 MoveCount = _length - Index;
		if (GetUnusedSpace() < Count+1)
		{
			Resize(_length+Count);
		}

		if (MoveCount > 0)
		{
			fpPlatformMemory::MemMove
			(
				(uint8*)_allocator.GetData() + ((Index + Count) * sizeof(ElemType)),
				((uint8*)_allocator.GetData() + (Index * sizeof(ElemType))),
				sizeof(ElemType)*MoveCount
			);
		}		
		_length+= Count;
	}
	FORCEINLINE void CreateFromRange(const ElemType* BeginPtr, uint32 inCount)
	{
		/*если вот тут отвалилось, значит в первоначальной инциализации аллокатора что-то пошло не так*/
		assert(_length == inCount);
		_length = inCount;
		Resize(_length);
		ConstructItems<ElemType>(_allocator.GetData(), BeginPtr, _length);
	}

	FORCEINLINE void CheckState()
	{
		assert(_length <= _allocator.MaxSize() && _length >= 0);
	}

private:	
	AllocatorType _allocator;
	uint32 _length;
};

template <typename T> struct fpIsfpArray { enum { Value = false }; };

template <typename ElemType, typename AllocatorType> struct fpIsfpArray<               fpArray<ElemType, AllocatorType>> { enum { Value = true }; };
template <typename ElemType, typename AllocatorType> struct fpIsfpArray<const          fpArray<ElemType, AllocatorType>> { enum { Value = true }; };
template <typename ElemType, typename AllocatorType> struct fpIsfpArray<      volatile fpArray<ElemType, AllocatorType>> { enum { Value = true }; };
template <typename ElemType, typename AllocatorType> struct fpIsfpArray<const volatile fpArray<ElemType, AllocatorType>> { enum { Value = true }; };

#endif //FLYPARTENGINE_FPARRAY_H