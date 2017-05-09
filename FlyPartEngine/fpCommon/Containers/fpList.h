#ifndef _FP_LIST_INCLUDE_
#define _FP_LIST_INCLUDE_
#pragma once
#include "../../Core/CoreAbstractLayer/CoreAbstractLayerInclude.h"
#include "../ClassMemoryOps.h"
#include "../TypeTraits.h"

template<typename NodeType, typename ElemType>
class fpDefaultListAllocator :public AllocatorBase<NodeType, uint32>
{
public:
	fpDefaultListAllocator()
		:_allocator(fpMemory::GetCommonHeap()->MakeAllocator())
	{
	}
	FORCEINLINE PointerType Allocate()
	{
		//int32 counter = (int32)Count;
		//NodeType* node = nullptr;
		//NodeType* OldNode;
		//while (counter>0)
		//{
		//	node = (NodeType*)_allocator->Allocate(sizeof(NodeType));
		//	new(node)NodeType();
		//	OldNode->Next = node;
		//	OldNode = node;
		//	--counter;
		//	++_size;
		//}
		//return node;
		return (PointerType)_allocator->Allocate(sizeof(NodeType));
	}
	FORCEINLINE void Deallocate(PointerType Ptr)
	{
		DestroyItems(Ptr, 1);
		_allocator->Free(Ptr, sizeof(NodeType));
	}
	~fpDefaultListAllocator()
	{

	}
private:
	fpAllocatorInterface* _allocator;
};

template<typename ElemType>
class fpSingleListNode
{
public:
	fpSingleListNode()
		:Next(nullptr)
	{}
	fpSingleListNode(const ElemType& Element)
		:Next(nullptr)
	{
		Data = Element;
	}
	fpSingleListNode(ElemType&& Element)
		:Next(nullptr)
	{
		Data = Element;
	}
	fpSingleListNode(const fpSingleListNode& other)
	{
		Next = other.Next;
		Data = other.Data;
	}
	fpSingleListNode(fpSingleListNode&& other)
		:Next(other.Next),Data(other.Data)
	{
		other.Next = nullptr;
		other.Data.ElemType::~ElemType();
	}
public:
	fpSingleListNode<ElemType>* Next;
	ElemType Data;

};

template<typename ElemType,typename AllocatorType=fpDefaultListAllocator<fpSingleListNode<ElemType>,ElemType>>
class fpList
{
public:
	fpList()
		:_length(0)
	{
		_head = _tail = _allocator.Allocate();
	}
private:
	AllocatorType _allocator;
	fpSingleListNode<ElemType>* _head;
	fpSingleListNode<ElemType>* _tail;
	uint32 _length;
};

#endif
