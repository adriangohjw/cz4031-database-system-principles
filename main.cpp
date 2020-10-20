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
#include <cstring>
#include "BplusTree.cpp"
#include <typeinfo>



using namespace std;

typedef unsigned int uint;
typedef unsigned char uchar;

struct keys_struct{
    float key_value;
    vector <void*> add_vect;
};

class BTreeNode
{
    keys_struct *keys;  // An array of keys
    int t;      // Minimum degree (defines the range for number of keys)
    BTreeNode **C; // An array of child pointers
    int n;     // Current number of keys
    bool leaf; // Is true when node is leaf. Otherwise false

public:
    
    BTreeNode(int _t, bool _leaf);   // Constructor

    // A function to traverse all nodes in a subtree rooted with this node
    void traverse();

    // A function to search a key in subtree rooted with this node.
    BTreeNode *search(float k);

    // A function that returns the index of the first key that is greater
    // or equal to k
    int findKey(float k);

    // A utility function to insert a new key in the subtree rooted with
    // this node. The assumption is, the node must be non-full when this
    // function is called
    void insertNonFull(keys_struct k);

    // A utility function to split the child y of this node. i is index
    // of y in child array C[].  The Child y must be full when this
    // function is called
    void splitChild(int i, BTreeNode *y);

    // A wrapper function to remove the key k in subtree rooted with
    // this node.
    void remove(float k);

    // A function to remove the key present in idx-th position in
    // this node which is a leaf
    void removeFromLeaf(int idx);

    // A function to remove the key present in idx-th position in
    // this node which is a non-leaf node
    void removeFromNonLeaf(int idx);

    // A function to get the predecessor of the key- where the key
    // is present in the idx-th position in the node
    keys_struct getPred(int idx);

    // A function to get the successor of the key- where the key
    // is present in the idx-th position in the node
    keys_struct getSucc(int idx);

    // A function to fill up the child node present in the idx-th
    // position in the C[] array if that child has less than t-1 keys
    void fill(int idx);

    // A function to borrow a key from the C[idx-1]-th node and place
    // it in C[idx]th node
    void borrowFromPrev(int idx);

    // A function to borrow a key from the C[idx+1]-th node and place it
    // in C[idx]th node
    void borrowFromNext(int idx);

    // A function to merge idx-th child of the node with (idx+1)th child of
    // the node
    void merge(int idx);
    
    int height();

//     Make BTree friend of this so that we can access private members of
//     this class in BTree functions
    friend class BTree;
};

class BTree
{
    BTreeNode *root; // Pointer to root node
    int t;  // Minimum degree
public:

    // Constructor (Initializes tree as empty)
    BTree(int _t)
    {
        root = NULL;
        t = _t;
    }

    void traverse()
    {
        if (root != NULL) root->traverse();
    }
    
    int height()
    {
        return (root == NULL)? NULL : root->height();
    }

    // function to search a key in this tree
    BTreeNode* search(float k)
    {
        return (root == NULL)? NULL : root->search(k);
    }

    // The main function that inserts a new key in this B-Tree
    void insert(keys_struct k);

    // The main function that removes a new key in the B-Tree
    void remove(float k);

};

BTreeNode::BTreeNode(int t1, bool leaf1)
{
    // Copy the given minimum degree and leaf property
    t = t1;
    leaf = leaf1;

    // Allocate memory for maximum number of possible keys
    // and child pointers
    keys = new keys_struct[2*t-1];
    C = new BTreeNode *[2*t];

    // Initialize the number of keys as 0
    n = 0;
}

// A utility function that returns the index of the first key that is
// greater than or equal to k
int BTreeNode::findKey(float k)
{
    int idx=0;
    while (idx<n && keys[idx].key_value < k)
        ++idx;
    return idx;
}

