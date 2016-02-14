
#ifndef _REFERENCE_COUNTER_
#define _REFERENCE_COUNTER_
#pragma once
#include "typedefs.h"
class fpSharedRefCounter {
private:
	fpSharedRefCounter(fpSharedRefCounter&&);
public:
	fpSharedRefCounter() :refCount(1) {}
	fpSharedRefCounter(fpSharedRefCounter& const inRefCoounter) :refCount(inRefCoounter.refCount) {}
	int32 IncrementCounter()  { return this->refCount++; }
	int32 DecrementCounter() { return this->refCount--; }
	const int32 RefCount()const { return this->refCount; }
private:
	int32 refCount;
};
#endif