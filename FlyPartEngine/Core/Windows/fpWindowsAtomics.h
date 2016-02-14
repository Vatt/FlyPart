#ifndef _FP_WINDOWS_INCREMENT_INCLUDE_
#define _FP_WINDOWS_INCREMENT_INCLUDE_
#include "../GenericPlatform/fpAtomics.h"
class fpWindowsAtomics:public fpPlatformAtomicsImpl {
public:
	FORCEINLINE int32 InterlockedIncrement_i32(volatile int32* Addend)override;
	FORCEINLINE int64 InterlockedIncrement_i64(volatile int64* Addend)override;

	FORCEINLINE int32 InterlockedDecrement_i32(volatile int32* Addend)override;
	FORCEINLINE int64 InterlockedDecrement_i64(volatile int64* Addend)override;

	FORCEINLINE int32 InterlockedAdd_i32(volatile int32* Addend, int32 Value)override;
	FORCEINLINE int64 InterlockedAdd_i64(volatile int64* Addend, int64 Value)override;
};
#endif