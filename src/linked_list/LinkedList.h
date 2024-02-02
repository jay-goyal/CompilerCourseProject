#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdlib.h>
#include <stdio.h>

struct Node {
    int val;
    struct Node* next;
};


struct Node* makeNode(int val);


void insert_tail_node(struct Node* head, int val);


void delete_tail_node(struct Node* head);

#endif 
