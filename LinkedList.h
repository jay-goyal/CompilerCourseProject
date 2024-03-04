/*
GROUP 20
VAIBHAV SINGLA - 2021A7PS2227P
JAY GOYAL - 2021A7PS2418P
SANJEEV MALLICK - 2021A7PS2217P
TRAYAMBAK SHRIVASTAVA - 2021A7PS1629P
PRANAV TANNA - 2021A7PS2685P
ARYAN BANSAL - 2021A7PS2776P
*/

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "lexerDef.h"

typedef struct Node {
    stentry_t* key;
    struct Node* next;
} node_t;

node_t* make_node(stentry_t* key);
node_t* insert_tail_node(node_t* head, stentry_t* key);
void delete_tail_node(node_t* head);
void delete_list(node_t* head);

#endif
