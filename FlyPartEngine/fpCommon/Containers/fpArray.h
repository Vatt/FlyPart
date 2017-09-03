#ifndef _FPARRAY_H_
#define _FPARRAY_H_

#include <initializer_list>
#include "../ClassMemoryOps.h"
#include "Iterators.h"
#include "../../Core/CoreAbstractLayer/Memory/fpHeapInterface.h"
#include <initializer_list>

template <typename TElement>
class fpDefaultArrayAllocator
{
	typedef const TElement* TConstPointer;
	typedef TElement* TPointer;
	typedef TElement& ReferenceType;
	typedef const TElement& ConstReferenceType;
	typedef uint32 TSize;
	typedef TElement TValue;


	typedef fpDefaultArrayAllocator<TElement>& TSelfRef;
	template <typename TOtherElement, typename TOtherAllocator> friend class fpArray;
public:
	fpDefaultArrayAllocator()
	{
		_allocator = fpMemory::GetCommonHeap()->MakeAllocator();
		_size = 0;
		Allocate(_size);
	}
	template<typename TOtherElement>
	fpDefaultArrayAllocator(fpDefaultArrayAllocator<TOtherElement>&& other)
	{
		this->_data = other._data;
		this->_size = other._size;
		this->_allocator = other._allocator;
	}

	fpDefaultArrayAllocator(fpDefaultArrayAllocator<TElement>&& other)
	{
		this->_data = other._data;
		this->_size = other._size;
		this->_allocator = other._allocator;
	}
	template<typename TOtherElement>
	TSelfRef operator=(fpDefaultArrayAllocator<TOtherElement>&)
	{
		return *this;
	}
	FORCEINLINE TElement* Allocate(uint32 Count)
	{
		uint32 realNewSize = Count * RESIZE_COEFFICIENT;
		if (Count == realNewSize) { realNewSize += 1; }
		_size = realNewSize;
		_data = static_cast<TElement*>(_allocator->Allocate(_size * sizeof(TElement)));
		return _data;
	}
	FORCEINLINE TElement* ReallocateData(uint32 inNewSize)
	{
		uint32 realNewSize = inNewSize * RESIZE_COEFFICIENT;
		if (realNewSize == _size) { return _data; }
		if (inNewSize == realNewSize) { realNewSize += 1; }
		_size = realNewSize;
		_data = static_cast<TElement*>(_allocator->Realloc(_data, _size * sizeof(TElement)));
		return _data;
	}
	FORCEINLINE void FreeData()
	{
		if (_allocator != nullptr && _size > 0 && _data != nullptr)
		{
			_allocator->Free(_data, _size * sizeof(TElement));
			_size = 0;
			_data = nullptr;
		}
	}
	FORCEINLINE TPointer GetData()const
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

		assert(_size > RealLength + 1);
		_size = RealLength + 1;
	}

	/*
	For fpArray never used
	*/
	FORCEINLINE void Deallocate(TPointer Ptr, uint32 Count)
	{
		assert(Count == _size);
		FreeData();
	}
	/*����� ������� ����� � Rvalue ������������ ���������*/
	~fpDefaultArrayAllocator()
	{
		if (_size)
		{
			_allocator->Free(_data, _size);
		}
		_data = nullptr;
		_size = 0;
        //delete _allocator;
	}
private:
	constexpr static float RESIZE_COEFFICIENT = 1.3;
	fpAllocatorInterface* _allocator;
	TElement* _data;
	uint32 _size;
};

template <typename TElement,typename TAllocator = fpDefaultArrayAllocator<TElement>>
class fpArray
{
private:
	typedef fpArray<TElement,TAllocator> TSelf;
	typedef fpIndexedAraryIterator<		 fpArray<TElement>,       TElement, uint32> TIterator;
	typedef fpIndexedAraryIterator<const fpArray<TElement>, const TElement, uint32> TConstIterator;

