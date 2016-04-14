
#ifndef _FP_SHARED_PTR_
#define _FP_SHARED_PTR_
#pragma once
#include "SmartPtrPrivate.h"
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
	template<class Othertype,class DeleterType>
	inline explicit fpSharedRef(Othertype* ptr, DeleterType deleter)
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
		return _controller->GetSharedRefCount();
	}
	~fpSharedRef() {
		
	}
private:
	ObjType* _object;
	fpSharedRefCounter* _controller;
};
#endif