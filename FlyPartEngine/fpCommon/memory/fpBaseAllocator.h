#ifndef _FP_BASE_ALLOCATOR_
#define _FP_BASE_ALLOCATOR_
#include<memory>
/*
* not pool allocator
*/

class fpBaseMemoryAllocator
{
private:
	class MemBlock
	{
	private:
		void* _mem;
		size_t _size;
		ptrdiff_t& _firstPtr;
		ptrdiff_t& _lastPtr;
	public:
		MemBlock(size_t size)
		{
			_mem =   malloc(size);
			_firstPtr = &_mem;
			_lastPtr = &_mem + size;
			_size = size;
		}
		void* getMemoryCell(unsigned int index)
		{
			return  (&_mem+(index*_size));
		}

	};
	 MemBlock* lastUsedBlock;
	 MemBlock* root;
private:
	fpBaseMemoryAllocator();
	fpBaseMemoryAllocator(fpBaseMemoryAllocator&);
	fpBaseMemoryAllocator(fpBaseMemoryAllocator&&);
public:
	void AgregateBlocks();
public:
	fpBaseMemoryAllocator(size_t blockSize);
	void* Allocate(size_t size);
	void Free(void* ptr);
};

#endif