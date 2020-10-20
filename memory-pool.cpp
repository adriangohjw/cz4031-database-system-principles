//
// Created by Abhishek Bhagwat on 13/10/20.
//

/**
 * This implementation of the memory pool is based on the idea of the fixed-size memory pool allocator.
 * A contiguous section of memory is reserved for the pool, which is further divided into blocks.
 * Records of data are stored in these blocks sequentially. Each memory block can be accessed by the address of the
 * first block, size of the block and number of blocks allocated. The algorithm below just keeps track of the block
 * operations and usage as they are frequently allocated and deallocated.
 */


#include "memory-pool.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>

typedef unsigned int uint;
typedef unsigned char uchar;

using namespace std;

/**
 * MemPool Constructor
 * @param memPoolSize Overall size of the MemPool
 * @param blkSize Size of each block to be allocated in the MemPool
 */

MemPool::MemPool(uint memPoolSize, uint blkSize) {
    this->memPoolSize = memPoolSize;
    this->blkSize = blkSize;
    uchar* memPoolPtr = nullptr;
    this->memPoolPtr = new uchar[memPoolSize]; // allocate memPoolSize uchars and store it in memPoolPtr and initialize it to NULL.
    this->blkPtr = nullptr;
    this->memPoolUsedBlks = 0;
    this->memPoolUsedRecords = 0;
    this->numAllocBlks = 0;
    this->numAvailBlks = memPoolSize / blkSize;
    this -> curBlkUsed = 0;
}

/**
 * to allocate a new block, we should increment the pool ptr by the number of blocks to be allocated
 * after allocation, we should increment the next free ptr to the address after the allocated memory blocks
 * @return status of allocation of the block
 */
bool MemPool::allocBlk() {

    if (numAvailBlks > 0) {
        blkPtr = memPoolPtr + (numAllocBlks * blkSize); // increment blkPtr by number of allocated blocks
        memPoolUsedBlks+=blkSize;
        numAvailBlks -= 1; // decrement the available number of blocks by 1
        numAllocBlks += 1; // increment the number of allocated blocks by 1
        curBlkUsed = 0;

        return true;
    }

    else {
        cout << "MEMORY FULL";
        return false;
    }
}

/**
 * Edge conditions to write records
 * 1. If there are no free space in the blocks or no blocks have been allocated, create a new block
 * 2. if the record size is greater than the block size, then writing is not possible.
 * @param record record to be written onto the block
 * @return status of the write of the record
 */
tuple<void * , uint> MemPool::writeRecord(uint recordSize) {

    if(blkSize < (curBlkUsed + recordSize) or numAllocBlks == 0){
        if (!allocBlk())
            throw "Unable to reserve space as no free space in blocks or no blocks can be allocated";
    }

    if (blkSize < recordSize) {
        throw "Unable to reserve space as record size is greater than the block size";
    }

    // Create a tuple for the address where the record is written <block address, relative offset>
    // The record can be accessed at the address (block address + relative offset)

    // void * pointer stores the address of the block, but in order to perform pointer arithmetic, this further needs
    // to be cast into uint or uchar pointer
    tuple<void * , uint> recordAddress(blkPtr, curBlkUsed);

    memPoolUsedRecords+=recordSize;
    curBlkUsed+=recordSize;

    return recordAddress;
}

/**
 * function to delete the record from the given address.
 * Edge Case : If the given address points to an empty block, then delete the block
 * @param blkAddress address of the block where the record resides
 * @param relativeOffset address of the record inside the block, relative to the block start address
 * @param recordSize size of the record to be deleted
 * @return status of deletion of the record
 */
bool MemPool::deleteRecord(uchar *blkAddress, uint relativeOffset, uint recordSize) {
    try {
        // to delete a record, we can change the values stored in that record to NULL
        // traverse from the beginning of the record address to the end based on the size of the record
        // fill the elements to the null character
        memPoolUsedRecords-=recordSize;
        fill(blkAddress+relativeOffset, blkAddress+relativeOffset+recordSize, '\0');

        uchar cmpBlk [recordSize];
        fill(cmpBlk, cmpBlk+recordSize, '\0');

        if(equal(cmpBlk, cmpBlk+recordSize, blkAddress)){
            memPoolUsedBlks-=blkSize;
        }

        return true;
    }

    catch(exception &e) {
        cout << "Exception" <<e.what() << "\n";
        cout << "Delete record or block failed" << "\n";
        return false;
    }
}

/**
 * Destructor
 */
MemPool::~MemPool() {
    // safe deletion of pointers involves using the delete operator and then initialising it to NULL, to allow for future reference
    delete memPoolPtr;
    memPoolPtr = nullptr;
}