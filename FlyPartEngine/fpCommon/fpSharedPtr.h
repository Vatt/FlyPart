
#ifndef _FP_SHARED_PTR_
#define _FP_SHARED_PTR_
#pragma once
#include "SmartPtrPrivate.h"
#include "../Core/GenericPlatform/Memory/fpMemorySystem.h"
using namespace fpTemplate;
template <class ObjType, RefControllerMode Mode> class fpWeakPtr;
template <class ObjType,RefControllerMode Mode = RefControllerMode::Auto>
class fpSharedRef{
private:
	typedef fpSharedRef<ObjType, Mode> SelfType;
    typedef fpWeakPtr<ObjType, Mode> WeakPtrType;
	template<class OtherObjType,RefControllerMode OtherMode> friend class fpWeakPtr;
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
	
	FORCEINLINE fpSharedRef(SelfType const&  reference)
        :_controller(reference._controller),_object(reference._object)
	{}
    FORCEINLINE fpSharedRef(SelfType const& InOtherRef, ObjType* InObj)
        :_object(InObj),_controller(InOtherRef._controller)
    {}
    FORCEINLINE fpSharedRef(SelfType&& reference)
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
    FORCEINLINE SelfType& operator=(SelfType&& InReference)
	{       
        _controller = InReference._controller;
        _object = InReference._object;
        //fpMemorySystem::PlatformMemory()::MemSwap(this, &InReference, sizeof(fpSharedRef));
		return *this;
	}
    FORCEINLINE SelfType& operator=(SelfType const& InReference)
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
	FORCEINLINE fpSharedRef& operator=(SelfType& InReference);
	ObjType* _object;
	SmartPtrPrivate::fpSharedRefCounter<Mode> _controller;
};



template <class ObjType, RefControllerMode Mode = RefControllerMode::Auto>
class fpWeakPtr
{
    typedef fpWeakPtr<ObjType,Mode> SelfType;
public:

    fpWeakPtr(fpWeakPtr const& InWeakPtr)
        :_controller(InWeakPtr._controller),
         _object(InWeakPtr._object)
    {}
    fpWeakPtr(fpWeakPtr&& InWeakPtr)
        :_controller(InWeakPtr._controller),
         _object(InWeakPtr._object)
    {}
    fpWeakPtr(fpSharedRef<ObjType,Mode> const& InSharedRef)
		:_controller(InSharedRef._controller),
		 _object(InSharedRef._object)
	{}

    inline SelfType& operator=(fpWeakPtr const& InWeakRef)
    {
		_controller = InWeakRef._controller;
		_object = InWeakRef._object;
    }
    inline SelfType& operator=(fpWeakPtr&& InWeakRef)
    {
		_controller = InWeakRef._controller;
		_object = InWeakRef._object;
    }

  /*  inline SelfType& operator=(fpSharedRef<ObjType> const& InSharedRef)
    {
        _controller = InSharedRef._controller;
        _object = InSharedRef._object;
    }
    inline SelfType& operator=(fpSharedRef<ObjType>&& InSharedRef)
    {
        _controller = InSharedRef._controller;
        _object = InSharedRef._object;
    }*/

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
        return _controller.GetWeakRefCount();
    }
	FORCEINLINE void Reset()
	{
	}
    FORCEINLINE fpSharedRef<ObjType,Mode> Lock()
	{
	}
	FORCEINLINE const bool isValid()const
	{
		return _object != nullptr && _controller.isValid();
	}
private:

    ObjType* _object;
    SmartPtrPrivate::fpWeakRefCounter<Mode> _controller;
};

#endif
