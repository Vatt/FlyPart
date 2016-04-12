#ifndef _FP_WINDOWS_INCREMENT_INCLUDE_
#define _FP_WINDOWS_INCREMENT_INCLUDE_
#include "../GenericPlatform/fpAtomics.h"

class fpWindowsAtomics:public fpPlatformAtomicsImpl {
public:
    FORCEINLINE int32 InterlockedIncrement(volatile int32* Addend)override;
    FORCEINLINE int32 InterlockedDecrement(volatile int32* Addend)override;
    FORCEINLINE int32 InterlockedAdd(volatile int32* Addend, int32 Value)override;
    FORCEINLINE int32 InterlockedExchange(volatile int32* Target, int32 Value)override;
    FORCEINLINE int32 InterlockedExchangeAdd(volatile int32* Addend, int32 Value)override;
#ifdef ENABLE_64BITS_ATOMICS
    FORCEINLINE int64 InterlockedIncrement(volatile int64* Addend)override;
    FORCEINLINE int64 InterlockedDecrement(volatile int64* Addend)override;
    FORCEINLINE int64 InterlockedAdd(volatile int64* Addend, int64 Value)override;
    FORCEINLINE int64 InterlockedExchange(volatile int64* Target, int64 Value)override;
    FORCEINLINE int64 InterlockedExchangeAdd(volatile int64* Addend, int64 Value)override;
#endif
};
#endif
