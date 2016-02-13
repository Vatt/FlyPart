#ifndef _NOT_NULL_INCLUDE_
#define _NOT_NULL_INCLUDE_
#pragma once
#include <assert.h>
template<typename ObjType>
class NotNullPtr {

public:
	NotNullPtr(NotNullPtr&&);
	NotNullPtr(const NotNullPtr&  InPtr) :_object(InPtr._object) {}
	NotNullPtr(ObjType* obj)
	{
		static_assert(_object != nullptr);
		assert(_object!=nullptr);
		_object = obj;
	}
	ObjType* get() { 
		assert(_object != nullptr);
		return _object; 
	}
private:
	ObjType* _object;
};
#endif 