// A function to remove the key k from the sub-tree rooted with this node
void BTreeNode::remove(float k)
{
    int idx = findKey(k);

    // The key to be removed is present in this node
    if (idx < n && keys[idx].key_value == k)
    {

        // If the node is a leaf node - removeFromLeaf is called
        // Otherwise, removeFromNonLeaf function is called
        if (leaf)
            removeFromLeaf(idx);
        else
            removeFromNonLeaf(idx);
    }
    else
    {

        // If this node is a leaf node, then the key is not present in tree
        if (leaf)
        {
            cout << "The key "<< k <<" is does not exist in the tree\n";
            return;
        }

        // The key to be removed is present in the sub-tree rooted with this node
        // The flag indicates whether the key is present in the sub-tree rooted
        // with the last child of this node
        bool flag = ( (idx==n)? true : false );

        // If the child where the key is supposed to exist has less that t keys,
        // we fill that child
        if (C[idx]->n < t)
            fill(idx);

        // If the last child has been merged, it must have merged with the previous
        // child and so we recurse on the (idx-1)th child. Else, we recurse on the
        // (idx)th child which now has atleast t keys
        if (flag && idx > n)
            C[idx-1]->remove(k);
        else
            C[idx]->remove(k);
    }
    return;
}

// A function to remove the idx-th key from this node - which is a leaf node
void BTreeNode::removeFromLeaf (int idx)
{

    // Move all the keys after the idx-th pos one place backward
    for (int i=idx+1; i<n; ++i)
        keys[i-1] = keys[i];

    // Reduce the count of keys
    n--;

    return;
}

// A function to remove the idx-th key from this node - which is a non-leaf node
void BTreeNode::removeFromNonLeaf(int idx)
{

    float k = keys[idx].key_value;

    // If the child that precedes k (C[idx]) has atleast t keys,
    // find the predecessor 'pred' of k in the subtree rooted at
    // C[idx]. Replace k by pred. Recursively delete pred
    // in C[idx]
    if (C[idx]->n >= t)
    {
        keys_struct pred = getPred(idx);
        keys[idx].key_value = pred.key_value;
        keys[idx].add_vect = pred.add_vect;
        C[idx]->remove(pred.key_value);
    }

        // If the child C[idx] has less that t keys, examine C[idx+1].
        // If C[idx+1] has atleast t keys, find the successor 'succ' of k in
        // the subtree rooted at C[idx+1]
        // Replace k by succ
        // Recursively delete succ in C[idx+1]
    else if  (C[idx+1]->n >= t)
    {
        keys_struct succ = getSucc(idx);
        keys[idx].key_value = succ.key_value;
        keys[idx].add_vect = succ.add_vect;
        C[idx+1]->remove(succ.key_value);
    }

        // If both C[idx] and C[idx+1] has less that t keys,merge k and all of C[idx+1]
        // into C[idx]
        // Now C[idx] contains 2t-1 keys
        // Free C[idx+1] and recursively delete k from C[idx]
    else
    {
        merge(idx);
        C[idx]->remove(k);
    }
    return;
}

// A function to get predecessor of keys[idx]
keys_struct BTreeNode::getPred(int idx)
{
    // Keep moving to the right most node until we reach a leaf
    BTreeNode *cur=C[idx];
    while (!cur->leaf)
        cur = cur->C[cur->n];
    
    keys_struct key;
    key.key_value = cur->keys[cur->n-1].key_value;
    key.add_vect = cur->keys[cur->n-1].add_vect;
    
    // Return the last key of the leaf
    return key;
}

keys_struct BTreeNode::getSucc(int idx)
{

    // Keep moving the left most node starting from C[idx+1] until we reach a leaf
    BTreeNode *cur = C[idx+1];
    while (!cur->leaf)
        cur = cur->C[0];

    // Return the first key of the leaf
    keys_struct key;
    key.key_value = cur->keys[0].key_value;
    key.add_vect = cur->keys[0].add_vect;
    return key;
}

