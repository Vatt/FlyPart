#ifndef _FP_WINDOWS_INCREMENT_INCLUDE_
#define _FP_WINDOWS_INCREMENT_INCLUDE_
#include "../GenericPlatform/fpAtomics.h"

class fpWindowsAtomics:public fpPlatformAtomicsImpl {
public:
    FORCEINLINE int32 InterlockedIncrementImpl(volatile int32* Addend)override;
    FORCEINLINE int32 InterlockedDecrementImpl(volatile int32* Addend)override;
    FORCEINLINE int32 InterlockedAddImpl(volatile int32* Addend, int32 Value)override;
    FORCEINLINE int32 InterlockedExchangeImpl(volatile int32* Target, int32 Value)override;
#ifdef ENABLE_64BITS_ATOMICS
    FORCEINLINE int64 InterlockedIncrementImpl(volatile int64* Addend)override;
    FORCEINLINE int64 InterlockedDecrementImpl(volatile int64* Addend)override;
    FORCEINLINE int64 InterlockedAddImpl(volatile int64* Addend, int64 Value)override;
    FORCEINLINE int64 InterlockedExchangeImpl(volatile int64* Target, int64 Value)override;
#endif

	virtual ~fpWindowsAtomics();
};
#endif
