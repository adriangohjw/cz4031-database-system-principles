//
// Created by Abhishek Bhagwat on 13/10/20.
//

#ifndef DATABASEDESIGN_MEMORY_POOL_H
#define DATABASEDESIGN_MEMORY_POOL_H
#include <cstring>
#include<iostream>
#include <vector>
#include <tuple>
#include <algorithm>

const int MAX = 5;
//const int MIN_LEAF = 7;
//const int MIN_NON_LEAF = 6;
typedef unsigned int uint;
typedef unsigned char uchar;

using namespace std;

// Structure of the record being read from the data file

struct Record {
    char tconst[10];
    float averageRating;
    uint numVotes;
};

class MemPool {
private:
    uchar *memPoolPtr;
    uchar *blkPtr;

    uint memPoolSize;
    uint blkSize;
    uint memPoolUsedBlks;
    uint memPoolUsedRecords;
    uint curBlkUsed;

    int numAllocBlks;
    int numAvailBlks;

public:
    /**
     * Constructor to initialize class MemPool with the given arguments
     * @param bufferSize Size of the buffer memory pool
     * @param blkSize Size of the block to be allocated in the the MemPool
     */
    MemPool(uint memPoolSize, uint blkSize);

    /**
     * Destructor
     */
    ~MemPool();

    /**
     * function to allocate block in the memory pool
     * @return False if block is not allocated (ERROR)
     */

    bool allocBlk();

     /**
     * function to allocate memory for a single record
      * @param recordSize size of memory to be reserved for the particular record
      * @return tuple containing address of the blkPtr and the relative offset of the record inside the block. <blkPtr address, relative offset from blkPtr>
      */
     tuple<void *, uint> writeRecord(uint recordSize);


     /**
     * function to delete the record at a particular memory address or if a block has one record, to delete the memory reserved by the block
      * @param blkAddress starting address of the block where the record resides
      * @param relativeOffset relative address of the record inside the block
      * @param recordSize size of the record stored at the address
      * @return status of deletion of the record
      */
    bool deleteRecord(uchar *blkAddress, uint relativeOffset, uint recordSize);

    /**
     * function to get the size of each block
     * @return size of block in bytes
     */
    uint getBlkSize(){
        return blkSize;
    }

    /**
     * function to get the size of the memory pool
     * @return size of the MemPool
     */
    uint getMemPoolSize() {
        return memPoolSize;
    }

    /**
     * function to get amount of memory used in the MemPool based on number of blocks allocated
     * @return size of used up memory in the MemPool
     */
    int getMemPoolUsedBlks() {
        return memPoolUsedBlks;
    }

    /**
     * function to get amount of memory used in the MemPool based on number of records written
     * @return size of used up memory in the MemPool
     */
    int getMemPoolUsedRecords() {
        return memPoolUsedRecords;
    }

    /**
     * function to get the amount of memory used in the current block pointed by blkPtr
     * @return size of used up memory in the current block
     */
    int getCurBlkUsed(){
        return curBlkUsed;
    }

    /**
     * function to get the number of allocated blocks
     * @return number of allocated blocks
     */
    int getNumAllocBlks() {
        return numAllocBlks;
    }

    /**
     * function to get the number of available blocks in the MemPool
     * @return number of available blocks in MemPool
     */
    int getNumAvailBlks() {
        return numAvailBlks;
    }
};

#endif //DATABASEDESIGN_MEMORY_POOL_H

