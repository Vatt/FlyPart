#include "fpLinuxAtomics.h"

fpPlatformAtomicsImpl* fpAtomics::_atomicsImpl = new fpLinuxAtomics();
FORCEINLINE int32 fpLinuxAtomics::InterlockedIncrementImpl(volatile int32* Addend)
{
	return __sync_fetch_and_add(Addend,1) + 1;
}
FORCEINLINE int32 fpLinuxAtomics::InterlockedDecrementImpl(volatile int32* Addend)
{
	return __sync_fetch_and_sub(Addend,1) - 1;
}
FORCEINLINE int32 fpLinuxAtomics::InterlockedAddImpl(volatile int32* Addend, int32 Value)
{
	return __sync_fetch_and_add(Addend,Value);
}
FORCEINLINE int32 fpLinuxAtomics::InterlockedExchangeImpl(volatile int32* Target, int32 Value)
{
	return __sync_lock_test_and_set(Target,Value);
}
#ifdef ENABLE_64BITS_ATOMICS
FORCEINLINE int64 fpLinuxAtomics::InterlockedIncrementImpl(volatile int64* Addend)
{
	return __sync_fetch_and_add(Addend,1) + 1;
}
FORCEINLINE int64 fpLinuxAtomics::InterlockedDecrementImpl(volatile int64* Addend)
{
	return __sync_fetch_and_sub(Addend,1) - 1;
}

FORCEINLINE int64 fpLinuxAtomics::InterlockedAddImpl(volatile int64* Addend, int64 Value)
{
	return __sync_fetch_and_add(Addend, Value);
}
FORCEINLINE int64 fpLinuxAtomics::InterlockedExchangeImpl(volatile int64* Target, int64 Value)
{
	return __sync_lock_test_and_set(Target,Value);
}
#endif
fpLinuxAtomics::~fpLinuxAtomics() { }