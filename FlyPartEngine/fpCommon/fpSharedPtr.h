
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
    inline explicit fpSharedRef(ObjType* InObj)
        :_controller(MakeDefaultReferenceController(InObj))
	{
		
	}
    template <class OtherType,class DeleterType>
    inline explicit fpSharedRef(OtherType* InObj, DeleterType deleter)
        :_controller(MakeCustomReferenceController(InObj, deleter))
	{}
    template<class OtherType>
    FORCEINLINE fpSharedRef(fpSharedRef<OtherType,mode> const&  reference)
        :_controller(reference._controller),_object(reference._object)
	{}
    template<class OtherType>
    FORCEINLINE fpSharedRef(fpSharedRef<OtherType,mode> const& InOtherRef, ObjType* InObj)
        :_object(InObj),_controller(InOtherRef._controller)
    {}
    template<class OtherType>
    FORCEINLINE fpSharedRef(fpSharedRef<OtherType,mode>&& reference)
        :_controller(reference._controller),_object(reference._object)
    {}
    FORCEINLINE ObjType& Get()const{
        return *_object;
    }
	FORCEINLINE ObjType& operator*()const{
		return *_object;
	}
	FORCEINLINE ObjType* operator->()const{
		return _object;
	}
    FORCEINLINE fpSharedRef& operator=(fpSharedRef<ObjType,mode>&& InReference)
	{       
        _controller = InReference._controller;
        _object = InReference._object;
        //fpMemorySystem::PlatformMemory()::MemSwap(this, &InReference, sizeof(fpSharedRef));
		return *this;
	}
    FORCEINLINE fpSharedRef& operator=(fpSharedRef<ObjType,mode> const& InReference)
    {
        _controller = InReference._controller;
        _object = InReference._object;
        return *this;
    }
    /*
    *   pls, don't use this
    */
	FORCEINLINE const int32 GetRefCount() const
	{
		return _controller->GetSharedRefCount();
	}
	~fpSharedRef() {
		
	}
private:
	ObjType* _object;
    fpSharedRefCounter<mode>* _controller;
};
#endif
