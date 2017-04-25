#ifndef _CLASS_MEMORY_OPS_
#define _CLASS_MEMORY_OPS_
#pragma once
#include "CommonHelperFunctions.h"
#include "ClassTraits.h"
#include "../Core/GenericPlatform/fpPlatform.h"
using namespace fpTemplate;
template<typename ElemType>
FORCEINLINE typename fpEnableIf<!fpHasTrivialDestructor<ElemType>::Value>::Type  DestroyItems(ElemType* ElementDest, uint32 Count)
{
	while (Count)
	{
		ElementDest->ElemType::~ElemType();
		++ElementDest;
		--Count;
	}
}

template<typename ElemType>
FORCEINLINE typename fpEnableIf<fpHasTrivialDestructor<ElemType>::Value>::Type  DestroyItems(ElemType* ElementDest, uint32 Count)
{
}


template<typename ElemType>
FORCEINLINE typename fpEnableIf<!fpIsPODType<ElemType>::Value>::Type ConstructItems(ElemType* ElementDest, uint32 Count)
{
	while (Count)
	{
		new(ElementDest)ElemType();
		++ElementDest;
		--Count;
	}
}
template<typename ElemType>
FORCEINLINE typename fpEnableIf<fpHasTrivialConstructor<ElemType>::Value>::Type ConstructItems(ElemType* ElementDest, uint32 Count)
{
	fpPlatformMemory::MemSet(ElementDest, 0, sizeof(ElemType)*Count);
}
template<typename ElemType>
FORCEINLINE typename fpEnableIf<!fpIsPODType<ElemType>::Value>::Type ConstructItems(void* Dest, const ElemType* Src, uint32 Count)
{
	while (Count)
	{
		new(Dest)ElemType(*Src);
		++Src;
		++(ElemType*&)Dest;
		--Count;
	}
}
template<typename ElemType>
FORCEINLINE typename fpEnableIf<fpIsPODType<ElemType>::Value>::Type ConstructItems(void* Dest, const ElemType* Src, uint32 Count)
{
	fpPlatformMemory::MemCopy(Dest, Src, Count*sizeof(ElemType));
}
#endif

