/*
GROUP 20
VAIBHAV SINGLA - 2021A7PS2227P
JAY GOYAL - 2021A7PS2418P
SANJEEV MALLICK - 2021A7PS2217P
TRAYAMBAK SHRIVASTAVA - 2021A7PS1629P
PRANAV TANNA - 2021A7PS2685P
ARYAN BANSAL - 2021A7PS2776P
*/

#ifndef PARSER_H
#define PARSER_H

#include <stdlib.h>

#include "grammar.h"
#include "parserDef.h"

pt_t createParseTable(gram_t *gram, set_t **first_sets, set_t **follow_sets);
void clear_parse_table(pt_t pt);

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
