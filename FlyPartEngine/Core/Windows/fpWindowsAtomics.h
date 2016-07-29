#ifndef _FP_WINDOWS_INCREMENT_INCLUDE_
#define _FP_WINDOWS_INCREMENT_INCLUDE_
#include "../GenericPlatform/fpPlatformAtomics.h"
#include <Windows.h>
struct fpWindowsPlatformAtomics:public fpPlatformAtomics{
    static FORCEINLINE int32 InterlockedIncrement(volatile int32* Addend)
    {
        return (int32)::InterlockedIncrement((LPLONG)Addend);
    }
    static FORCEINLINE int32 InterlockedDecrement(volatile int32* Addend)
    {
        return (int32)::InterlockedDecrement((LPLONG)Addend);
    }
    static FORCEINLINE int32 InterlockedAdd(volatile int32* Addend, int32 Value)
    {
        return (int32)::InterlockedExchangeAdd((LPLONG)Addend, (LONG)Value);
    }
    static FORCEINLINE int32 InterlockedExchange(volatile int32* Target, int32 Value)
    {
        return (int32)::InterlockedExchange((LPLONG)Target, Value);
    }

#ifdef ENABLE_64BITS_ATOMICS
    static FORCEINLINE int64 InterlockedIncrement(volatile int64* Addend)
    {
        return (int64)::InterlockedIncrement64((LONGLONG*)Addend);
    }
    static FORCEINLINE int64 InterlockedDecrement(volatile int64* Addend)
    {
        return (int64)::InterlockedDecrement64((LONGLONG*)Addend);
    }
    static FORCEINLINE int64 InterlockedAdd(volatile int64* Addend, int64 Value)
    {
        return (int64)::InterlockedExchangeAdd64((LONG64*)Addend, (LONG64)Value);
    }
    static FORCEINLINE int64 InterlockedExchange(volatile int64* Target, int64 Value)
    {
        return (int64)::InterlockedExchange64((LONGLONG*)Target, Value);
    }

#endif
};
typedef fpWindowsPlatformAtomics fpAtomics;
#endif
