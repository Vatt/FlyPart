#pragma once
#ifndef _CONTAINER_BASE_
#define _CONTAINER_BASE_
#include "../../Core/CoreAbstractLayer/CoreAbstractLayerInclude.h"
#include "../TypeTraits.h"
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
		this->Data = other.data;
		this->Size = other.Size;
		this->Allocator = other.Allocator;
	}
	ArrayBase(ArrayBase&& other)
	{
		this->Data = other.data;
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
		Allocator->Realloc(Data, inNewSize * sizeof(ElemType));
		Size = inNewSize;
	}

	~ArrayBase()
	{
		Allocator->Free(Data,Size);
		Data = nullptr;
	}
};
#endif