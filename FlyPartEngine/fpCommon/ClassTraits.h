#ifndef _CLASS_TRAITS_
#define _CLASS_TRAITS_
#pragma once
#include "TypeTraits.h"
template<typename T> struct fpHasTrivialDestructor  { enum { Value = __has_trivial_destructor(T)  }; };
template<typename T> struct fpHasTrivialConstructor { enum { Value = __has_trivial_constructor(T) }; };
#endif