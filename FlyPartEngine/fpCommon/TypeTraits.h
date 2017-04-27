#ifndef _TYPE_TRAITS_INCLUDE_
#define _TYPE_TRAITS_INCLUDE_
#include "../Core/GenericPlatform/typedefs.h"
template <typename T> struct fpIsFloatType   {enum{Value = false};};
template <> struct fpIsFloatType<float>      {enum{Value = true};};
template <> struct fpIsFloatType<double>     {enum{Value = true};};
template <> struct fpIsFloatType<long double>{enum{Value = true};};

template <typename T> struct fpIsIntType{enum{Value = false};};
template <> struct fpIsIntType<int8>    {enum{Value = true};};
template <> struct fpIsIntType<int16>   {enum{Value = true};};
template <> struct fpIsIntType<int32>   {enum{Value = true};};
template <> struct fpIsIntType<int64>   {enum{Value = true};};
template <> struct fpIsIntType<uint16>  {enum{Value = true};};
template <> struct fpIsIntType<uint32>  {enum{Value = true};};
template <> struct fpIsIntType<uint64>  {enum{Value = true};};
template <> struct fpIsIntType<ASCICHAR>{enum{Value = true};};
template <> struct fpIsIntType<WIDECHAR>{enum{Value = true};};

template<typename T> struct fpIsSignedType{enum{Value = false};};
template<> struct fpIsSignedType<int8>    {enum{Value = true};};
template<> struct fpIsSignedType<int16>   {enum{Value = true};};
template<> struct fpIsSignedType<int32>   {enum{Value = true};};
template<> struct fpIsSignedType<int64>   {enum{Value = true};};

template<typename T> struct fpIsUnsignedType{enum{Value = false};};
template<> struct fpIsUnsignedType<uint16>   {enum{Value = true};};
template<> struct fpIsUnsignedType<uint32>   {enum{Value = true};};
template<> struct fpIsUnsignedType<uint64>   {enum{Value = true};};

template<typename T> struct fpIsArithmeticType{
    enum{Value = fpIsIntType<T>::Value||fpIsFloatType<T>::Value};
};


template <typename T> struct fpIsPointerType				   {enum{Value = false};};
template <typename T> struct fpIsPointerType<T*>               {enum{Value = true};};
template <typename T> struct fpIsPointerType<const T*>         {enum{Value = true};};
template <typename T> struct fpIsPointerType<const T* const>   {enum{Value = true};};
template <typename T> struct fpIsPointerType<T* volatile>      {enum{Value = true};};
template <typename T> struct fpIsPointerType<T* const volatile>{enum{Value = true};};

template <typename T> struct fpIsReference			{enum{Value = false};};
template <typename T> struct fpIsReference<T&>      {enum{Value = true};};
template <typename T> struct fpIsReference<T&&>     {enum{Value = true};};

template <typename T> struct fpIsLValueReference		  {enum{Value = false};};
template <typename T> struct fpIsLValueReference<T&>      {enum{Value = true};};

template <typename T> struct fpIsRValueReference		  {enum{Value = false};};
template <typename T> struct fpIsRValueReference<T&&>     {enum{Value = true};};

template<typename T> struct fpIsVoidType               {enum{Value = false};};
template<> struct fpIsVoidType<void>                   {enum{Value = true};};
template<> struct fpIsVoidType<const void>             {enum{Value = true};};
template<> struct fpIsVoidType<void volatile>          {enum{Value = true};};
template<> struct fpIsVoidType<const void volatile>    {enum{Value = true};};


template<typename T> struct fpIsEnum{ enum{Value = __is_enum(T)}; };

template<typename T> struct fpIsBitwiseComparable{enum{Value = fpIsArithmeticType<T>||fpIsEnum<T>||fpIsPointerType<T>}; };

template<typename T> struct fpIsFunction { enum { Value = false }; };
template<typename RetType,typename ... Args>
struct fpIsFunction<RetType(Args...)>
{
    enum { Value = true };
};

template<typename T,typename S> struct fpIsSame     {enum{Value = false};};
template<typename T>            struct fpIsSame<T,T>{enum{Value = true};};

template<typename T> struct fpRemoveCV					{ typedef T Type; };
template<typename T> struct fpRemoveCV<const T>			{ typedef T Type; };
template<typename T> struct fpRemoveCV<volatile T>      { typedef T Type; };
template<typename T> struct fpRemoveCV<const volatile T>{ typedef T Type; };

template<typename T> struct fpIsPODType
{
	enum { Value = fpIsArithmeticType<T>::Value||__is_pod(T)|| __is_enum(T)|| fpIsPointerType<T>::Value };
};








































#endif // !_TYPE_TRAITS_INCLUDE_

