#ifndef _FP_LIST_INCLUDE_
#define _FP_LIST_INCLUDE_
#pragma once
#include "../../Core/CoreAbstractLayer/CoreAbstractLayerInclude.h"
#include "../ClassMemoryOps.h"
#include "../TypeTraits.h"

template<typename TContainerNode>
class fpLinkedListIteratorBase
{
public:
	fpLinkedListIteratorBase(TContainerNode* head, TContainerNode* node)
		:_headNode(head),_currentNode(node)
	{
	}
	FORCEINLINE void MoveNext()
	{
		if (_currentNode->Next==_headNode)
		{
			_currentNode = nullptr;
			return;
		}
        _currentNode = _currentNode->Next;
	}
	FORCEINLINE void MovePrev()
	{
		_currentNode = _currentNode->Prev;
	}
    FORCEINLINE void Reset()
    {
        _currentNode = _headNode;
    }
	FORCEINLINE TContainerNode* GetNode()
	{
		return _currentNode;
	}
	FORCEINLINE explicit virtual operator bool() const
	{
		return _currentNode!=nullptr;
	}
protected:
	TContainerNode* _currentNode;
	TContainerNode* _headNode;
	FORCEINLINE friend bool operator==(const fpLinkedListIteratorBase& Lhs, const fpLinkedListIteratorBase& Rhs)
    {
        return Lhs._currentNode == Rhs._currentNode;
    }
	FORCEINLINE friend bool operator!=(const fpLinkedListIteratorBase& Lhs, const fpLinkedListIteratorBase& Rhs)
    {
        return Lhs._currentNode != Rhs._currentNode;
    }
};

template<typename TContainerNode,typename TElement>
class fpLinkedListIterator: public fpLinkedListIteratorBase<TContainerNode>
{
	typedef fpLinkedListIteratorBase<TContainerNode> Base;
public:
	fpLinkedListIterator(TContainerNode* head, TContainerNode* node)
		:Base(head,node)
	{ }
    FORCEINLINE TElement* operator->() const
	{
		assert(this->_currentNode != nullptr);
		return &this->_currentNode->Data;
	}
	FORCEINLINE TElement& operator*()const
	{
		assert(this->_currentNode != nullptr);
		return this->_currentNode->Data;
	}
    FORCEINLINE fpLinkedListIterator& operator++()
    {
        this->MoveNext();
        return *this;
    }
    FORCEINLINE fpLinkedListIterator operator++(int32)
    {
        auto tmp = *this;
        this->MoveNext();
        return tmp;
    }
    FORCEINLINE fpLinkedListIterator& operator--()
    {
        this->MovePrev();
        return *this;
    }
    FORCEINLINE fpLinkedListIterator operator--(int32)
    {
        auto tmp = *this;
        this->MovePrev();
        return tmp;
    }
};
template<typename TContainerNode,typename TElement>
class fpLinkedListReverseIterator:public fpLinkedListIteratorBase<TContainerNode>
{
	typedef fpLinkedListIteratorBase<TContainerNode> Base;
public:
	fpLinkedListReverseIterator(TContainerNode* head,TContainerNode* node)
			:Base(head,node)
	{

	}
    FORCEINLINE TElement* operator->() const
    {
        assert(this->_currentNode != nullptr);
        return &this->_currentNode->Data;
    }
    FORCEINLINE TElement& operator*()const
    {
        assert(this->_currentNode != nullptr);
        return this->_currentNode->Data;
    }
    FORCEINLINE fpLinkedListReverseIterator& operator++()
    {
        this->MovePrev();
        return *this;
    }
    FORCEINLINE fpLinkedListReverseIterator operator++(int32)
    {
        auto tmp = *this;
        this->MovePrev();
        return tmp;
    }
    FORCEINLINE fpLinkedListReverseIterator& operator--()
    {
        this->MoveNext();
        return *this;
    }
    FORCEINLINE fpLinkedListReverseIterator operator--(int32)
    {
        auto tmp = *this;
        this->MoveNext();
        return tmp;
    }
    FORCEINLINE explicit operator bool() const override
    {
        return this->_currentNode!=this->_headNode;
    }
};

