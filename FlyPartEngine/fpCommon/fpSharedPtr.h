
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
    template <class OtherType,class DeleterType>
    inline explicit fpSharedRef(OtherType* ptr, DeleterType deleter)
		:_controller(MakeCustomReferenceController(ptr, deleter))
	{}
    template<class OtherType>
    FORCEINLINE fpSharedRef(fpSharedRef<OtherType,mode> const&  reference)
	{}
    FORCEINLINE fpSharedRef(fpSharedRef<ObjType,mode>&& reference)
	{}

	FORCEINLINE ObjType& operator*()const{
		return *_object;
	}
	FORCEINLINE ObjType* operator->()const{
		return _object;
	}
    FORCEINLINE fpSharedRef& operator=(fpSharedRef<ObjType,mode>&& InReference)
	{
        //fpMemorySystem::PlatformMemory()::MemSwap(this, &InReference, sizeof(fpSharedRef));
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
    fpSharedRefCounter<mode>* _controller;
};
#endif
