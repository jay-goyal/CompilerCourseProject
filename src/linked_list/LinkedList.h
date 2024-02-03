#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct Node {
    char** key;
    int val;
    struct Node* next;
} node_t;

node_t* make_node(char** key, int val);
void insert_tail_node(node_t* head, char** key, int val);
void delete_tail_node(node_t* head);
void delete_list(node_t* head);

#endif
