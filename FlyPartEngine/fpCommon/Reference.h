#ifndef _REFERENCE_INCLUDE_
#define _REFERENCE_INCLUDE_
#pragma once
#include "ReferenceCounter.h"

template<class ObjType> 
class Reference
{
	ObjType* _object;
	fpSharedRefCounter _refCounter;	
public:

	FORCEINLINE ObjType& GetRef() {
		_refCounter.IncrementCounter();
	};
	FORCEINLINE void DeleteRef() {
		if (_refCounter.DecrementCounter() == 0)
		{
			delete _object;
			return; 
		}
		
	}
	FORCEINLINE int32 Count() {
		return _refCounter.RefCount();
	}
protected:
	/*
	* for the heirs
	*/
	FORCEINLINE ObjType* GetObjectPointer() {
		return _object;
	}
private:
	Reference();
};
/*template<class ObjType>
class ConstReference
{
private:

public:
	FORCEINLINE const ObjType& GetRef() const;
	void DeleteRef();
};*/
#endif