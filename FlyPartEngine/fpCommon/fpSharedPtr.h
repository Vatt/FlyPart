
#ifndef _FP_SHARED_PTR_
#define _FP_SHARED_PTR_
#pragma once
#include "ReferenceCounter.h"
#include "NotNull.h"
#include "../Core/GenericPlatform/Memory/fpMemorySystem.h"

template <class ObjType>
class fpSharedRef{
private:

public:
	inline fpSharedRef(ObjType* ptr)
	{
		
	}
	FORCEINLINE fpSharedRef(fpSharedRef<ObjType>& const reference):_object(reference._object)
	{}
	FORCEINLINE fpSharedRef(fpSharedRef<ObjType>&& const reference) : _object(reference._object)
	{}

	FORCEINLINE ObjType& operator*()const{
		return *_object;
	}
	FORCEINLINE ObjType* operator->()const{
		return _object;
	}
	FORCEINLINE fpSharedRef& operator=(fpSharedRef<ObjType>&& InReference)
	{
		fpMemorySystem::PlatformMemory()::MemSwap(this, &InReference, sizeof(fpSharedRef));
		return *this;
	}

	FORCEINLINE const int32 GetRefCount() const
	{
		return _refCounter.RefCount();
	}
	~fpSharedRef() {
		_refCounter.DecrementCounter();
	}
private:
	ObjType* _object;
	fpSharedRefCounter _refCounter;
};
#endif