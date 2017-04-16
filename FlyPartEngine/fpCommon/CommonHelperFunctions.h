#ifndef _COMMON_HELPER_FUNCTIONS_
#define _COMMON_HELPER_FUNCTIONS_
#pragma once

#include "../Core/GenericPlatform/typedefs.h"
namespace fpTemplate {
	template<typename T> struct fpRemoveReference { typedef T Type; };
	template<typename T> struct fpRemoveReference<T&> { typedef T Type; };
	template<typename T> struct fpRemoveReference<T&&> { typedef T Type; };

	template<typename T>
	FORCEINLINE T&& fpForward(typename fpRemoveReference<T>::Type& Obj)
	{
		return static_cast<T&&>(Obj);
	}
	template<typename T>
	FORCEINLINE T&& fpForward(typename fpRemoveReference<T>::Type&& Obj)
	{
		return static_cast<T&&>(Obj);
	}
	template<typename T>
	FORCEINLINE typename fpRemoveReference<T>::Type&& fpMove(T&& Obj)
	{
        return static_cast<typename fpRemoveReference<T>::Type&& >(Obj);
	}

	template<bool Predicate,typename Result = void> struct fpEnableIf;	
	template<typename Result> struct fpEnableIf<true,Result> { typedef Result Type; };
	template<typename Result> struct fpEnableIf<false,Result>{ };


};
#endif // !_COMMON_HELPER_FUNCTIONS_