template<typename TNodeElement>
class fpDoubleLinkedNode
{
public:
	fpDoubleLinkedNode()
			:Next(nullptr),Prev(nullptr)
	{}
    explicit fpDoubleLinkedNode(const TNodeElement& Element)
            :Data(Element),Next(nullptr),Prev(nullptr)
    {}
    ~fpDoubleLinkedNode()
    {
        //TODO: проверить верность уничтожения элемента
        DestroyItems(&Data,1);
    }
public:
    TNodeElement Data;
    fpDoubleLinkedNode<TNodeElement>* Next;
    fpDoubleLinkedNode<TNodeElement>* Prev;
};
/*
 * Double linked list
 */
template<typename TElement>
class fpLinkedList
{
private:
	template <typename TIteratorNode,typename TIteratorElement>
	class fpRangedForIterator:public fpLinkedListIteratorBase<TIteratorNode>
	{
		typedef fpLinkedListIteratorBase<TIteratorNode> Base;
	public:
		explicit fpRangedForIterator(TIteratorNode* head,TIteratorNode* node)
			:Base(head,node)
		{}
		FORCEINLINE TIteratorElement& operator*()const
		{
			return this->_currentNode->Data;
		}
        FORCEINLINE fpRangedForIterator& operator++()
        {
            this->MoveNext();
            return *this;
        }
        FORCEINLINE fpRangedForIterator operator++(int32)
        {
            auto tmp = *this;
            this->MoveNext();
            return tmp;
        }
        FORCEINLINE fpRangedForIterator& operator--()
        {
            this->MovePrev();
            return *this;
        }
        FORCEINLINE fpRangedForIterator operator--(int32)
        {
            auto tmp = *this;
            this->MovePrev();
            return tmp;
        }
	};
    typedef fpRangedForIterator<fpDoubleLinkedNode<TElement>,TElement> TRangedForIterator;
    typedef fpRangedForIterator<fpDoubleLinkedNode<const TElement>,const TElement> TConstRangedForIterator;
public:
	typedef fpDoubleLinkedNode<TElement> TNode;
	typedef fpDoubleLinkedNode<const TElement> TConstNode;
	typedef fpDoubleLinkedNode<TElement>* TNodePointer;


