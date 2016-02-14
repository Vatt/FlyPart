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
	return (int32) ::_InlineInterlockedAdd((LPLONG)Addend, (LONG)Value);
}
FORCEINLINE int64 fpWindowsAtomics::InterlockedAdd_i64(volatile int64* Addend, int64 Value)
{
	return (int64) ::_InlineInterlockedAdd64((LONG64*)Addend, (LONG64)Value);
}
