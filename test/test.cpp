// test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../FlyPartEngine/fpCommon/memory/fpBaseAllocator.h"
 

#pragma comment(lib,"fpSystem.lib")
struct test
{
	int x, y, z;
};
int _tmain(int argc, _TCHAR* argv[])
{
	fpBaseMemoryAllocator<int>* allocator = new  fpBaseMemoryAllocator<int>(  sizeof(int)* 10);
	/*test* st = (test*)allocator->Allocate();
	
	st->x = 10;
	st->y = 20;
	st->z = 100;*/
	int* arr = (int*)allocator->Allocate();
	*arr = 1;
	system("PAUSE");
	return 0;
}

