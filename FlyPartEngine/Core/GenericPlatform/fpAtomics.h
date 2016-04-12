#ifndef _FP_INCREMENT_INCLUDE_
#define _FP_INCREMENT_INCLUDE_
#include "../../fpCommon/typedefs.h"
#include "../../fpCommon/defines.h"
#ifdef PLATFORM_64
    #define ENABLE_64BITS_ATOMICS
#endif
class fpPlatformAtomicsImpl {
public:
    virtual FORCEINLINE int32 InterlockedIncrement(volatile int32* Addend) = 0;
    virtual FORCEINLINE int32 InterlockedDecrement(volatile int32* Addend) = 0;
    virtual FORCEINLINE int32 InterlockedAdd(volatile int32* Addend,int32 Value) = 0;
    virtual FORCEINLINE int32 InterlockedExchange(volatile int32* Target, int32 Value) = 0;
    virtual FORCEINLINE int32 InterlockedExchangeAdd(volatile int32* Addend, int32 Value) = 0;
#ifdef ENABLE_64BITS_ATOMICS
    virtual FORCEINLINE int64 InterlockedIncrement(volatile int64* Addend) = 0;
    virtual FORCEINLINE int64 InterlockedDecrement(volatile int64* Addend) = 0;
    virtual FORCEINLINE int64 InterlockedAdd(volatile int64* Addend,int64 Value) = 0;
    virtual FORCEINLINE int64 InterlockedExchange(volatile int64* Target, int64 Value) = 0;
#endif
	//virtual FORCEINLINE void* InterlockedExchangePointer(volatile void** Target, void* Value) = 0;
	virtual ~fpPlatformAtomicsImpl()=0;
};
class fpAtomics {
	friend class fpPlatformAtomicsImpl;
	static fpPlatformAtomicsImpl* _atomicsImpl;
public:
    static FORCEINLINE int32 InterlockedIncrement(volatile int32* Addend)
	{
        _atomicsImpl->InterlockedIncrement(Addend);
	}
    static FORCEINLINE int32 InterlockedDecrement(volatile int32* Addend)
    {
        _atomicsImpl->InterlockedDecrement(Addend);
    }
    /*static FORCEINLINE int32 InterlockedAdd(volatile int32* Addend, int32 Value)
    {
        _atomicsImpl->InterlockedAdd(Addend, Value);
    }*/
    static FORCEINLINE int32 InterlockedExchange(volatile int32* Target, int32 Value)
    {
        return _atomicsImpl->InterlockedExchange(Target, Value);
    }
    static FORCEINLINE int32 InterlockedExchangeAdd(volatile int32* Addend, int32 Value)
    {
        return _atomicsImpl->InterlockedExchangeAdd(Addend, Value);
    }

#ifdef ENABLE_64BITS_ATOMICS
    static FORCEINLINE int64 InterlockedIncrement(volatile int64* Addend)
	{
        _atomicsImpl->InterlockedIncrement(Addend);
	}
    static FORCEINLINE int64 InterlockedDecrement(volatile int64* Addend)
	{
        _atomicsImpl->InterlockedDecrement(Addend);
	}
    static FORCEINLINE int64 InterlockedAdd(volatile int64* Addend, int64 Value)
	{
        _atomicsImpl->InterlockedAdd(Addend, Value);
	}
    static FORCEINLINE int64 InterlockedExchange(volatile int64* Target, int64 Value)
	{
        return _atomicsImpl->InterlockedExchange(Target, Value);
	}
    static FORCEINLINE int64 InterlockedExchangeAdd(volatile int64* Addend, int64 Value)
	{
        return _atomicsImpl->InterlockedExchangeAdd(Addend, Value);
	}
#endif
};
#endif