	template<typename TIteratorElement>
	class fpRangedForIterator
	{
	public:
		explicit fpRangedForIterator(TIteratorElement* inPtr, uint32 inIndex)
			:_itPtr(inPtr),
			 _currentIndex(inIndex),
			 _initialIndex(inIndex)
		{}
		FORCEINLINE TIteratorElement& operator*()const
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
		TIteratorElement* _itPtr;
		const uint32 _initialIndex;
		uint32 _currentIndex;

		FORCEINLINE friend bool operator !=(const fpRangedForIterator& Lhs, const fpRangedForIterator& Rhs)
		{
			/*TODO: �������� ������ ���������� � ���*/
			assert(Lhs._currentIndex == Lhs._initialIndex);
			return Lhs._itPtr != Rhs._itPtr;
		}
	};
	typedef fpRangedForIterator<TElement>		RangedForIterator;
	typedef fpRangedForIterator<const TElement> ConstRangedForIterator;
public:
	fpArray() :_allocator(TAllocator()), _length(0)
	{}
	fpArray(uint32 inSize)
		:_allocator( TAllocator()),
		 _length(inSize)
	{
		_allocator.Allocate(inSize);
		ConstructItems<TElement>(_allocator.GetData(), inSize);
	}
	template<typename OtherType,typename OtherAllocatorType>
	fpArray(fpArray<OtherType,OtherAllocatorType>&& other)
		:_allocator(fpMove(other._allocator)),_length(other._length)
	{
		/*����� ������� ����� � Rvalue ������������ ���������,
		* ����� ���������� ������ � �� ��������� ������ ��� ������
		*/
		other._length = 0;
		other._allocator._size = 0;
	}
	fpArray(const TSelf& other)
		:_allocator(other._length)
	{
		//this->_allocator = other._allocator;
		this->_length = other._length;
		CreateFromRange(other._allocator.GetData(), other._length);
	}
	template<typename TOtherElement, typename TOtherAllocator>
	explicit fpArray(const fpArray<TOtherElement, TOtherAllocator>& other)
		:_allocator(TAllocator(other._length))
	{
		//this->_allocator = other._allocator;
		this->_length = other._length;
		CreateFromRange(other._allocator.GetData(), other._length);
	}
	fpArray(std::initializer_list<TElement> InitList)
		:/*_allocator(TAllocator(InitList.size())),*/
		_length(InitList.size())
	{		
		
		_allocator.Allocate(InitList.size());
		CreateFromRange(InitList.begin(), InitList.size());
	}

