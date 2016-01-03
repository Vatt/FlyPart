
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
	void IncrementCounter() { this->refCount++; }
	int32 DecrementCounter() { this->refCount--; }
	int32 RefCount() { return this->refCount; }
private:
	int32 refCount;
};
#endif