#include "HeapTester.h"

fpHeapInterface* HeapTester::_heap = nullptr;
uint32 HeapTester::_validateStep = 0;;
uint32 HeapTester::_circlesCount = 0;
HeapTester::AllocateInfo* HeapTester::_allocated = nullptr;
uint32 HeapTester::_lowSize = 0;
uint32 HeapTester::_highSize = 0;
HeapTester::~HeapTester()
{
}
