#include "fpWindowsAtomics.h"
#include <Windows.h>
fpPlatformAtomicsImpl* fpAtomics::_atomicsImpl = new fpWindowsAtomics();
FORCEINLINE int32 fpWindowsAtomics::InterlockedIncrementImpl(volatile int32* Addend)
{
	return (int32)::InterlockedIncrement((LPLONG)Addend);
}
FORCEINLINE int32 fpWindowsAtomics::InterlockedDecrementImpl(volatile int32* Addend)
{
    return (int32)::InterlockedDecrement((LPLONG)Addend);
}
FORCEINLINE int32 fpWindowsAtomics::InterlockedAddImpl(volatile int32* Addend, int32 Value)
{
    return (int32)::InterlockedExchangeAdd((LPLONG)Addend, (LONG)Value);
}
FORCEINLINE int32 fpWindowsAtomics::InterlockedExchangeImpl(volatile int32* Target, int32 Value)
{
    return (int32)::InterlockedExchange((LPLONG)Target, Value);
}
FORCEINLINE int32 fpWindowsAtomics::InterlockedExchangeAddImpl(volatile int32* Addend, int32 Value)
{
    return (int32)::InterlockedExchangeAdd((LPLONG)Addend, Value);
}
#ifdef ENABLE_64BITS_ATOMICS
FORCEINLINE int64 fpWindowsAtomics::InterlockedIncrementImpl(volatile int64* Addend)
{
	return (int64)::InterlockedIncrement64((LONGLONG*)Addend);
}
FORCEINLINE int64 fpWindowsAtomics::InterlockedDecrementImpl(volatile int64* Addend)
{
	return (int64)::InterlockedDecrement64((LONGLONG*)Addend);
}
FORCEINLINE int64 fpWindowsAtomics::InterlockedAddImpl(volatile int64* Addend, int64 Value)
{
    return (int64)::InterlockedExchangeAdd64((LONG64*)Addend, (LONG64)Value);
}
FORCEINLINE int64 fpWindowsAtomics::InterlockedExchangeImpl(volatile int64* Target, int64 Value)
{
	return (int64)::InterlockedExchange64((LONGLONG*)Target, Value);
}
FORCEINLINE int64 fpWindowsAtomics::InterlockedExchangeAddImpl(volatile int64* Addend, int64 Value)
{
	return (int64)::InterlockedExchange64((LONGLONG*)Addend, Value);
}

#endif
fpWindowsAtomics::~fpWindowsAtomics()
{
}
