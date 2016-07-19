#ifndef _FP_WINDOWS_INCREMENT_INCLUDE_
#define _FP_WINDOWS_INCREMENT_INCLUDE_
#include "../GenericPlatform/fpPlatformAtomics.h"

class fpLinuxAtomics:public fpPlatformAtomics {
public:
	FORCEINLINE static int32 InterlockedIncrement(volatile int32* Addend)
	{
		return __sync_fetch_and_add(Addend,1) + 1;
	}
	FORCEINLINE static int32 InterlockedDecrement(volatile int32* Addend)
	{
		return __sync_fetch_and_sub(Addend,1) - 1;
	}
	FORCEINLINE static int32 InterlockedAdd(volatile int32* Addend, int32 Value)
	{
		return __sync_fetch_and_add(Addend,Value);
	}
	FORCEINLINE static int32 InterlockedExchange(volatile int32* Target, int32 Value)
	{
		return __sync_lock_test_and_set(Target,Value);
	}
#ifdef ENABLE_64BITS_ATOMICS
	FORCEINLINE static int64 InterlockedIncrement(volatile int64* Addend)
	{
		return __sync_fetch_and_add(Addend,1) + 1;
	}
	FORCEINLINE static int64 InterlockedDecrement(volatile int64* Addend)
	{
		return __sync_fetch_and_sub(Addend,1) - 1;
	}

	FORCEINLINE static int64 InterlockedAdd(volatile int64* Addend, int64 Value)
	{
		return __sync_fetch_and_add(Addend, Value);
	}
	FORCEINLINE static int64 InterlockedExchange(volatile int64* Target, int64 Value)
	{
		return __sync_lock_test_and_set(Target,Value);
	}
#endif
};
typedef fpLinuxAtomics fpAtomics;
#endif
