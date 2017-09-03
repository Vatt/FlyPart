#pragma once
#ifndef _ITERATORS_
#define _ITERATORS_
#include "../../Core/CoreAbstractLayer/CoreAbstractLayerInclude.h"
#include "../TypeTraits.h"
template<typename ContainerType,typename ElemType, typename IndexType>
class fpIndexedAraryIterator
{
	typedef fpIndexedAraryIterator<ContainerType, ElemType, IndexType>& TSelfRef;
	typedef fpIndexedAraryIterator<ContainerType, ElemType, IndexType> const & TConstSelfRef;
	typedef fpIndexedAraryIterator<ContainerType, ElemType, IndexType> TSelf;
	typedef ContainerType& ContainerRefType;
public:
	fpIndexedAraryIterator(ContainerRefType inContainer, IndexType inStartPosition = 0)
		:_container(inContainer),
		_index(inStartPosition)
	{
		_container.IsValidIndex(_index);
	}
	TSelfRef operator++()
	{
		++_index;
		return *this;
	}
	TSelf operator++(int)
	{
		TSelf temp(*this);
		++_index;
		return temp;
	}
	TSelfRef operator--()
	{
		--_index;
		return *this;
	}
	TSelf operator--(int)
	{
		TSelf temp(*this);
		--_index;
		return temp;
	}
	TSelfRef operator+=(int32 offset)
	{
		_index += offset;
		return *this;
	}
	TSelf operator+(int32 offset) const
	{
		TSelf temp(*this);
		return temp += offset;
	}
	TSelfRef operator-=(int32 offset)
	{
		return *this += -offset;;
	}
	TSelf operator-(int32 offset)const
	{
		TSelf temp(*this);
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
	FORCEINLINE friend fpIndexedAraryIterator operator+(fpIndexedAraryIterator& Rhs, fpIndexedAraryIterator& Lhs)
	{
		assert(Rhs._container == Lhs._container);
		return fpIndexedAraryIterator(Rhs._container,Lhs._index+Rhs._index);
	}
	FORCEINLINE fpIndexedAraryIterator operator+(fpIndexedAraryIterator& Rhs)
	{
		assert(this->_container == Rhs._container);
		return fpIndexedAraryIterator(this->_container, this->_index + Rhs._index);
	}
	FORCEINLINE explicit operator bool()const
	{
		return _container.IsValidIndex(_index);
	}
	FORCEINLINE bool operator !()const
	{
		return !(bool)*this;
	}
private:
	fpIndexedAraryIterator() = delete;
	ContainerRefType _container;
	IndexType _index;
};


#endif