	FORCEINLINE TElement& operator[](uint32 index)
	{
		return At(index);
	}
	FORCEINLINE const TElement& operator[](uint32 index)const
	{
		return (const TElement&)At(index);
	}
	FORCEINLINE void  Resize(uint32 inNewLen)
	{	
		_allocator.ReallocateData(inNewLen);;
	}
	FORCEINLINE bool IsValidIndex(uint32 Index) const
	{
		return Index >= 0 && Index < _length;
	}
	FORCEINLINE const TElement& Front() const
	{
		CheckIndex(0);
		return (const TElement&)At(0);
	}
	FORCEINLINE TElement& Front()
	{
		CheckIndex(0);
		return At(0);
	}
	FORCEINLINE TElement& Back()
	{
		CheckIndex(_length - 1);
		return At(_length - 1);
	}
	FORCEINLINE const TElement& Back()const
	{
		CheckIndex(_length - 1);
		return (const TElement&)At(_length - 1);
	}
	FORCEINLINE bool IsEmpty() const
	{
		return _length > 0;
	}
	FORCEINLINE uint32 Length() const
	{
		return _length;
	}
	FORCEINLINE TElement Pop()
	{
		CheckIndex(0);
		TElement top = At(0);
		RemovePrivate(0, 1, true);
		--_length;
		return top;
	}
	FORCEINLINE TElement& At(uint32 index)
	{
		CheckIndex(index);
		return *((TElement*)((UINTPTR)_allocator.GetData() + index * sizeof(TElement)));
	}
	FORCEINLINE const TElement& At(uint32 index)const
	{
		CheckIndex(index);
		return *((TElement*)((UINTPTR)_allocator.GetData() + index * sizeof(TElement)));
	}
	FORCEINLINE void PushFront(const TElement& inElement)
	{
		InsertPrivate(0, inElement);
	}
	FORCEINLINE void Insert(uint32 Index, const TElement& inElement)
	{
		CheckIndex(Index);
		InsertPrivate(Index, inElement);
	}
	FORCEINLINE void Insert(uint32 Index, TElement&& inElement)
	{
		CheckIndex(Index);
		InsertPrivate(Index, fpTemplate::fpMove(inElement));
	}
	FORCEINLINE uint32 Insert(const fpArray<TElement>& Other, const uint32 inIndex)
	{
		assert(this != &Other);	
		InsertEmptyPrivate(inIndex, Other._length);
		auto dataPtr = _allocator.GetData();
		uint32 index = inIndex;
		for (auto it = Other.CreateConstIterator(); it; ++it)
		{
			new(dataPtr + index) TElement(fpTemplate::fpMove(*it));
			index++;
		}
		return inIndex;
	}
	FORCEINLINE uint32 Insert(std::initializer_list<TElement> InitList, const uint32 inIndex)
	{
		InsertEmptyPrivate(inIndex, InitList.size());
		auto dataPtr = _allocator.GetData();
		uint32 index = inIndex;
		for (const TElement& elem:InitList)
		{
			new(dataPtr + index) TElement(elem);
			index++;
		}
		return inIndex;
	}
	FORCEINLINE uint32 Insert(const TElement* RawData, uint32 Count, uint32 Index)
	{
		assert(RawData != nullptr);
		InsertEmptyPrivate(Index, Count);
		ConstructItems(_allocator.GetData() + Index, RawData, Count);
		return Index;
	}
	FORCEINLINE void PushFront(TElement&& inElement)
	{
		InsertPrivate(0, fpTemplate::fpMove(inElement));
	}
	FORCEINLINE void PushBack(const TElement& inElement)
	{
		InsertPrivate(_length, inElement);
	}
	FORCEINLINE void PushBack(TElement&& inElement)
	{
		InsertPrivate(_length, fpTemplate::fpMove(inElement));
	}
	template<typename... TArgs>
	FORCEINLINE uint32 EmplaceBack(TArgs&&... inArgs)
	{
		assert(!(GetUnusedSpace() < 0));
		uint32 index = _length;
		if (GetUnusedSpace() == 0)
		{
			Resize(_length + 1);
		}
		new(_allocator.GetData() + index)TElement(fpTemplate::fpForward<TArgs>(inArgs)...);
		++_length;
		return index;
	}
	template<typename... Args>
	FORCEINLINE void Emplace(uint32 Index, Args&&... inArgs)
	{
		InsertEmptyPrivate(Index, 1);
		new(_allocator.GetData() + Index)TElement(fpTemplate::fpForward<Args>(inArgs)...);
	}
	FORCEINLINE void Remove(uint32 Index)
	{
		RemovePrivate(Index, 1, true);
	}
	FORCEINLINE void Remove(uint32 Index, uint32 Count, bool ShrinkAllowed = true)
	{
		RemovePrivate(Index, Count, ShrinkAllowed);
	}
	RangedForIterator begin()			{ return RangedForIterator(_allocator.GetData(), 0); }
	RangedForIterator end()			 	{ return RangedForIterator(_allocator.GetData()+_length, _length); }
	ConstRangedForIterator cbegin()const{ return ConstRangedForIterator(_allocator.GetData(), 0); }
	ConstRangedForIterator cend()  const{ return ConstRangedForIterator(_allocator.GetData() + _length, _length); }
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
				return this->_length == Other._length && CompareItems(thisData, otherData, _length);
		#endif

	}
	FORCEINLINE bool operator!=(fpArray& Other)
	{
		return !(*this == Other);
	}

	TIterator CreateIterator()
	{
		return TIterator(*this, 0);
	}
	TConstIterator CreateConstIterator()const
	{
		return TConstIterator(*this, 0);
	}
	TIterator CreateReverseIterator()
	{
		return TIterator(*this, _length-1);
	}
	TConstIterator CreateConstReverseIterator()const
	{
		return TConstIterator(*this, _length);
	}
	const TElement* GetData()
	{
		return static_cast<const TElement*>(_allocator.GetData());
	}

	FORCEINLINE bool Find(const TElement& Element, uint32& Index)const
	{
		Index = this->Find(Element);
		return Index != -1;
	}
	FORCEINLINE int32 Find(const TElement& Element)const
	{
		const TElement* RESTRICT Data = _allocator.GetData();
		for (const TElement* RESTRICT It = Data, *RESTRICT End = Data + _length;
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
		const TElement* RESTRICT Data = _allocator.GetData();
		for (const TElement* RESTRICT It = Data, *RESTRICT End = Data + _length;
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
		const TElement* RESTRICT Data = _allocator.GetData();
		for (const TElement* RESTRICT It = Data+StartIndex, *RESTRICT End = Data + _length;
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
	FORCEINLINE bool FindLast(const TElement& Element, uint32& Index)const
	{
		Index = this->FindLast(Element);
		return Index != -1;
	}
	FORCEINLINE int32 FindLast(const TElement& Element)const
	{
		const TElement* RESTRICT Data = _allocator.GetData();
		for (const TElement* RESTRICT Start = Data, *RESTRICT It = Start + _length; It != Start; )
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
		const TElement* RESTRICT Data = _allocator.GetData();
		for (const TElement* RESTRICT Start = Data, *RESTRICT It = Start + _length; It != Start; )
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
	fpArray<TElement> Filter(PredicateType Predicate)
	{
		fpArray<TElement> Filtered;
		const TElement* RESTRICT Data = _allocator.GetData();
		for (const TElement* RESTRICT It = Data, *RESTRICT End = Data + _length;
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
				(uint8*)_allocator.GetData() + (Index * sizeof(TElement)),
				((uint8*)_allocator.GetData() + ((Index + inCount) * sizeof(TElement))),
				sizeof(TElement)*MoveCount
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
	FORCEINLINE void InsertPrivate(uint32 Index, const TElement& inElement)
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
				(uint8*)_allocator.GetData() + ((Index + 1) * sizeof(TElement)),
				((uint8*)_allocator.GetData() + (Index  * sizeof(TElement))),
				sizeof(TElement)*MoveCount
			);
		}
		*(_allocator.GetData() +Index) = inElement;
		++_length;
	}
	FORCEINLINE void InsertPrivate(uint32 Index,TElement&& inElement)
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
				(uint8*)_allocator.GetData() + ((Index + 1) * sizeof(TElement)),
				((uint8*)_allocator.GetData() + (Index * sizeof(TElement))),
				sizeof(TElement)*MoveCount
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
				(uint8*)_allocator.GetData() + ((Index + Count) * sizeof(TElement)),
				((uint8*)_allocator.GetData() + (Index * sizeof(TElement))),
				sizeof(TElement)*MoveCount
			);
		}		
		_length+= Count;
	}
	FORCEINLINE void CreateFromRange(const TElement* BeginPtr, uint32 inCount)
	{
		/*���� ��� ��� ����������, ������ � �������������� ������������ ���������� ���-�� ����� �� ���*/
		assert(_length == inCount);
		_length = inCount;
		Resize(_length);
		ConstructItems<TElement>(_allocator.GetData(), BeginPtr, _length);
	}

	FORCEINLINE void CheckState()
	{
		assert(_length <= _allocator.MaxSize() && _length >= 0);
	}

private:	
	TAllocator _allocator;
	uint32 _length;
};

template <typename T> struct fpIsfpArray { enum { Value = false }; };

template <typename TElement, typename TAllocator> struct fpIsfpArray<               fpArray<TElement, TAllocator>> { enum { Value = true }; };
template <typename TElement, typename TAllocator> struct fpIsfpArray<const          fpArray<TElement, TAllocator>> { enum { Value = true }; };
template <typename TElement, typename TAllocator> struct fpIsfpArray<      volatile fpArray<TElement, TAllocator>> { enum { Value = true }; };
template <typename TElement, typename TAllocator> struct fpIsfpArray<const volatile fpArray<TElement, TAllocator>> { enum { Value = true }; };

#endif //FLYPARTENGINE_FPARRAY_H