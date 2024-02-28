#ifndef PARSER_H
#define PARSER_H

#include "grammar.h"
#include <stdlib.h>

typedef struct ParseTable {
    prod_t ***table;
} pt_t;

typedef struct Stack {
    int size;
    int *data;
} stack_t;

typedef struct Treetnode tnode_t;
struct Treetnode {
    int val;
    int num_children;
    tnode_t **children;
};

typedef struct Tree {
    tnode_t *root;
} tree_t;

pt_t create_parse_table(gram_t *gram, set_t **first_sets, set_t **follow_sets);

stack_t *create_stack();
void push(stack_t *stack, int val);
void pop(stack_t *stack);
int top(stack_t *stack);
bool is_empty(stack_t *stack);
void clear_stack(stack_t *stack);

tree_t *create_tree();
void insert_tree(tree_t *tree, tnode_t *node);
tnode_t *create_tnode(int val);
void insert_tnode(tnode_t *parent, tnode_t *child);
void clear_tnode(tnode_t *node);
void clear_tree(tree_t *tree);

#endif