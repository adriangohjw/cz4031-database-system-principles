//
// Created by Abhishek Bhagwat on 13/10/20.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include "memory-pool.h"

using namespace std;

int main() {
    MemoryPool memPool{900000000, 100};
    ifstream file("/data/data.tsv");
    string line;
    int i = 0;
    while(getline(file, line)){
        i++;
        string title;
        float avgRating;
        unsigned int numVote;

//        cout << memPool.getNumAvailBlks() << "\n";

        stringstream linestream(line);
        getline(linestream, title, '\t');
        linestream >> avgRating >> numVote;
        cout << title << ' ' << avgRating << ' ' << numVote << '\n';

        Record record {title, avgRating, numVote};
        memPool.writeRecord(record);

        cout << memPool.getNumAvailBlks() << "\n";
    }

// ---------------- Test -------------------
//    Record test{"tt0000001", 10.0, 123456};
//    Record test1{"tt0000002", 0.0, 654321};
//
//    memPool.writeRecord(test);
//    memPool.writeRecord(test1);

    return 0;
}
