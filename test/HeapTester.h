#ifndef _HEAP_TESTER_
#define _HEAP_TESTER_
#pragma once
#include "../FlyPartEngine/FlyPart.h"
#include <random>
#include <iostream>
class HeapTester
{
	struct AllocateInfo 
	{
		void* Ptr;
		uint64 Size;
	};
	static fpHeapInterface* _heap;
	static uint32 _validateStep;
	static uint32 _circlesCount;
	static uint32 _lowSize;
	static uint32 _highSize;
	static AllocateInfo* _allocated;
public:
	static void InitTester(fpHeapInterface* inHeap,uint32 circles_count,uint32 validateStep, uint32 lowSize, uint32 highSize) 
	{
		_heap = inHeap;
		_allocated = new AllocateInfo[circles_count];
		_validateStep = validateStep;
		_circlesCount = circles_count;
		_lowSize = lowSize;
		_highSize = highSize;
		_heap->HeapInit();
	}
	static void ShutdownTester()
	{
		std::cout << "-----------------------------------------" << std::endl;
		std::cout << "BEFORE destroy heap" << std::endl;
		std::cout << "Memory used: " << fpMemory::Stats.UsedMemory / 1024 / 1024 << "MB" << std::endl;
		std::cout << "OS alloc counter: " << fpMemory::Stats.AllocCallCounter << std::endl;
		std::cout << "OS free counter: " << fpMemory::Stats.FreeCallCounter << std::endl;
		_heap->HeapDestroy();
		std::cout << "AFTER destroy heap" << std::endl;
		std::cout << "Memory used: " << fpMemory::Stats.UsedMemory / 1024 / 1024 << "MB" << std::endl;
		std::cout << "OS alloc counter: " << fpMemory::Stats.AllocCallCounter << std::endl;
		std::cout << "OS free counter: " << fpMemory::Stats.FreeCallCounter << std::endl;
		std::cout << "-----------------------------------------" << std::endl;

	}
	static void RunTests()
	{
		uint32 index;
		fpAllocatorInterface* allocator = _heap->MakeAllocator();
// ALLOCATE LOOP
		for (index = 0; index <= _circlesCount; index++)
		{
			uint32 size = HeapTester::NextSize();
			void* ptr = allocator->Allocate(size);
			_allocated[index] = { ptr,size };
			if (index%_validateStep == 0)
			{
				bool is_valid = _heap->ValidateHeap();
				if (is_valid)
				{
					std::cout << "Heap is OK, on "<< index <<" iteration" <<"(ALLOCATE LOOP)" <<std::endl;
				}
				else {
					std::cout << "Heap is corrupted, on " << index << " iteration" << "(ALLOCATE LOOP)" << std::endl;
				}
			}
		}
//REALLOC LOOP
		//for (index = 0; index <= _circlesCount; index++)
		//{
		//	uint32 size = HeapTester::NextSize();
		//	void* ptr = allocator->Realloc(_allocated[index].Ptr, size);
		//	_allocated[index] = { ptr,size };
		//	if (index%_validateStep == 0)
		//	{
		//		bool is_valid = _heap->ValidateHeap();
		//		if (is_valid)
		//		{
		//			std::cout << "Heap is OK, on " << index << " iteration"<<"(REALOC LOOP)" << std::endl;
		//		}
		//		else {
		//			std::cout << "Heap is corrupted, on " << index << " iteration" << "(REALOC LOOP)" << std::endl;
		//		}
		//	}
		//}
//FREE LOOP
		for (index= 0; index <= _circlesCount; index++)
		{
			allocator->Free(_allocated[index].Ptr, _allocated[index].Size);
			if (index%_validateStep == 0)
			{
				bool is_valid = _heap->ValidateHeap();
				if (is_valid)
				{
					std::cout << "Heap is OK, on " << index << " iteration" << "(FREE LOOP)" << std::endl;
				}
				else {
					std::cout << "Heap is corrupted, on " << index << " iteration" << "(FREE LOOP)" << std::endl;
				}
			}
		}	   
	}
	~HeapTester();
private:
	FORCEINLINE static uint32 NextSize() 
	{
		static std::random_device device;
		static std::default_random_engine engine(device());
		static std::uniform_int_distribution<uint32> uniform_dist(_lowSize,_highSize);
		return uniform_dist(engine);
	}
};

#endif