// A function to fill child C[idx] which has less than t-1 keys
void BTreeNode::fill(int idx)
{

    // If the previous child(C[idx-1]) has more than t-1 keys, borrow a key
    // from that child
    if (idx!=0 && C[idx-1]->n>=t)
        borrowFromPrev(idx);

        // If the next child(C[idx+1]) has more than t-1 keys, borrow a key
        // from that child
    else if (idx!=n && C[idx+1]->n>=t)
        borrowFromNext(idx);

        // Merge C[idx] with its sibling
        // If C[idx] is the last child, merge it with with its previous sibling
        // Otherwise merge it with its next sibling
    else
    {
        if (idx != n)
            merge(idx);
        else
            merge(idx-1);
    }
    return;
}

// A function to borrow a key from C[idx-1] and insert it
// into C[idx]
void BTreeNode::borrowFromPrev(int idx)
{

    BTreeNode *child=C[idx];
    BTreeNode *sibling=C[idx-1];

    // The last key from C[idx-1] goes up to the parent and key[idx-1]
    // from parent is inserted as the first key in C[idx]. Thus, the  loses
    // sibling one key and child gains one key

    // Moving all key in C[idx] one step ahead
    for (int i=child->n-1; i>=0; --i)
        child->keys[i+1] = child->keys[i];

    // If C[idx] is not a leaf, move all its child pointers one step ahead
    if (!child->leaf)
    {
        for(int i=child->n; i>=0; --i)
            child->C[i+1] = child->C[i];
    }

    // Setting child's first key equal to keys[idx-1] from the current node
    child->keys[0] = keys[idx-1];

    // Moving sibling's last child as C[idx]'s first child
    if(!child->leaf)
        child->C[0] = sibling->C[sibling->n];

    // Moving the key from the sibling to the parent
    // This reduces the number of keys in the sibling
    keys[idx-1] = sibling->keys[sibling->n-1];

    child->n += 1;
    sibling->n -= 1;

    return;
}

// A function to borrow a key from the C[idx+1] and place
// it in C[idx]
void BTreeNode::borrowFromNext(int idx)
{

    BTreeNode *child=C[idx];
    BTreeNode *sibling=C[idx+1];

    // keys[idx] is inserted as the last key in C[idx]
    child->keys[(child->n)] = keys[idx];

    // Sibling's first child is inserted as the last child
    // into C[idx]
    if (!(child->leaf))
        child->C[(child->n)+1] = sibling->C[0];

    //The first key from sibling is inserted into keys[idx]
    keys[idx] = sibling->keys[0];

    // Moving all keys in sibling one step behind
    for (int i=1; i<sibling->n; ++i)
        sibling->keys[i-1] = sibling->keys[i];

    // Moving the child pointers one step behind
    if (!sibling->leaf)
    {
        for(int i=1; i<=sibling->n; ++i)
            sibling->C[i-1] = sibling->C[i];
    }

    // Increasing and decreasing the key count of C[idx] and C[idx+1]
    // respectively
    child->n += 1;
    sibling->n -= 1;

    return;
}

// A function to merge C[idx] with C[idx+1]
// C[idx+1] is freed after merging
void BTreeNode::merge(int idx)
{
    BTreeNode *child = C[idx];
    BTreeNode *sibling = C[idx+1];

    // Pulling a key from the current node and inserting it into (t-1)th
    // position of C[idx]
    child->keys[t-1] = keys[idx];

    // Copying the keys from C[idx+1] to C[idx] at the end
    for (int i=0; i<sibling->n; ++i)
        child->keys[i+t] = sibling->keys[i];

    // Copying the child pointers from C[idx+1] to C[idx]
    if (!child->leaf)
    {
        for(int i=0; i<=sibling->n; ++i)
            child->C[i+t] = sibling->C[i];
    }

    // Moving all keys after idx in the current node one step before -
    // to fill the gap created by moving keys[idx] to C[idx]
    for (int i=idx+1; i<n; ++i)
        keys[i-1] = keys[i];

    // Moving the child pointers after (idx+1) in the current node one
    // step before
    for (int i=idx+2; i<=n; ++i)
        C[i-1] = C[i];

    // Updating the key count of child and the current node
    child->n += sibling->n+1;
    n--;

    // Freeing the memory occupied by sibling
    delete(sibling);
    return;
}

