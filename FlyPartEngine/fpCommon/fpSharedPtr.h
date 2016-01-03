
#ifndef _FP_SHARED_PTR_
#define _FP_SHARED_PTR_
#pragma once
#include "Reference.h"
#include "NotNull.h"
template <class ObjType>
class fpSharedRef:public Reference<ObjType>{
private:

public:
	fpSharedRef() {
		ObjType* ptr = new ObjType();
		_object = NotNullPtr<ObjType>(ptr);
	}
	explicit fpSharedRef(ObjType* ptr)
	{
		_object = NotNullPtr<ObjType>(ptr);
	}
	fpSharedRef(fpSharedRef<ObjType>& const reference) {
		_object = reference._object;
	}

	void operator delete(){
		DeleteRef();
	}
private:
	NotNullPtr<ObjType> _object;

};
#endif