
#ifndef _FP_SHARED_PTR_
#define _FP_SHARED_PTR_
#pragma once
#include "SmartPtrPrivate.h"
#include "../Core/GenericPlatform/Memory/fpMemorySystem.h"
using namespace fpTemplate;


template <class ObjType,RefControllerMode Mode = RefControllerMode::Auto>
class fpSharedRef{
private:
	typedef fpSharedRef<ObjType, Mode> SelfType;
	typedef fpWeakRef<ObjType, Mode> WeakRefType;
public:
	template<class OtherType>
    inline explicit fpSharedRef(OtherType* InObj)
        :_controller(SmartPtrPrivate::MakeDefaultReferenceController(InObj))
	{
        Init(InObj);
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
    FORCEINLINE SelfType& operator=(fpSharedRef<ObjType,Mode>&& InReference)
	{       
        _controller = InReference._controller;
        _object = InReference._object;
        //fpMemorySystem::PlatformMemory()::MemSwap(this, &InReference, sizeof(fpSharedRef));
		return *this;
	}
    FORCEINLINE SelfType& operator=(fpSharedRef<ObjType,Mode>const& InReference)
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
    FORCEINLINE void Init(ObjType* InObj)
	{
        _object = InObj;
	}
	FORCEINLINE fpSharedRef& operator=(fpSharedRef<ObjType, Mode>& InReference);
	ObjType* _object;
	SmartPtrPrivate::fpSharedRefCounter<Mode> _controller;
};



template <class ObjType, RefControllerMode Mode = RefControllerMode::Auto>
class fpWeakRef
{
    typedef fpWeakRef<ObjType,Mode> SelfType;
	typedef fpSharedRef<ObjType, Mode> SharedType;
public:

    fpWeakRef(fpWeakRef const& InWeakRef)
        :_controller(InWeakRef._controller),
         _object(InWeakRef._object)
    {}
    fpWeakRef(fpWeakRef&& InWeakRef)
        :_controller(InWeakRef._controller),
         _object(InWeakRef._object)
    {}
	fpWeakRef(SharedType const& InSharedRef)
	{

	}
	fpWeakRef(SharedType&& InSharedRef)
	{

	}
    inline SelfType& operator=(fpWeakRef const& InWeakRef)
    {
		_controller = InWeakRef._controller;
		_object = InWeakRef._object;
    }
    inline SelfType& operator=(fpWeakRef&& InWeakRef)
    {
		_controller = InWeakRef._controller;
		_object = InWeakRef._object;
    }
    FORCEINLINE ObjType& Get()const
    {
        return *_object;
    }
    FORCEINLINE ObjType* operator->()const
    {
        return _object;
    }
    FORCEINLINE ObjType& operator*()const
    {
        return *_object;
    }
    FORCEINLINE int32 GetRefCount()const
    {
        return _controller.GetRefCount();
    }
	FORCEINLINE void Reset()
	{
	}
	FORCEINLINE SharedType Lock()
	{
	}
	FORCEINLINE const bool isValid()const
	{
		return _object != nullptr && _controller.isValid();
	}
private:
    FORCEINLINE void Init(ObjType* InObj)
    {
/*
* TODВставить проверку на не nullptr
*/
        _object = InObj;
    }

    ObjType* _object;
    SmartPtrPrivate::fpWeakRefCounter<Mode> _controller;
};

#endif
