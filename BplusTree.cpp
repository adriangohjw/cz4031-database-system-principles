//
// Created by Hitesh Agarwal on 20/10/20.
//

#include<iostream>
#include <cmath>
#include "memory-pool.h"


using namespace std;

struct node {
    float *rating;
    node **child_ptr;
    node *parent_ptr;
    bool leaf;
    int n;

node(){

    this->n=0;
    this->rating = new float[MAX];
    this->child_ptr = new node*[MAX+1];
    this->parent_ptr=NULL;
    this->leaf = true;
}
};
class BplusTree{

    int height;
    int n;
    int nodes;


public:

    node *root;

    /*
    BplusTree();
    void insert(float);
    node* search(node*, float, int*);
    void del(float);
    void read(node*);
    void split(node*, float, node*, node*);
    void insertInNode(node*, float);
    */

BplusTree() {
    root = nullptr;
}

void insertInNode(node* cur, float r){
    for (int i=0;i< cur->n;i++){
        if (r<cur->rating[i]){
            for (int j=(cur->n);j>=i;j--){
                cur->rating[j] = cur->rating[j-1];
            }
            cur->rating[i] = r;
            (cur->n)++;
            break;
        }
        if (i==(cur->n)-1){
            cur->rating[cur->n] = r;
            (cur->n)++;
            break;
        }
    }
}
void insert(float avgRating){
    if (root==nullptr){
        root = new node;
        root->rating[0] = avgRating;
        root->leaf = true;
        root->parent_ptr = nullptr;
        root->n = 1;
    }
    else{
        node *current = root;
        while(current->leaf != true){
            for (int i=0;i<current->n;i++){
                if (avgRating < current->rating[i]){
                    //current->parent_ptr = current;
                    current = current->child_ptr[i];
                    break;
                }
                if (i == (current->n) - 1){
                    //current->parent_ptr = current;
                    current = current->child_ptr[i+1];
                    break;
                }
            }
        }
        if (current->n == MAX){
            node *child;
            node *x;
            child = new node;
            x = new node;
            split(current, avgRating, child, x);
        }
        else{
            insertInNode(current, avgRating);
        }
    }
}
void split(node *cur, float r, node *child, node *x){
    insertInNode(cur, r);
    float temp = cur->rating[MAX];
    if (cur->leaf == true){
        cur->child_ptr[MAX] = child;
        int val = floor((MAX+1)/2);

        for (int i= val;i<MAX;i++){
            child->rating[i-val] = cur->rating[i];
            //child->child_ptr[i-val] = cur->child_ptr[i+2];
            cur->rating[i] = NULL;
        }
        child->rating[val-1] = temp;
        cur->n = val;
        child->n = val;
    }
    else{

        //printf("hihi \n");
        //printf("%.2lf \n", child->rating[0]);
        //printf("%.2lf \n", child->rating[1]);
        //printf("%.2lf \n", child->rating[2]);

        int val = floor((MAX+1)/2);
        float temp2 = cur->rating[val];
        cur->rating[val] = NULL;

        for (int i= val+1;i<MAX;i++){
            child->rating[i-(val+1)] = cur->rating[i];
            child->child_ptr[i-(val+1)] = cur->child_ptr[i];
            cur->rating[i] = NULL;
            cur->child_ptr[i] = NULL;
        }
        child->rating[val-2] = temp;
        child->child_ptr[val-2] = cur->child_ptr[MAX];
        child->child_ptr[val-1] = cur->child_ptr[MAX]->child_ptr[MAX];
        cur->child_ptr[MAX+1] = NULL;
        cur->n = val;
        child->n = val-1;
        //printf("hihi \n");
        //printf("%.2lf \n", child->rating[0]);
        //printf("%.2lf \n", child->child_ptr[0]->rating[0]);
        //printf("%.2lf \n", child->rating[2]);
    }

    if (cur->parent_ptr == NULL){
        //printf("hi \n");
        x->leaf = false;
        cur->parent_ptr = x;
        child->parent_ptr = x;
        if (cur->leaf == true){
            x->rating[0] = child->rating[0];

        }
        else{
            x->rating[0] = child->child_ptr[0]->rating[0];
        }
        x->child_ptr[0] = cur;
        x->child_ptr[1] = child;

        x->parent_ptr = NULL;
        x->n = 1;
        root = x;
        //printf("hi \n");
    }

    else{
        if (cur->parent_ptr->n == MAX){
            node *child;
            node *x;
            child = new node;
            child->leaf = false;
            x = new node;
            split(cur->parent_ptr, cur->child_ptr[MAX]->rating[0], child, x);

        }
        else{
            cur->parent_ptr->n++;
            cur->parent_ptr->rating[cur->parent_ptr->n - 1] = cur->child_ptr[MAX]->rating[0];
            cur->parent_ptr->child_ptr[cur->parent_ptr->n] = cur->child_ptr[MAX];
            cur->child_ptr[MAX]->parent_ptr = cur->parent_ptr;
        }
    }
}

void del(float rat){
    int search_index;
    node *curr = search(root, rat, &search_index);
    if (search_index == -1){
        printf("Element for deletion is not there in B+ tree \n");
        return;
    }
    printf("Element to be deleted: %.1lf ", curr->rating[search_index]);

    if (curr->leaf == true){
        if (curr->n >= floor((curr->n+1)/2)+1){
            if (search_index != 0){
                //remove element and shift other keys
            }
            else{
                //remove element, shift node, check parent element
            }
        }
        else{
            //merge blocks
        }
    }
}
/*
void BplusTree::delInternal(node*, float rat){

}
*/

node* search(node *current, float num, int *search_index){
    if (root==NULL){
        cout<<"BplusTree is empty";
        *search_index = -1;
    }
    else{
        node *resultnode;
        if (current->leaf != true){
            for(int i = 0; i<current->n; i++){
                if(num<current->rating[i]){
                    current = current->child_ptr[i];
                    resultnode = search(current, num, search_index);
                    return resultnode;
                    break;
                }
                else if(i == (current->n)-1){
                    current = current->child_ptr[i+1];
                    resultnode = search(current, num , search_index);
                    return resultnode;
                    break;
                }
            }
        }
        else if (current->leaf == true){
            bool there = false;
            for (int i = 0 ; i<current->n; i++){
                if(current->rating[i] == num){
                    there = true;
                    *search_index = i;
                    return current;
                    break;
                }
            }
            if (there == false){
                cout<< "it is not there";
                *search_index = -1;
            }
        }

    }
    return NULL;
}

void read(node *curr, int h){
    if(curr->leaf!=true){
        for(int i = 0; i<(curr->n)+1;i++){
            read(curr->child_ptr[i], h+1);

        }
    }
    if(curr->leaf==true){
        for (int i = 0; i<curr->n; i++){
            cout<<"rating "<<curr->rating[i]<<"\n";
            cout<<"height "<<h+1<<"\n";
        }
    }
}

};