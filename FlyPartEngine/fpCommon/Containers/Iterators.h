#pragma once
#ifndef _ITERATORS_
#define _ITERATORS_
#include "../../Core/CoreAbstractLayer/CoreAbstractLayerInclude.h"
#include "../TypeTraits.h"
template<typename ContainerType,typename ElemType, typename IndexType>
class fpIndexedAraryIterator
{
	typedef fpIndexedAraryIterator<ContainerType, ElemType, IndexType>& SelfRef;
	typedef fpIndexedAraryIterator<ContainerType, ElemType, IndexType> const & ConstSelfRef;
	typedef fpIndexedAraryIterator<ContainerType, ElemType, IndexType> Self;
	typedef ContainerType& ContainerRefType;
public:
	fpIndexedAraryIterator(ContainerRefType inContainer, IndexType inStartPosition = 0)
		:_container(inContainer),
		_index(inStartPosition)
	{}
	SelfRef operator++()
	{
		++_index;
		return *this;
	}
	Self operator++(int)
	{
		Self temp(*this);
		++_index;
		return temp;
	}
	SelfRef operator--()
	{
		--_index;
		return *this;
	}
	Self operator--(int)
	{
		Self temp(*this);
		--_index;
		return temp;
	}
	SelfRef operator+=(int32 offset)
	{
		_index += offset;
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
		return _container[_index];
	}
	ElemType* operator-> () const
	{
		return &_container[_index];
	}
	IndexType GetIndex()const 
	{
		return _index;
	}
	void Reset()
	{
		_index = 0;
	}
	FORCEINLINE friend bool operator==(fpIndexedAraryIterator& Rhs, fpIndexedAraryIterator& Lhs)
	{
		return Rhs._container == Lhs._container && Rhs._index == Lhs._index;
	}
	FORCEINLINE friend bool operator!=(fpIndexedAraryIterator& Rhs, fpIndexedAraryIterator& Lhs)
	{
		return Rhs._container != Lhs._container || Rhs._index != Lhs._index;
	}
private:
	fpIndexedAraryIterator();
	ContainerRefType _container;
	IndexType _index;
};


#endif