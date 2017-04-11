#ifndef _HEAP_TESTER_
#define _HEAP_TESTER_
#pragma once
#include "../../FlyPartEngine/FlyPart.h"
#include <random>
#include <chrono>
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
	static AllocateInfo* _allocatedDefault;
	static AllocateInfo* _allocatedCustom;
public:
	static void InitTester(fpHeapInterface* inHeap,uint32 circles_count,uint32 validateStep, uint32 lowSize, uint32 highSize) 
	{
		_heap = inHeap;
		_validateStep = validateStep;
		_circlesCount = circles_count;
		_lowSize = lowSize;
		_highSize = highSize;

		
	}
	static void HeapStatisticsPrintAndKillHeap()
	{
		std::cout << "BEFORE destroy heap" << std::endl;
		std::cout << "Memory used: " << fpPlatformMemory::Stats.OsMemory / 1024 / 1024 << "MB" << std::endl;
		std::cout << "OS alloc counter: " << fpPlatformMemory::Stats.AllocCallCounter << std::endl;
		std::cout << "OS free counter: " << fpPlatformMemory::Stats.FreeCallCounter << std::endl;
		_heap->HeapDestroy();
		std::cout << "AFTER destroy heap" << std::endl;
		std::cout << "Memory used: " << fpPlatformMemory::Stats.OsMemory / 1024 / 1024 << "MB" << std::endl;
		std::cout << "OS alloc counter: " << fpPlatformMemory::Stats.AllocCallCounter << std::endl;
		std::cout << "OS free counter: " << fpPlatformMemory::Stats.FreeCallCounter << std::endl;
	}
	static void DefaultHeapTest()
	{

		_allocatedDefault = new AllocateInfo[_circlesCount];
		uint32 index;
		// ALLOCATE LOOP
		for (index = 0; index <= _circlesCount; index++)
		{
			uint32 size = HeapTester::NextSize();
			void* ptr = malloc(size);
			_allocatedDefault[index] = { ptr,size };
		}

		//REALLOC LOOP
		for (index = 0; index <= _circlesCount; index++)
		{
			uint32 size = HeapTester::NextSize();
			void* ptr = realloc(_allocatedDefault[index].Ptr, size);
			_allocatedDefault[index].Ptr = ptr;
			_allocatedDefault[index].Size = size;
		}

		//FREE LOOP

        for (index = 0; index <= _circlesCount; index++)
		{
			free(_allocatedDefault[index].Ptr);
		}

	}
	static void CustomHeapTest()
	{
		_allocatedCustom = new AllocateInfo[_circlesCount];
		uint32 index;
		fpAllocatorInterface* allocator = _heap->MakeAllocator();
		// ALLOCATE LOOP
		for (index = 0; index <= _circlesCount; index++)
		{
			uint32 size = HeapTester::NextSize();
			void* ptr = allocator->Allocate(size);
			_allocatedCustom[index] = { ptr,size };
			if (_validateStep!= 0 && index%_validateStep == 0)
			{
				bool is_valid = _heap->ValidateHeap();
				if (!is_valid)
				{
					std::cout << "Heap is corrupted, on " << index << " iteration" << "(ALLOCATE LOOP)" << std::endl;
				}
			}
		}
		//REALLOC LOOP

        for (index = 0; index <= _circlesCount; index++)
		{
			uint32 size = HeapTester::NextSize();
			void* ptr = allocator->Realloc(_allocatedCustom[index].Ptr, size);
			_allocatedCustom[index] = { ptr,size };
			if (_validateStep != 0 && index%_validateStep == 0)
			{
				bool is_valid = _heap->ValidateHeap();
				if (!is_valid)
				{
					std::cout << "Heap is corrupted, on " << index << " iteration" << "(REALLOC LOOP)" << std::endl;
				}
			}
		}

		//FREE LOOP
		for (index = 0; index <= _circlesCount; index++)
		{
			allocator->Free(_allocatedCustom[index].Ptr, _allocatedCustom[index].Size);
			if (_validateStep != 0 && index%_validateStep == 0)
			{
				bool is_valid = _heap->ValidateHeap();
				if (!is_valid)
				{
					std::cout << "Heap is corrupted, on " << index << " iteration" << "(FREE LOOP)" << std::endl;
				}
			}
		}

	}
	static void RunTests()
	{
		std::cout << "-------------------HEAP TEST START---------------------" << std::endl;
        std::chrono::time_point<std::chrono::system_clock> custom_start, custom_end,default_start,default_end;
        int custom_elapsed, default_elapsed;


        default_start = std::chrono::system_clock::now();
        DefaultHeapTest();
        default_end = std::chrono::system_clock::now();
        default_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(default_end - default_start).count();
        std::cout << "default allocator time: " << default_elapsed << std::endl;


        _heap->HeapInit();
        bool is_valid = _heap->ValidateHeap();
        if (!is_valid)
        {
            std::cout << "Heap is corrupted" << std::endl;
        }
		custom_start = std::chrono::system_clock::now();
		CustomHeapTest();
		custom_end = std::chrono::system_clock::now();
		custom_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(custom_end - custom_start).count();
		std::cout << "Custom heap test time(ms): " << custom_elapsed << std::endl;
		HeapStatisticsPrintAndKillHeap();

        std::cout << "Difference default elapsed/custom elapsed(ms): "<< (float)((float)default_elapsed/ (float)custom_elapsed) << std::endl;

		std::cout << "-------------------HEAP TEST END---------------------" << std::endl;
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

