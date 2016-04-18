
#ifndef _FP_SHARED_PTR_
#define _FP_SHARED_PTR_
#pragma once
#include "SmartPtrPrivate.h"
#include "../Core/GenericPlatform/Memory/fpMemorySystem.h"
using namespace fpTemplate;


template <class ObjType,RefControllerMode Mode = RefControllerMode::Auto>
class fpSharedRef{
private:
	typedef fpSharedRef<ObjType, Mode> Self;
public:
	template<class OtherType>
    inline explicit fpSharedRef(OtherType* InObj)
        :_controller(SmartPtrPrivate::MakeDefaultReferenceController(InObj)),
		 _object(InObj)
	{
		
	}
    template <class OtherType,class DeleterType>
    inline explicit fpSharedRef(OtherType* InObj, DeleterType deleter)
        :_controller(SmartPtrPrivate::MakeCustomReferenceController(InObj, deleter)),
		 _object(InObj)
	{}
/*    
	template<class OtherType>
	FORCEINLINE fpSharedRef(fpSharedRef<OtherType, Mode> const&  reference)
		: _controller(reference._controller), _object(reference._object)
	{}
	template<class OtherType>
	FORCEINLINE fpSharedRef(fpSharedRef<OtherType, Mode> const& InOtherRef, ObjType* InObj)
		: _object(InObj), _controller(InOtherRef._controller)
	{}
	template<class OtherType>
	FORCEINLINE fpSharedRef(fpSharedRef<OtherType, Mode>&& reference)
		: _controller(reference._controller), _object(reference._object)
	{}
*/
	
	FORCEINLINE fpSharedRef(fpSharedRef<ObjType,Mode> const&  reference)
        :_controller(reference._controller),_object(reference._object)
	{}
    FORCEINLINE fpSharedRef(fpSharedRef<ObjType,Mode> const& InOtherRef, ObjType* InObj)
        :_object(InObj),_controller(InOtherRef._controller)
    {}
    FORCEINLINE fpSharedRef(fpSharedRef<ObjType,Mode>&& reference)
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
    FORCEINLINE Self& operator=(fpSharedRef<ObjType,Mode>&& InReference)
	{       
        _controller = InReference._controller;
        _object = InReference._object;
        //fpMemorySystem::PlatformMemory()::MemSwap(this, &InReference, sizeof(fpSharedRef));
		return *this;
	}
    FORCEINLINE Self& operator=(fpSharedRef<ObjType,Mode>const& InReference)
    {
        _controller = InReference._controller;
        _object = InReference._object;
        return *this;
    }
	FORCEINLINE const int32 GetRefCount() const
	{
		return _controller.GetSharedRefCount();
	}
	FORCEINLINE bool isUnique()const
	{
		return _controller.isUnique();
	}
	~fpSharedRef() 
	{
			
	}
private:
	void Init(ObjType* InObj)
	{
	}
	FORCEINLINE fpSharedRef& operator=(fpSharedRef<ObjType, Mode>& InReference);
	ObjType* _object;
	SmartPtrPrivate::fpSharedRefCounter<Mode> _controller;
};



template <class ObjType, RefControllerMode Mode = RefControllerMode::Auto>
class fpWeakRef
{

};

#endif
