#include "HeapTester.h"

fpHeapInterface* HeapTester::_heap = nullptr;
uint32 HeapTester::_validateStep = 0;;
uint32 HeapTester::_circlesCount = 0;
HeapTester::AllocateInfo* HeapTester::_allocatedCustom = nullptr;
HeapTester::AllocateInfo* HeapTester::_allocatedDefault = nullptr;
uint32 HeapTester::_lowSize = 0;
uint32 HeapTester::_highSize = 0;
HeapTester::~HeapTester()
{
}
