#include "fpLinuxAtomics.h"

fpPlatformAtomicsImpl* fpAtomics::_atomicsImpl = new fpLinuxAtomics();
FORCEINLINE int32 fpLinuxAtomics::InterlockedIncrement_i32(volatile int32* Addend)
{
	return __sync_fetch_and_add(Addend,1);
}

FORCEINLINE int64 fpLinuxAtomics::InterlockedIncrement_i64(volatile int64* Addend)
{
	return __sync_fetch_and_add(Addend,1);
}



FORCEINLINE int32 fpLinuxAtomics::InterlockedDecrement_i32(volatile int32* Addend)
{
	return __sync_fetch_and_sub(Addend,1);
}

FORCEINLINE int64 fpLinuxAtomics::InterlockedDecrement_i64(volatile int64* Addend)
{
	return __sync_fetch_and_sub(Addend,1);
}



FORCEINLINE int32 fpLinuxAtomics::InterlockedAdd_i32(volatile int32* Addend, int32 Value)
{
	return __sync_fetch_and_add(Addend,Value);
}
FORCEINLINE int64 fpLinuxAtomics::InterlockedAdd_i64(volatile int64* Addend, int64 Value)
{
	return __sync_fetch_and_add(Addend,Value);
