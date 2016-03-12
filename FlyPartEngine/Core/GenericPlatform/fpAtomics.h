#ifndef _FP_INCREMENT_INCLUDE_
#define _FP_INCREMENT_INCLUDE_
#include "../../fpCommon/typedefs.h"
#include "../../fpCommon/defines.h"
class fpPlatformAtomicsImpl {
public:
	virtual FORCEINLINE int32 InterlockedIncrement_i32(volatile int32* Addend) = 0;
	virtual FORCEINLINE int64 InterlockedIncrement_i64(volatile int64* Addend) = 0;

	virtual FORCEINLINE int32 InterlockedDecrement_i32(volatile int32* Addend) = 0;
	virtual FORCEINLINE int64 InterlockedDecrement_i64(volatile int64* Addend) = 0;

	virtual FORCEINLINE int32 InterlockedAdd_i32(volatile int32* Addend,int32 Value) = 0;
	virtual FORCEINLINE int64 InterlockedAdd_i64(volatile int64* Addend,int64 Value) = 0;


	virtual FORCEINLINE int32 InterlockedExchange_i32(volatile int32* Target, int32 Value) = 0;
	virtual FORCEINLINE int64 InterlockedExchange_i64(volatile int64* Target, int64 Value) = 0;

	virtual FORCEINLINE int32 InterlockedExchangeAdd_i32(volatile int32* Addend, int32 Value) = 0;
	virtual FORCEINLINE int64 InterlockedExchangeAdd_i64(volatile int64* Addend, int64 Value) = 0;

	//virtual FORCEINLINE void* InterlockedExchangePointer(volatile void** Target, void* Value) = 0;
	virtual ~fpPlatformAtomicsImpl()=0;
};
class fpAtomics {
	friend class fpPlatformAtomicsImpl;
	static fpPlatformAtomicsImpl* _atomicsImpl;
public:
	static FORCEINLINE int32 InterlockedIncrement_i32(volatile int32* Addend)
	{
		_atomicsImpl->InterlockedIncrement_i32(Addend);
	}
	static FORCEINLINE int64 InterlockedIncrement_i64(volatile int64* Addend)
	{
		_atomicsImpl->InterlockedIncrement_i64(Addend);
	}

	static FORCEINLINE int32 InterlockedDecrement_i32(volatile int32* Addend)
	{
		_atomicsImpl->InterlockedDecrement_i32(Addend);
	}
	static FORCEINLINE int64 InterlockedDecrement_i64(volatile int64* Addend)
	{
		_atomicsImpl->InterlockedDecrement_i64(Addend);
	}

	static FORCEINLINE int32 InterlockedAdd_i32(volatile int32* Addend, int32 Value)
	{
		_atomicsImpl->InterlockedAdd_i32(Addend, Value);
	}
	static FORCEINLINE int64 InterlockedAdd_i64(volatile int64* Addend, int64 Value)
	{
		_atomicsImpl->InterlockedAdd_i64(Addend, Value);
	}
	static FORCEINLINE int32 InterlockedExchange_i32(volatile int32* Target, int32 Value)
	{
		return _atomicsImpl->InterlockedExchange_i32(Target, Value);
	}
	static FORCEINLINE int64 InterlockedExchange_i64(volatile int64* Target, int64 Value)
	{
		return _atomicsImpl->InterlockedExchange_i64(Target, Value);
	}

	static FORCEINLINE int32 InterlockedExchangeAdd_i32(volatile int32* Addend, int32 Value)
	{
		return _atomicsImpl->InterlockedExchangeAdd_i32(Addend, Value);
	}
	static FORCEINLINE int64 InterlockedExchangeAdd_i64(volatile int64* Addend, int64 Value)
	{
		return _atomicsImpl->InterlockedExchangeAdd_i64(Addend, Value);
	}
};
#endif