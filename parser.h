#ifndef PARSER_H
#define PARSER_H

#include <stdlib.h>

#include "grammar.h"
#include "parserDef.h"

pt_t createParseTable(gram_t *gram, set_t **first_sets, set_t **follow_sets);

stack_t *create_stack();
void push(stack_t *stack, tnode_t *node);
void pop(stack_t *stack);
tnode_t *top(stack_t *stack);
bool is_empty(stack_t *stack);
void clear_stack(stack_t *stack);

tree_t *create_tree();
tnode_t *create_tnode(int val, tokeninfo_t tokeninfo);
void insert_tnode(tnode_t *parent, tnode_t *child);
void clear_tnode(tnode_t *node);
void clear_tree(tree_t *tree);
tree_t *parseInputSourceCode(pt_t pt, char *src_filename, ht_t *symbol_table);
void print_node(tnode_t *node, int fptr);
void printParseTree(tree_t *tree, char *parser_op_file);
#endif
