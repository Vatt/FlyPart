#ifndef _FP_LIST_INCLUDE_
#define _FP_LIST_INCLUDE_
#pragma once
#include "../../Core/CoreAbstractLayer/CoreAbstractLayerInclude.h"
#include "../ClassMemoryOps.h"
#include "../TypeTraits.h"
template<typename NodeType, typename ElemType>
class fpDefaultListLikeAllocator :public AllocatorBase<NodeType, uint32>
{
public:
	fpDefaultListLikeAllocator()
		:_allocator(fpMemory::GetCommonHeap()->MakeAllocator()),
		_size(0)
	{
		Allocate(_size);
	}
	FORCEINLINE PointerType Allocate(uint32 Count)
	{
		int32 counter = (int32)Count;
		NodeType* node = (NodeType*)_allocator->Allocate(sizeof(NodeType));
		new(node)NodeType();
		++_size;
		--counter;
		NodeType* OldNode = node;
		while (counter>0)
		{
			NodeType* NewNode = (NodeType*)_allocator->Allocate(sizeof(NodeType));
			new(NewNode)NodeType();
			OldNode->Next = NewNode;
			OldNode = NewNode;
			--counter;
			++_size;
		}
		return node;
	}
	FORCEINLINE void Deallocate(PointerType Ptr, uint32 Count)
	{

	}

	FORCEINLINE void Shrink(uint32 RealLength)
	{

	}
	FORCEINLINE uint32 MaxSize()const
	{
		return _size;
	}
	~fpDefaultListLikeAllocator()
	{

	}
	FORCEINLINE void FreeData()
	{
		static_assert(true, "fpDefaultListLikeAllocator::FreeData never used for list like allcoators");
	}
	FORCEINLINE NodeType* ReallocateData(uint32 inNewSize)
	{
		static_assert(true, "fpDefaultListLikeAllocator::ReallocateData never used for list like allcoators");
	}
private:
	fpAllocatorInterface* _allocator;
	uint32 _size;
};

template<typename ElemType>
struct fpListNode
{
	ElemType Data;
	fpListNode<ElemType>* Next;
	fpListNode()
		:Next(nullptr)
	{}
	fpListNode(const ElemType& Element)
		:Next(nullptr)
	{
		Data = Element;
	}
	fpListNode(ElemType&& Element)
		:Next(nullptr)
	{
		Data = Element;
	}
};

template<typename ElemType,typename AllocatorType=fpDefaultListLikeAllocator<fpListNode<ElemType>,ElemType>>
class fpList
{
public:
	fpList()
		:_length(0)
	{
	}
private:
	AllocatorType _allocator;
	fpListNode<ElemType>* _first;
	uint32 _length;
};
#endif
