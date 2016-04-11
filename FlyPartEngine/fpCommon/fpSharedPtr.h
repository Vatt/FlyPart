
#ifndef _FP_SHARED_PTR_
#define _FP_SHARED_PTR_
#pragma once
#include "SmartPtrPrivate.h"
#include "NotNull.h"
#include "../Core/GenericPlatform/Memory/fpMemorySystem.h"
using namespace fpTemplate::SmartPtrPrivate;
template <class ObjType,RefControllerMode mode>
class fpSharedRef{
private:

public:
	inline explicit fpSharedRef(ObjType* ptr)
		:_controller(MakeDefaultReferenceController(ptr))
	{
		
	}
	template<class ObjType,class DeleterType>
	inline explicit fpSharedRef(ObjType* ptr, DeleterType deleter) 
		:_controller(MakeCustomReferenceController(ptr, deleter))
	{}
	FORCEINLINE fpSharedRef(fpSharedRef<ObjType>& const reference)
	{}
	FORCEINLINE fpSharedRef(fpSharedRef<ObjType>&& const reference) 
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
		return 0;
	}
	~fpSharedRef() {
		
	}
private:
	ObjType* _object;
	fpSharedRefController* _controller;
};
#endif