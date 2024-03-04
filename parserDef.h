//
// Created by jay on 3/4/24.
//

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
