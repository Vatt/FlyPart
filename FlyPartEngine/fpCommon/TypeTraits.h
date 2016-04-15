#ifndef _TYPE_TRAITS_INCLUDE_
#define _TYPE_TRAITS_INCLUDE_
#include "typedefs.h"
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


template <typename T> struct fpIsPointerType         {enum{Value = false};};
template <> struct fpIsPointerType<T*>               {enum{Value = true};};
template <> struct fpIsPointerType<const T>          {enum{Value = true};};
template <> struct fpIsPointerType<const T* const>   {enum{Value = true};};
template <> struct fpIsPointerType<T* volatile>      {enum{Value = true};};
template <> struct fpIsPointerType<T* const volatile>{enum{Value = true};};

template <typename T> struct fpIsReference{enum{Value = false};};
template <> struct fpIsReference<T&>      {enum{Value = true};};
template <> struct fpIsReference<T&&>     {enum{Value = true};};

template <typename T> struct fpIsLValueReference{enum{Value = false};};
template <> struct fpIsLValueReference<T&>      {enum{Value = true};};

template <typename T> struct fpIsRValueReference{enum{Value = false};};
template <> struct fpIsRValueReference<T&&>     {enum{Value = true};};

template<typename T> struct fpIsVoidType               {enum{Value = false};};
template<> struct fpIsVoidType<void>                   {enum{Value = true};};
template<> struct fpIsVoidType<const void>             {enum{Value = true};};
template<> struct fpIsVoidType<void volatile>          {enum{Value = true};};
template<> struct fpIsVoidType<const void volatile>    {enum{Value = true};};

template<typename T> struct fpIsFunction{enum{Value = false};};
template<typename RetType,typename ... Args>
struct fpIsFunction<RetType(Args...)>
{
    enum{Value = true};
};

template<typename T,typename S> struct fpIsSame     {enum{Value = false};};
template<typename T>            struct fpIsSame<T,T>{enum{Value = true};};










































#endif // !_TYPE_TRAITS_INCLUDE_

