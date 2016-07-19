#ifndef _FP_INCREMENT_INCLUDE_
#define _FP_INCREMENT_INCLUDE_

#include <assert.h>
#include "typedefs.h"
#include "defines.h"
#ifdef PLATFORM_64
    #define ENABLE_64BITS_ATOMICS
#endif
class fpPlatformAtomics {
public:
    static FORCEINLINE int32 InterlockedIncrement(volatile int32* Addend)
	{
        assert(0);
        return 0;
	}
    static FORCEINLINE int32 InterlockedDecrement(volatile int32* Addend)
    {
        assert(0);
        return 0;
    }
    static FORCEINLINE int32 InterlockedAdd(volatile int32* Addend, int32 Value)
    {
        assert(0);
        return 0;
    }
    static FORCEINLINE int32 InterlockedExchange(volatile int32* Target, int32 Value)
    {
        assert(0);
        return 0;
    }

#ifdef ENABLE_64BITS_ATOMICS
    static FORCEINLINE int64 InterlockedIncrement(volatile int64* Addend)
	{
        assert(0);
        return 0;
	}
    static FORCEINLINE int64 InterlockedDecrement(volatile int64* Addend)
	{
        assert(0);
        return 0;
	}
    static FORCEINLINE int64 InterlockedAdd(volatile int64* Addend, int64 Value)
	{
        assert(0);
        return 0;
	}
    static FORCEINLINE int64 InterlockedExchange(volatile int64* Target, int64 Value)
	{
        assert(0);
        return 0;
	}
#endif
};
#endif
