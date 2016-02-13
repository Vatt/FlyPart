
#ifndef _FP_SHARED_PTR_
#define _FP_SHARED_PTR_
#pragma once
#include "Reference.h"
#include "NotNull.h"
#include "../Core/GenericPlatform/Memory/fpMemorySystem.h"
enum ReferenceType {
	CONST,
	COMMON,
};

template <class ObjType,typename ReferenceType=COMMON>
class fpSharedRef:public Reference<ObjType>{
private:

public:
	inline fpSharedRef(ObjType* ptr)
	{
		
	}
	inline fpSharedRef(fpSharedRef<ObjType>& const reference):_object(reference._object)
	{}
	inline fpSharedRef(fpSharedRef<ObjType>&& const reference) : _object(reference._object)
	{}
	inline fpSharedRef& operator =(fpSharedRef<ObjType>&& reference)
	{
		fpMemorySystem::PlatformMemory()::MemSwap(this, &InSharedRef, sizeof(TSharedRef));
		return *this;
	}
	void operator delete(){
		DeleteRef();
	}
};
#endif