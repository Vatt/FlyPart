#ifndef _COMMON_HELPER_FUNCTIONS_
#define _COMMON_HELPER_FUNCTIONS_
#pragma once
#include "defines.h"
template<typename T> struct RemoveReference		{ typedef T Type; };
template<typename T> struct RemoveReference<T&> { typedef T Type; };
template<typename T> struct RemoveReference<T&&>{ typedef T Type; };

template<typename T>
FORCEINLINE T&& Forward(typename RemoveReference<T>::Type& Obj)
{
	return (T&&)Obj;
}
template<typename T>
FORCEINLINE T&& Forward(typename RemoveReference<T>::Type&& Obj)
{
	return (T&&)Obj;
}
#endif // !_COMMON_HELPER_FUNCTIONS_


