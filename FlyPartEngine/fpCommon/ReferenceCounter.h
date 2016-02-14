
#ifndef _REFERENCE_COUNTER_
#define _REFERENCE_COUNTER_
#pragma once
#include "typedefs.h"
#include "../Core/CoreCommonHeader.h"
#define FORCE_THREADSAFE_REFERENCE 0

enum RefControllerMode {
	ThreadSafe = 0,
	NotThreadSafe = 1,
	Optional = FORCE_THREADSAFE_REFERENCE ? 0:1,
};
class fpRefControllerBase{
public:
	FORCEINLINE explicit fpRefControllerBase(void *obj):
		SharedReferenceCount(1),
		WeakReferenceCount(1),
		Object(obj)
	{}
	int32 SharedReferenceCount;
	int32 WeakReferenceCount;
	void* Object;
	virtual void DestroyObj() = 0;
	virtual ~fpRefControllerBase() {};
private:
	fpRefControllerBase(fpRefControllerBase& const);
	fpRefControllerBase& operator=(fpRefControllerBase& const);
};
template<typename ObjType, typename DeleterType>
class fpRefControllerWithDeleter:public fpRefControllerBase,private DeleterType
{
	explicit fpRefControllerWithDeleter(void* obj, DeleterType&& deleter) :
		fpRefControllerBase(obj), DeleterType(std::move(deleter))
	{}
	virtual void DestroyObj() {
		(*static_cast<DeleterType*>(this))((ObjType*)static_cast<fpRefControllerBase*>(this)->Object);
	}
};
template<RefControllerMode Mode>
class fpSharedRefCounter {
private:
	fpSharedRefCounter(fpSharedRefCounter&&);
public:
	fpSharedRefCounter() :refCount(1) {}
	fpSharedRefCounter(fpSharedRefCounter& const inRefCoounter) :refCount(inRefCoounter.refCount) {}
	int32 IncrementCounter() { return fpAtomics::InterlockedIncrement_i32(&refCount); }
	int32 DecrementCounter() { return fpAtomics::InterlockedDecrement_i32(&refCount); }
	const int32 RefCount()const { return this->refCount; }
private:
};
#endif