#ifndef _DEREF_INLUDE_
#define _DEREF_INCLUDE_
#pragma once
#include "ReferenceCounter.h"
template<class ObjType> 
class Reference
{

	fpSharedRefCounter _refCounter;	
public:
	Reference()
	virtual ObjType& GetRef() {
		_refCounter.IncrementCounter();
	};
	virtual void DeleteRef() {
		if (_refCounter.DecrementCounter() == 0)
		{

		}
		
	}
};
template<class ObjType>
class ConstReference
{
private:

public:
	virtual const ObjType& ConstGetRef() const = 0 ;
	virtual void DeleteRef() = 0;
};
#endif