#ifndef _COMMON_HELPER_FUNCTIONS_
#define _COMMON_HELPER_FUNCTIONS_
#pragma once
#include "defines.h"
#include "typedefs.h"
namespace fpTemplate {
	template<typename T> struct RemoveReference { typedef T Type; };
	template<typename T> struct RemoveReference<T&> { typedef T Type; };
	template<typename T> struct RemoveReference<T&&> { typedef T Type; };

	template<typename T>
	FORCEINLINE T&& Forward(typename RemoveReference<T>::Type& Obj)
	{
		return static_cast<T&&>(Obj);
	}
	template<typename T>
	FORCEINLINE T&& Forward(typename RemoveReference<T>::Type&& Obj)
	{
		return static_cast<T&&>(Obj);
	}
	template<typename T>
	FORCEINLINE typename RemoveReference<T>::Type&& Move(T&& Obj)
	{
        return static_cast<typename RemoveReference<T>::Type&& >(Obj);
	}


};
#endif // !_COMMON_HELPER_FUNCTIONS_