// The main function that inserts a new key in this B-Tree
void BTree::insert(keys_struct k)
{
    // If tree is empty
    if (root == NULL)
    {
        // Allocate memory for root
        root = new BTreeNode(t, true);
        root->keys[0].key_value = k.key_value;  // Insert key
        root->n = 1;  // Update number of keys in root
        root->keys[0].add_vect = k.add_vect;
    }
    else // If tree is not empty
    {
        // If root is full, then tree grows in height
        //cout<< k.key_value << "\n";
        BTreeNode *searchval = search(k.key_value);
        
//        cout<<"nullpointer "<< (searchval==nullptr)<< " with"<<k.key_value<<"\n";
        if (searchval==nullptr){
            
            if (root->n == 2*t-1)
            {
                // Allocate memory for new root
                BTreeNode *s = new BTreeNode(t, false);

                s->C[0] = root;

                s->splitChild(0, root);

                int i = 0;
                if (s->keys[0].key_value < k.key_value)
                    i++;
                s->C[i]->insertNonFull(k);

                // Change root
                root = s;
            }
            else  // If root is not full, call insertNonFull for root
                root->insertNonFull(k);
        }
        else{
            
            int i = 0;
            while (i < searchval->n && k.key_value > searchval->keys[i].key_value){
                i++;
//                cout<<searchval->keys[i].key_value<< " ";
                //cout<<"\n";
            }
            
            
            if (searchval->keys[i].key_value == k.key_value){
                //cout << "hello " << k.key_value << " address " << searchval->keys[i].key_value<<" yayy";
                (searchval->keys[i].add_vect).push_back((void*)k.add_vect.front());
            }
            
            
            
        }
    }
}

// A utility function to insert a new key in this node
// The assumption is, the node must be non-full when this
// function is called
void BTreeNode::insertNonFull(keys_struct k)
{
    // Initialize index as index of rightmost element
    int i = n-1;

    // If this is a leaf node
    if (leaf == true)
    {

        while (i >= 0 && keys[i].key_value > k.key_value)
        {
            keys[i+1] = keys[i];
            i--;
        }

        // Insert the new key at found location
        keys[i+1].key_value = k.key_value;
        keys[i+1].add_vect = k.add_vect;
        n = n+1;
    }
    else // If this node is not leaf
    {
        // Find the child which is going to have the new key
        while (i >= 0 && keys[i].key_value > k.key_value)
            i--;

        
        if (C[i+1]->n == 2*t-1)
        {
            
            splitChild(i+1, C[i+1]);
            if (keys[i+1].key_value < k.key_value)
                i++;
        }
        C[i+1]->insertNonFull(k);
    }
}

// A utility function to split the child y of this node
// Note that y must be full when this function is called
void BTreeNode::splitChild(int i, BTreeNode *y)
{
    // Create a new node which is going to store (t-1) keys
    // of y
    BTreeNode *z = new BTreeNode(y->t, y->leaf);
    z->n = t - 1;

    // Copy the last (t-1) keys of y to z
    for (int j = 0; j < t-1; j++)
        z->keys[j] = y->keys[j+t];

    // Copy the last t children of y to z
    if (y->leaf == false)
    {
        for (int j = 0; j < t; j++)
            z->C[j] = y->C[j+t];
    }

    // Reduce the number of keys in y
    y->n = t - 1;

    // Since this node is going to have a new child,
    // create space of new child
    for (int j = n; j >= i+1; j--)
        C[j+1] = C[j];

    // Link the new child to this node
    C[i+1] = z;

    // A key of y will move to this node. Find location of
    // new key and move all greater keys one space ahead
    for (int j = n-1; j >= i; j--)
        keys[j+1] = keys[j];

    // Copy the middle key of y to this node
    keys[i] = y->keys[t-1];

    // Increment count of keys in this node
    n = n + 1;
}