	typedef fpLinkedListIterator<TNode, TElement> TIterator;
	typedef fpLinkedListIterator<TConstNode, const TElement> TConstIterator;
	typedef fpLinkedListReverseIterator<TNode,TElement> TReverseIterator;
	typedef fpLinkedListReverseIterator<TNode,const TElement> TConstReverseIterator;
public:
	fpLinkedList()
		:_length(0),_allocator(fpMemory::DefaultAllocator()),_head(nullptr)
	{
	}
	fpLinkedList(fpAllocatorInterface* Allocator)
		:_length(0), _allocator(Allocator),_head(nullptr)
	{
	}
	~fpLinkedList()
	{
        for(auto it = CreateIterator();it;it++)
        {
            DestructOne(it.GetNode());
            _allocator->Free(it.GetNode(),sizeof(TNode));
        }
        _length=0;
        _head = nullptr;
	}
public:
	FORCEINLINE TNodePointer Front()const
	{
		return _head;
	}
	FORCEINLINE TNodePointer Back()const
	{
		return _head->Prev == nullptr ? nullptr : _head->Prev;
	}
	void PushFront(TNodePointer Node)
	{
		assert(Node != nullptr);
		if (_head == nullptr)
		{
			_head = Node;
			_head->Next = _head;
			_head->Prev = _head;
		}
		else 
		{
			/*
			if (_head->Prev == nullptr)
			{
				_head->Prev = _head;
				_head = Node;
				Node->Prev = _head;
				
			}
			else 
			{
				_head->Prev->Next = Node;
				Node->Prev = _head->Prev;
				Node->MoveNext = _head;
				_head->Prev = Node;
				_head = Node;
			}
			*/
			_head->Prev->Next = Node;
			Node->Prev = _head->Prev;
			Node->Next = _head;
			_head->Prev = Node;
			_head = Node;

		}
		_length += 1;
	}
	FORCEINLINE void  PushFront(const TElement& Element)
	{
		PushFront(AllocateOneInit(Element));
	}
    FORCEINLINE void  PushFront(TElement&& Element)
    {
        PushFront(AllocateOneInit(fpTemplate::fpMove(Element)));
    }
	void PushBack(TNodePointer Node)
	{
		assert(Node != nullptr);
		if (_head == nullptr)
		{
			_head = Node;
			_head->Next = _head;
			_head->Prev = _head;
		}else
        {
            _head->Prev->Next = Node;
            Node->Prev = _head->Prev;
            Node->Next = _head;
            _head->Prev = Node;
        }
		_length+=1;
	}
	FORCEINLINE void PushBack(TElement&& Element)
	{
		PushBack(AllocateOneInit(fpTemplate::fpMove(Element)));
	}
	FORCEINLINE void PushBack(const TElement& Element)
	{
		PushBack(AllocateOneInit(Element));
	}
    FORCEINLINE void LinkBefore(TNodePointer target,TNodePointer node)
    {
        node->Next = target;
        node->Prev = target->Prev;
        target->Prev->Next = node;
        target->Prev = node;
        _length += 1;
    }
    bool isEmpty()
    {
        return _length == 0;
    }
    uint32 Length()
    {
        return _length;
    }
    FORCEINLINE void LinkBefore(TNodePointer target,const TElement& element)
    {
        LinkBefore(target,AllocateOneInit(element));
    }
    FORCEINLINE void LinkAfter(TNodePointer target,TNodePointer node)
    {
        LinkBefore(target->Next,node);
    }
    FORCEINLINE void LinkAfter(TNodePointer target,const TElement& element)
    {
        LinkBefore(target->Next,element);
    }

    /*
     * DO NOT USE DIRECTLY
     * */
	TRangedForIterator begin()const
	{
		return TRangedForIterator(Front(), Front());
	}
    /*
    * DO NOT USE DIRECTLY
    */
	TRangedForIterator end()const
	{
		/*
		 * TODO: Пахнет грязным хаком
		 *       но поскольку у нас нет заглушки и мы зациклены,
         *       а стандарт требует конечного итератора тогда: и так сойдет(с)
         */
		return TRangedForIterator(Front(), nullptr);
	}
    /*
    * DO NOT USE DIRECTLY
    */
	TConstRangedForIterator cbegin()const
	{
		return TConstRangedForIterator(Front(), Front());
	}
    /*
    * DO NOT USE DIRECTLY
    */
	TConstRangedForIterator cend()const
	{
		return TConstRangedForIterator(Front(), Back());
	}

	TIterator CreateIterator()const
	{
		return TIterator(Front(), Front());
	}
	TConstIterator CreateConstIterator()const
	{
		return TConstIterator(Front(), Front());
	}
	TReverseIterator CreateReverseIterator()const
	{
		return TReverseIterator(Front(), Back());
	}
	TConstReverseIterator CreateConstReverseIterator()const
	{
		return TConstReverseIterator(Front(), Back());
	}


private:
	FORCEINLINE TNodePointer AllocateOneInit(TElement&& Element)
	{
		TNodePointer node = static_cast<TNodePointer>(_allocator->Allocate(sizeof(TNode)));
		new(node)TElement(fpTemplate::fpMove(Element));
		return node;
	}
	FORCEINLINE TNodePointer AllocateOneInit(const TElement& Element)
	{
		TNodePointer node = static_cast<TNodePointer>(_allocator->Allocate(sizeof(TNode)));
		new(node)TElement(Element);
		return node;
	}
    FORCEINLINE void DestructOne(TNodePointer node)
    {
        node->TNode::~TNode();
    }
private:
	fpAllocatorInterface* _allocator;
	TNodePointer _head;
	uint32 _length;
};

#endif

#pragma clang diagnostic pop