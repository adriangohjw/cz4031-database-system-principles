//
// Created by Abhishek Bhagwat on 13/10/20.
//

#include "memory-pool.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/**
 * MemoryPool Constructor
 * @param memoryPoolSize Overall size of the MemoryPool
 * @param blkSize Size of each block to be allocated in the MemoryPool
 */

//allocated = numAllocBlks, sizeUsed = memoryPoolUsed, available = numAvailBlks
MemoryPool::MemoryPool(unsigned int memoryPoolSize, unsigned int blkSize) {
    this->memoryPoolSize = memoryPoolSize;
    this->blkSize = blkSize;

    // Assign a pointer to the start of the MemoryPool
    // The blkPtr and nextFree pointers are also assigned to the start of the MemoryPool at the beginning
    this->memPoolPtr = new unsigned char[memoryPoolSize];
    this->blkPtr = memPoolPtr;
    this->nextFree = memPoolPtr;

    this->memoryPoolUsed = 0;
    this->numAllocBlks = 0;
    this->numAvailBlks = memoryPoolSize / blkSize;
}
/**
 * to allocate a new block, we should increment the pool ptr by the number of blocks to be allocated
 * after allocation, we should increment the next free ptr to the address after the allocated memory blocks
 * @return status of allocation of the block
 */
bool MemoryPool::allocBlk() {

    if (numAvailBlks > 0) {
        memPoolPtr = blkPtr + (numAllocBlks * blkSize); // increment blkPtr by number of allocated blocks
        nextFree = blkPtr;

        numAvailBlks -= 1; // decrement the available number of blocks by 1
        numAllocBlks += 1; // increment the number of allocated blocks by 1
        memoryPoolUsed += blkSize; // add the block size allocated to the used memory pool

        return true;
    }

    else {
        cout << "MEMORY FULL";
    }
}

/**
 * Edge conditions to write records
 * 1. If there are no free blocks or no blocks have been allocated, create a new block
 * 2. if the record size is greater than the block size, then writing is not possible.
 * @param record record to be written onto the block
 * @return status of the write of the record
 */
unsigned char *MemoryPool::writeRecord(Record record) {

    if (numAllocBlks = 0) {
        bool successFlag = allocBlk();
        if (successFlag == false)
            return NULL;
    }

    if(blkSize < (nextFree - (blkPtr + sizeof(record)))){
        bool successFlag = allocBlk();
        if (successFlag == false)
            return NULL;
    }

    if (blkSize < sizeof(record)) {
        cout << "Record size is bigger than the block size";
        return NULL;
    }

    // write the record to the block
    // keep track of the address an an index
    memcpy(nextFree, &record, sizeof(record));
    unsigned char *index = nextFree;
    nextFree += sizeof(record);

    return index;
}

/**
 * Destructor
 */
MemoryPool::~MemoryPool() {
    // safe deletion of pointers involves using the delete operator and then initialising it to NULL, to allow for future reference
    delete memPoolPtr;
    memPoolPtr = NULL;
    blkPtr = NULL;
    nextFree = NULL;
}