// Function to traverse all nodes in a subtree rooted with this node
void BTreeNode::traverse()
{
//    // There are n keys and n+1 children, travers through n keys
//    // and first n children
//    int i;
//    for (i = 0; i < n; i++)
//    {
//        // If this is not leaf, then before printing key[i],
//        // traverse the subtree rooted with child C[i].
//        if (leaf == false)
//            C[i]->traverse();
//        cout << " " << keys[i].key_value;
//        cout << " ";
//    cout << " " << (*(Record *) keys[i].add_vect[0]).tconst;
//    }
//    // Print the subtree rooted with last child
//    if (leaf == false)
//        C[i]->traverse();
    
    if(leaf==false){
        for(int i = 0; i<n+1;i++){
            C[i]->traverse();
            //read(curr->child_ptr[i]);

        }
    }
    if(leaf==true){
        for (int i = 0; i<n; i++){
            cout<<"rating "<<keys[i].key_value<<" ";
            cout << (*(Record *) keys[i].add_vect[0]).tconst << " " << keys[i].add_vect.size() << " " << keys[i].add_vect.front() << "\n";
        }
    }
}

// Function to search key k in subtree rooted with this node
BTreeNode *BTreeNode::search(float k)
{
//    cout<<"K inside search: "<< k <<"\n";
//    // Find the first key greater than or equal to k
//    int i = 0;
//    while (i < n && k > keys[i].key_value)
//        i++;
//
//    // If the found key is equal to k, return this node
//    if (keys[i].key_value == k and leaf==true)
//        return this;
//
//    // If key is not found here and this is a leaf node
//    if (leaf == true)
//        return NULL;
//
//    // Go to the appropriate child
//    return C[i]->search(k);
    
        if (leaf != true){
            for(int i = 0; i<n; i++){
                if(k<keys[i].key_value){
                    return C[i]->search(k);
                    break;
                }
                else if(i == n-1){
                    return C[i+1]->search(k);
                    break;
                }
            }
        }
        else if (leaf == true){
            bool there = false;
            for (int i = 0 ; i<n; i++){
                if(keys[i].key_value == k){
                    there = true;
                    return this;
                    break;
                }
            }
            if (there == false){
                return nullptr;
            }
        }

    
    return nullptr;
}

void BTree::remove(float k)
{
    if (!root)
    {
        cout << "The tree is empty\n";
        return;
    }

    // Call the remove function for root
    root->remove(k);

    // If the root node has 0 keys, make its first child as the new root
    //  if it has a child, otherwise set root as NULL
    if (root->n==0)
    {
        BTreeNode *tmp = root;
        if (root->leaf)
            root = NULL;
        else
            root = root->C[0];

        // Free the old root
        delete tmp;
    }
    return;
}

int BTreeNode::height(){
    if(leaf==false){
        return C[0]->height() + 1;
    }
    else if(leaf==true){
        return 0;
    }
    else{
    return NULL;
    }
}


int main() {
    cout <<"<------------------- Database Storage Component ------------------->\n"
           "Database is created by allocating a memory pool, divided into blocks\n"
           "We shall make use of a fixed-size memory pool for storage" << "\n" << "\n";

    cout << "<------------------- Data file read started ------------------->" << "\n" << "\n";

    ifstream dataFile("/Users/abhishekbhagwat/CLionProjects/databaseDesign/data/data.tsv");

    MemPool memPool{100000000, 500};

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

    BplusTree node;
    int search_index;
    BTree t(3);

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
//         cout<<key.key_value<<"before insert\n";
         t.insert(key);
         i++;
     }

    t.traverse();
    cout << t.height();
    return 0;
}
