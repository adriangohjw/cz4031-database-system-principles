//
// Created by Abhishek Bhagwat on 13/10/20.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <tuple>
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
            memcpy(reinterpret_cast<uint*>(get<0>(dataRecord)) + get<1>(dataRecord), &record, sizeof(record));
            cout << "Record address: " << reinterpret_cast<uint*>(get<0>(dataRecord))+ get<1>(dataRecord) << "\n";
        }
    }
    return 0;
}