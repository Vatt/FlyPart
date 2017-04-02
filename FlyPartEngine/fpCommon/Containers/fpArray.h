#ifndef _FPARRAY_H_
#define _FPARRAY_H_
#include "../../Core/GenericPlatform/typedefs.h"
#include "../../Core/CoreAbstractLayer/Memory/fpHeapInterface.h"
template <typename Type,fpHeapInterface* Heap>
class fpArray
{
	void* data;
public:
	fpArray(uint64 size)
	{
		Heap->HeapAlloc(size * sizeof(Type));
	}
	Type& operator[](uint64 index)
	{
		return (data + index * sizeof(Type));
	}
};
#endif //FLYPARTENGINE_FPARRAY_H
