// test.cpp : Defines the entry point for the console application.
//

#include "../FlyPartEngine/FlyPart.h"
#include "../FlyPartEngine/fpCommon/SmartPtrTest.h"
#ifdef PLATFORM_LINUX
#endif
#ifdef PLATFORM_WINDOWS
	#include <tchar.h>
//	#include "../FlyPartEngine/fpSystem/impl/windows/D3D12/fpD3D12Window.h"
#endif



#include <iostream>
#include <memory>

//using namespace fpTemplate;
struct Test12Bit {
	uint32 x, y, z;
	static uint32 index;
	Test12Bit():x(index++),y(index++),z(index++)
	{}
	void SelfPrint() {
		std::cout << "X: " << this->x << " Y: " << this->y << " Z: " << this->z << std::endl;
	}
};
uint32 Test12Bit::index = 0;
int main(int argc, char **argv)
{
    SmartPtrTest::SmartPtrTestRun();
    fpMemory::UpdateMemoryStats();
    fpCommonHeap* Heap = new fpCommonHeap;
    Heap->HeapInit();
    //system("PAUSE");
    bool is_valid = Heap->ValidateHeap();
    if (is_valid)
    {
        std::cout<<"Heap is OK"<<std::endl;
    }else{
        std::cout<<"Heap is corrupted"<<std::endl;
    }
	fpAllocatorInterface* Allocator = Heap->MakeDefaultAllocator();
	/*
	*	ВОт тут после выделения происходит непонятки, дальше в цикле адреса в пуле бьются
		из чег оследует что выделенияе или выдача блока кривая
		есть мнение что алокация верная, но нужно также менять Pool->FreeMem уцказатель также как и 
		ListPoolFreeMemory,ListPoolFreeMemory адреса верные, Pool->FreeMem адреса битые
		Нужно также сместить указатель на локальные блоки в пуле(Pool->FreeMem) так же как и ListPoolFreeMemory
	*/
	Test12Bit* test = (Test12Bit*)Allocator->Allocate(sizeof(Test12Bit) * 40);
	for (UINTPTR i = 0;i < 40;i++)
	{
		new((void*)((Test12Bit*)test + i))Test12Bit();
		((Test12Bit*)test + i)->SelfPrint();
	}

	//Allocator->Free(test, sizeof(Test12Bit) * 40);
	//is_valid = Heap->ValidateHeap();
	//if (is_valid)
	//{
	//	std::cout << "Heap is OK" << std::endl;
	//}
	//else {
	//	std::cout << "Heap is corrupted" << std::endl;
	//}


	
	test = (Test12Bit*)Allocator->Realloc(test,sizeof(Test12Bit) * 50);
	for (uint32 i = 40;i < 50;i++)
	{
		((Test12Bit*)test + i)->SelfPrint();
	}
	for (uint32 i = 0;i < 50;i++)
	{
		((Test12Bit*)test + i)->SelfPrint();
	}
	
	is_valid = Heap->ValidateHeap();
	if (is_valid)
	{
		std::cout << "Heap is OK" << std::endl;
	}
	else {
		std::cout << "Heap is corrupted" << std::endl;
	}
    return 0;
}











