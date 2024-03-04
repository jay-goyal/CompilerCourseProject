/*
GROUP 20
VAIBHAV SINGLA - 2021A7PS2227P
JAY GOYAL - 2021A7PS2418P
SANJEEV MALLICK - 2021A7PS2217P
TRAYAMBAK SHRIVASTAVA - 2021A7PS1629P
PRANAV TANNA - 2021A7PS2685P
ARYAN BANSAL - 2021A7PS2776P
*/

#ifndef PARSERDEF_H
#define PARSERDEF_H

typedef struct ParseTable {
    prod_t ***table;
} pt_t;

typedef struct Treetnode tnode_t;
struct Treetnode {
    int val;
    int num_children;
    tokeninfo_t tokeninfo;
    tnode_t **children;
    tnode_t *parent;
};

typedef struct Tree {
    tnode_t *root;
} tree_t;

typedef struct Stack {
    int size;
    tnode_t **nodes;
} stack_t;


#endif  // PARSERDEF_H
