#pragma once
#ifndef _CONTAINER_BASE_
#define _CONTAINER_BASE_
#include "../../Core/CoreAbstractLayer/CoreAbstractLayerInclude.h"
#include "../TypeTraits.h"
template<typename ContainerType,typename ElemType, typename IndexType>
class fpIndexedIterator
{
	typedef fpIndexedIterator<ContainerType, ElemType, IndexType>& SelfRef;
	typedef fpIndexedIterator<ContainerType, ElemType, IndexType> const & SelfConstRef;
	typedef fpIndexedIterator<ContainerType, ElemType, IndexType> Self;
	typedef ContainerType& ContainerRefType;
public:
	fpIndexedIterator(ContainerRefType inContainer, IndexType inStartPosition = 0)
		:Container(inContainer),
		Index(inStartPosition)
	{}
	SelfRef operator++()
	{
		++Index;
		return *this;
	}
	Self operator++(int)
	{
		Self temp(*this);
		++Index;
		return temp;
	}
	SelfRef operator--()
	{
		--Index;
		return *this;
	}
	Self operator--(int)
	{
		Self temp(*this);
		--Index;
		return temp;
	}
	SelfRef operator+=(int32 offset)
	{
		Index += offset;
		return *this;
	}
	Self operator+(int32 offset) const
	{
		Self temp(*this);
		return temp += offset;
	}
	SelfRef operator-=(int32 offset)
	{
		return *this += -offset;;
	}
	Self operator-(int32 offset)const
	{
		Self temp(*this);
		return temp -= offset;
	}
	ElemType& operator* () const
	{
		return Container[Index];
	}
	ElemType* operator-> () const
	{
		return &Container[Index];
	}


	IndexType GetIndex()const 
	{
		return Index;
	}
	void Reset()
	{
		Index = 0;
	}
	
private:
	fpIndexedIterator();
	ContainerRefType Container;
	IndexType Index;
};

template <typename ElemType>
struct ArrayBase {
	ElemType* Data;
	fpAllocatorInterface* Allocator;
	uint32 Size;
	ArrayBase(uint32 size,fpAllocatorInterface* inAllocator = fpMemory::DefaultAllocator())
	{
		Allocator = inAllocator;
		Data = static_cast<ElemType*>(Allocator->Allocate(size * sizeof(ElemType)));
		Size = size;		
	}
	ArrayBase(ArrayBase const& other)
	{
		this->Data = other.Data;
		this->Size = other.Size;
		this->Allocator = other.Allocator;
	}
	ArrayBase(ArrayBase&& other)
	{
		this->Data = other.Data;
		this->Size = other.Size;
		this->Allocator = other.Allocator;
		other.Data = nullptr;
		other.Size = 0;
		other.Allocator = nullptr;
	}
	FORCEINLINE ElemType& operator[](uint32 index)
	{
		return *((ElemType*)((UINTPTR)Data + index * sizeof(ElemType)));
	}
	FORCEINLINE ElemType const & operator[](uint32 index)const
	{
		return *((ElemType*)((UINTPTR)Data + index * sizeof(ElemType)));
	}
	FORCEINLINE void  Resize(uint32 inNewSize)
	{
		Data = static_cast<ElemType*>(Allocator->Realloc(Data, inNewSize * sizeof(ElemType)));
		Size = inNewSize;
	}
	FORCEINLINE void Destroy()
	{
		Allocator->Free(Data,Size);
		Data = nullptr;
	}
	~ArrayBase()
	{
		Destroy();
	}
};
#endif