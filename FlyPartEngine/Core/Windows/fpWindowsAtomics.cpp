#include "fpWindowsAtomics.h"
#include <Windows.h>
fpPlatformAtomicsImpl* fpAtomics::_atomicsImpl = new fpWindowsAtomics();
FORCEINLINE int32 fpWindowsAtomics::InterlockedIncrement_i32(volatile int32* Addend)
{
	return (int32) ::_InterlockedIncrement((LPLONG)Addend);
}

FORCEINLINE int64 fpWindowsAtomics::InterlockedIncrement_i64(volatile int64* Addend)
{
	return (int64) ::_InterlockedIncrement64((LONGLONG*)Addend);
}



FORCEINLINE int32 fpWindowsAtomics::InterlockedDecrement_i32(volatile int32* Addend)
{
	return (int32) ::_InterlockedDecrement((LPLONG)Addend);
}

FORCEINLINE int64 fpWindowsAtomics::InterlockedDecrement_i64(volatile int64* Addend)
{
	return (int64) ::_InterlockedDecrement64((LONGLONG*)Addend);
}



FORCEINLINE int32 fpWindowsAtomics::InterlockedAdd_i32(volatile int32* Addend, int32 Value)
{
	//return (int32) ::_InlineInterlockedAdd((LPLONG)Addend, (LONG)Value);
	return (int32)::_InterlockedAdd((LPLONG)Addend, (LONG)Value);
}
FORCEINLINE int64 fpWindowsAtomics::InterlockedAdd_i64(volatile int64* Addend, int64 Value)
{
	//return (int64) ::_InlineInterlockedAdd64((LONG64*)Addend, (LONG64)Value);
	return (int64) ::_InterlockedAdd64((LONG64*)Addend, (LONG64)Value);
}


FORCEINLINE int32 fpWindowsAtomics::InterlockedExchange_i32(volatile int32* Target, int32 Value)
{
	return (int32)::_InterlockedExchange((LPLONG)Target, Value);
}
FORCEINLINE int64 fpWindowsAtomics::InterlockedExchange_i64(volatile int64* Target, int64 Value)
{
	return (int64)::_InterlockedExchange64((LONGLONG*)Target, Value);
}

FORCEINLINE int32 fpWindowsAtomics::InterlockedExchangeAdd_i32(volatile int32* Addend, int32 Value)
{
	return (int32)::_InterlockedExchangeAdd((LPLONG)Addend, Value);
}
FORCEINLINE int64 fpWindowsAtomics::InterlockedExchangeAdd_i64(volatile int64* Addend, int64 Value)
{
	return (int64)::_InterlockedExchange64((LONGLONG*)Addend, Value);
}