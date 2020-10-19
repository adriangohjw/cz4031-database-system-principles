//
// Created by Abhishek Bhagwat on 13/10/20.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <tuple>
#include <unordered_map>
#include "memory-pool.h"

using namespace std;

typedef unsigned int uint;
typedef unsigned char uchar;


int main() {
    ifstream dataFile("/Users/abhishekbhagwat/CLionProjects/databaseDesign/data/data.tsv");
    cout << dataFile.is_open();

    MemPool memPool{100000000, 100};

    vector<tuple<void *, uint>> dataset;

    if(dataFile.is_open()) {
        string line;
        while (getline(dataFile, line)) {
            Record record;
//            cout << memPool.getMemPoolUsedBlks();

            stringstream linestream(line);
            getline(linestream, record.tconst, '\t');
            linestream >> record.averageRating >> record.numVotes;
            tuple<void *, uint> dataRecord = memPool.writeRecord(sizeof(record));
            dataset.push_back(dataRecord);
            // void * pointer stores the address of the block, but in order to perform pointer arithmetic
            // we have to cast into uint or uchar pointer.

            // memcpy may seem to be potentially dangerous, but it is safe in this usage as it is the only function that
            // allows copying of byte data and it is being performed inside the container.
            void *rcdAdr = (uchar *)get<0>(dataRecord) + get<1>(dataRecord);
            memcpy(rcdAdr, &record, sizeof(record));
//            cout<< "Block Address: " << get<0>(dataRecord) << " Record address: " << rcdAdr << "\n";
        }
    }

    // key:value pair to hold pair of memory addresses.
    unordered_map<void *, void*> blocksInMemory;
    //vector of tuples of record addresses <block address, relative record address>
    vector<tuple<void *, uint>>::iterator recordsIterator;

     for (recordsIterator = dataset.begin(); recordsIterator != dataset.end(); ++recordsIterator) {
         void *blockAddress = (uchar *)get<0>(*recordsIterator);
         uint offset = get<1>(*recordsIterator);

         if (blocksInMemory.find(blockAddress) == blocksInMemory.end()) {
             void *mainMemoryBlock = operator new(memPool.getBlkSize());
             memcpy(mainMemoryBlock, blockAddress, memPool.getBlkSize());

             blocksInMemory[blockAddress] = mainMemoryBlock;
         }

         void *recordAddress = (uchar *)blocksInMemory.at(blockAddress) + offset;
         cout << "Ratings block address " << blocksInMemory.at(blockAddress) << " Offset: " << offset <<"\n";
         cout << (*(Record *) recordAddress).averageRating << " at " << recordAddress << '\n';
         cout << (*(Record *) recordAddress).tconst << " at " << recordAddress << '\n';

     }
    return 0;
}