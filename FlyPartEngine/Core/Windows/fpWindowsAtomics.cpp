#include "fpWindowsAtomics.h"
#include <Windows.h>
fpPlatformAtomicsImpl* fpAtomics::_atomicsImpl = new fpWindowsAtomics();
FORCEINLINE int32 fpWindowsAtomics::InterlockedIncrement(volatile int32* Addend)
{
	return (int32) ::_InterlockedIncrement((LPLONG)Addend);
}
FORCEINLINE int32 fpWindowsAtomics::InterlockedDecrement(volatile int32* Addend)
{
    return (int32) ::_InterlockedDecrement((LPLONG)Addend);
}
FORCEINLINE int32 fpWindowsAtomics::InterlockedAdd(volatile int32* Addend, int32 Value)
{
    return (int32)::InterlockedExchangeAdd((LPLONG)Addend, (LONG)Value);
}
FORCEINLINE int32 fpWindowsAtomics::InterlockedExchange(volatile int32* Target, int32 Value)
{
    return (int32)::_InterlockedExchange((LPLONG)Target, Value);
}
FORCEINLINE int32 fpWindowsAtomics::InterlockedExchangeAdd(volatile int32* Addend, int32 Value)
{
    return (int32)::_InterlockedExchangeAdd((LPLONG)Addend, Value);
}
#ifdef ENABLE_64BITS_ATOMICS
FORCEINLINE int64 fpWindowsAtomics::InterlockedIncrement(volatile int64* Addend)
{
	return (int64) ::_InterlockedIncrement64((LONGLONG*)Addend);
}
FORCEINLINE int64 fpWindowsAtomics::InterlockedDecrement(volatile int64* Addend)
{
	return (int64) ::_InterlockedDecrement64((LONGLONG*)Addend);
}
FORCEINLINE int64 fpWindowsAtomics::InterlockedAdd(volatile int64* Addend, int64 Value)
{
    return (int64) ::InterlockedExchangeAdd64((LONG64*)Addend, (LONG64)Value);
}
FORCEINLINE int64 fpWindowsAtomics::InterlockedExchange(volatile int64* Target, int64 Value)
{
	return (int64)::_InterlockedExchange64((LONGLONG*)Target, Value);
}
FORCEINLINE int64 fpWindowsAtomics::InterlockedExchangeAdd(volatile int64* Addend, int64 Value)
{
	return (int64)::_InterlockedExchange64((LONGLONG*)Addend, Value);
}
#endif
