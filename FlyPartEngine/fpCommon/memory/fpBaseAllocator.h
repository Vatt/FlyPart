#ifndef _FP_BASE_ALLOCATOR_
#define _FP_BASE_ALLOCATOR_
#include<memory>
#include<stddef.h>
/*
* not pool allocator
* fixed size
*/
template<typename T>
class fpBaseMemoryAllocator
{
private:
	struct MemBlock
	{
		void* _memory;
		size_t _size;
		size_t _cellSize;
		ptrdiff_t*   _firstPtr;
		ptrdiff_t*   _lastPtr;
		ptrdiff_t*  _currentPtr;
		bool isEnable;
		MemBlock* next;
		MemBlock(){};
		MemBlock( size_t size)
		{
			
			_memory =  malloc(size);
			_cellSize = sizeof(T);
			_firstPtr = (ptrdiff_t*)&_memory;
			_lastPtr = (ptrdiff_t*)(&_memory + size);
			_size = size;
			_currentPtr = _firstPtr;
		}
		ptrdiff_t* getMemoryCellPtr(ptrdiff_t*  offset)
		{
			return  (& _memory + ( offset *_cellSize));
		}
 
	};
	 MemBlock* lastUsedBlock;
	 MemBlock* firstEnabledBlock;
	// MemBlock* lastBlock;
	 MemBlock root;
private:
	fpBaseMemoryAllocator();
	fpBaseMemoryAllocator(fpBaseMemoryAllocator&);
	fpBaseMemoryAllocator(fpBaseMemoryAllocator&&);
public:
	void AgregateBlocks();
public:
 
	fpBaseMemoryAllocator(size_t blockSize, bool UseReserve = false)
	{
		_cellMemSize = sizeof(T);
		root = fpBaseMemoryAllocator::MemBlock(blockSize);
		_blockSize = blockSize;
		firstEnabledBlock = &root;
		lastUsedBlock = &root;
		useReserve = UseReserve;
		if (useReserve)
		{
			root.next = new fpBaseMemoryAllocator::MemBlock( _blockSize);
		}
	}

	void* Allocate()
	{
		void* retPtr = firstEnabledBlock->getMemoryCellPtr(firstEnabledBlock->_currentPtr + _cellMemSize);
		firstEnabledBlock->_currentPtr += _cellMemSize;
		return  retPtr;
	}
	void Free(void* ptr);
private:
	size_t _cellMemSize;
	size_t _blockSize;
	bool useReserve;
	const int BlocksCountToAgregation = 6;
};

#endif
