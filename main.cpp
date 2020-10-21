#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <tuple>
#include <unordered_map>
#include "memory-pool.h"
#include <cstring>
#include "b-plus-tree.cpp"
#include <typeinfo>



using namespace std;

typedef unsigned int uint;
typedef unsigned char uchar;

int main() {
    cout <<"<------------------- Database Storage Component ------------------->\n"
           "Database is created by allocating a memory pool, divided into blocks\n"
           "We shall make use of a fixed-size memory pool for storage" << "\n" << "\n";

    cout << "<------------------- Data file read started ------------------->" << "\n" << "\n";

    ifstream dataFile("/home/hitesh/CLionProjects/cz4031-database-system-principles/data/data.tsv");

    MemPool memPool{100000000, 100};

    vector<tuple<void *, uint>> dataset;
    bool flag=true;
    if(dataFile.is_open()) {
        string line;
        while (getline(dataFile, line)) {
            if(flag) {
                flag=false;
                continue;
            }

            Record record;
            string tempLine;
            //copy bytes till we encounter tabspace
            strcpy(record.tconst, line.substr(0, line.find('\t')).c_str());


            stringstream linestream(line);
            getline(linestream, tempLine,'\t');
            linestream >> record.averageRating >> record.numVotes;
            tuple<void *, uint> dataRecord = memPool.writeRecord(sizeof(record));
            dataset.push_back(dataRecord);

            // void * pointer stores the address of the block, but in order to perform pointer arithmetic
            // we have to cast into uint or uchar pointer.

            // memcpy may seem to be potentially dangerous, but it is safe in this usage as it is the only function that
            // allows copying of byte data and it is being performed inside the container.
            void *rcdAdr = (uchar *)get<0>(dataRecord) + get<1>(dataRecord);
            memcpy(rcdAdr, &record, sizeof(record));
//            cout << rcdAdr << " " << record.tconst << '\n';

        }
        cout << "<------------------- Data file read ended ------------------->" << "\n" << "\n";

        cout << "<------------------- Database Statistics ------------------->" << "\n";
        cout << "1. Size of Memory Pool: " << memPool.getMemPoolSize() << "\n";
        cout << "2. Size of 1 block: " << memPool.getBlkSize() << "\n";
        cout << "3. Number of blocks available at start: " << memPool.getMemPoolSize() / memPool.getBlkSize() << "\n";
        cout << "4. Number of allocated blocks: " << memPool.getNumAllocBlks() << "\n";
        cout << "5. Number of available blocks: " << memPool.getNumAvailBlks() << "\n" << '\n';


        dataFile.close();
    }

    // key:value pair to hold pair of memory addresses.
    unordered_map<void *, void*> blocksInMemory;
    //vector of tuples of record addresses <block address, relative record address>
    vector<tuple<void *, uint>>::iterator recordsIterator;

    BPTree node;
    int search_index;
    //BTree t(3);
    int i=0;
     for (recordsIterator = dataset.begin(); recordsIterator != dataset.end(); ++recordsIterator) {
         void *blockAddress = (uchar *)get<0>(*recordsIterator);
         uint offset = get<1>(*recordsIterator);

         if (blocksInMemory.find(blockAddress) == blocksInMemory.end()) {
             void *mainMemoryBlock = operator new(memPool.getBlkSize());
             memcpy(mainMemoryBlock, blockAddress, memPool.getBlkSize());

             blocksInMemory[blockAddress] = mainMemoryBlock;
         }

         void *recordAddress = (uchar *)blocksInMemory.at(blockAddress) + offset;
//         cout << (*(Record *) recordAddress).averageRating << (*(Record *) recordAddress).tconst << " at " << recordAddress << '\n';
         float num = (*(Record *) recordAddress).averageRating;
         keys_struct key;
         key.key_value = num;
         key.add_vect.push_back((uchar *) blocksInMemory.at(blockAddress) + offset);
         node.insert(key);

         i++;
     }
     int count=0;
     cout << "\n";
    cout <<node.display(node.getRoot(), count, true)<<"\n";
    cout << node.height(node.getRoot())<<"\n";
     cout << "\n";
     count=0;
    node.search(9, true, false);
    keys_struct key;
    key.key_value = 4.1;
    key.add_vect.push_back((uchar *) nullptr );
    //cout <<node.display(node.getRoot(), count, true)<<"\n";
    node.remove(key);
    //cout << "After delete \n";
    cout <<node.display(node.getRoot(), count, true)<<"\n";
    return 0;
}
