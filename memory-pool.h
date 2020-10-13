//
// Created by Abhishek Bhagwat on 13/10/20.
//

#ifndef DATABASEDESIGN_MEMORY_POOL_H
#define DATABASEDESIGN_MEMORY_POOL_H

#include <iostream>
#include <vector>

using namespace std;

// Structure of the record being read from the data file
struct Record {
    string tconst;
    float averageRating;
    unsigned int numVotes;
};

class MemoryPool {
private:
    unsigned char *memPoolPtr;
    unsigned char *blkPtr;
    unsigned char *nextFree;
    unsigned int memoryPoolSize;
    unsigned int blkSize;
    unsigned int memoryPoolUsed;
    int numAllocBlks;
    int numAvailBlks;

public:
    /**
     * Constructor to initialize class MemoryPool with the given arguments
     * @param bufferSize Size of the buffer memory pool
     * @param blkSize Size of the block to be allocated in the the MemoryPool
     */
    MemoryPool(unsigned int memoryPoolSize, unsigned int blkSize);

    /**
     * function to allocate block in the memory pool
     * @return False if block is not allocated (ERROR)
     */
    bool allocBlk();

    /**
     * function to deallocate block in the buffer pool
     * @return False if block is not deallocated (ERROR)
     */
    bool deallocBlk();

    /**
     * function to allocate a memory chunk ~ allocate memory for a single record
     * @param record Record to be written to memory chunk
     * @return Pointer to an unused space in the memory pool
     */
    unsigned char *writeRecord(Record record);

    unsigned int getBlkSize(){
        return blkSize;
    }

    /**
     * function to get the size of the memory pool
     * @return size of the MemoryPool
     */
    unsigned int getMemPoolSize() {
        return memoryPoolSize;
    }

    /**
     * function to get amount of memory used in the MemoryPool
     * @return size of used up memory in the MemoryPool
     */
    int getMemPoolUsed() {
        return memoryPoolUsed;
    }

    /**
     * function to get the number of allocated blocks
     * @return number of allocated blocks
     */
    int getNumAllocBlks() {
        return numAllocBlks;
    }

    /**
     * function to get the number of available blocks in the MemoryPool
     * @return number of available blocks in MemoryPool
     */
    int getNumAvailBlks() {
        return numAvailBlks;
    }

    /**
     * Destructor
     */
    ~MemoryPool();
};

#endif //DATABASEDESIGN_MEMORY_POOL_H
