#ifndef _FP_BASE_ALLOCATOR_
#define _FP_BASE_ALLOCATOR_
#include<memory>
#include<stddef.h>
/*
* not pool allocator
* fixed size
* linear allocator
*/
template<typename T>
class fpBaseMemoryAllocator
{
private:
	struct MemBlock
	{
		unsigned char* _memory;
		size_t _size;
		size_t _cellSize;
		ptrdiff_t   _firstPtr;
		ptrdiff_t   _lastPtr;
		size_t  _offset;
		bool isEnable;
		MemBlock* _next;
		MemBlock(){};
		MemBlock( size_t size)
		{
			
			_memory = (unsigned char*) malloc(size);
			_cellSize = sizeof(T);
			_firstPtr = (ptrdiff_t)&_memory;
			_lastPtr = (ptrdiff_t)(&_memory + size);
			_size = size;
			_offset = 0;
			_next = nullptr;
                        isEnable = true;
		}
		unsigned char* getNextMemoryCellPtr()
		{
			unsigned char* memCell =   ( _memory + ( _offset *_cellSize));
			_offset++;
			if (_size == _offset*_cellSize)
				isEnable = false;
			return memCell;
		}

 
	};
	 MemBlock* lastUsedBlock;
	 MemBlock* firstEnabledBlock;
	// MemBlock* lastBlock;
	 MemBlock* root;
private:
	fpBaseMemoryAllocator();
	fpBaseMemoryAllocator(fpBaseMemoryAllocator&);
	fpBaseMemoryAllocator(fpBaseMemoryAllocator&&);
public:
	void AgregateBlocks(){
		
	}
public:
 
	fpBaseMemoryAllocator(size_t cells, bool UseReserve = true)
	{
		_cellMemSize = sizeof(T);
		root = new fpBaseMemoryAllocator::MemBlock(_cellMemSize*cells);
		_blockSize = _cellMemSize*cells;
		firstEnabledBlock = &*root;
		lastUsedBlock = &*root;
		useReserve = UseReserve;
		if (useReserve)
		{
			root->_next = new fpBaseMemoryAllocator::MemBlock( _blockSize);
		}
	}

	void* Allocate()
	{
		if (firstEnabledBlock->isEnable)
			return (T*)firstEnabledBlock->getNextMemoryCellPtr();
		else{
			if (firstEnabledBlock->_next != nullptr)
			{
				firstEnabledBlock = firstEnabledBlock->_next;
				firstEnabledBlock->getNextMemoryCellPtr();
			}
			else{
				firstEnabledBlock->_next = new MemBlock(_blockSize);
				firstEnabledBlock = firstEnabledBlock->_next;
				return firstEnabledBlock->getNextMemoryCellPtr();
			}
		}
	}
	void Free(void* ptr)
	{

	}
    void getMem(unsigned int index)
    {

    }

private:
	size_t _cellMemSize;
	size_t _blockSize;
	bool useReserve;
        const int BlocksCountToAgregation = 4;
	const float reserveRatio = 1.5;
};

#endif
