#include "parser.h"

pt_t create_parse_table(gram_t *gram, set_t **first_sets, set_t **follow_sets) {
    pt_t pt;
    pt.table = (prod_t ***)calloc(NUM_NONTERMINALS, sizeof(prod_t **));
    prod_t *synch = create_production();

    for (int i = 0; i < NUM_NONTERMINALS; i++) {
        // include epsilon and $ in the table
        pt.table[i] = (prod_t **)calloc(NUM_TERMINALS + 2, sizeof(prod_t *));
        for (int j = 0; j < NUM_TERMINALS + 2; j++) {
            pt.table[i][j] = NULL;
            if (follow_sets[i]->term[j] == 1) {
                pt.table[i][j] = synch;
            }
        }
    }

    for (int i = 0; i < NUM_NONTERMINALS; i++) {
        int num_prod = gram->nonterminals[i]->num_prod;
        for (int k = 0; k < num_prod; k++) {
            // each terminal in First(alpha)
            int num_right = gram->nonterminals[i]->productions[k]->num_right;
            bool flag = 0;
            for (int l = 0; l < num_right; l++) {
                int right = gram->nonterminals[i]->productions[k]->right[l];
                if (right == -1) {
                    for (int m = 1; m <= NUM_TERMINALS + 1; m++) {
                        if (follow_sets[i]->term[m] == 1) {
                            pt.table[i][m] =
                                gram->nonterminals[i]->productions[k];
                        }
                    }
                    flag = 1;
                    // break;
                } else if (right < NUM_TERMINALS) {
                    pt.table[i][right + 1] =
                        gram->nonterminals[i]->productions[k];
                    flag = 1;
                    break;
                } else if (right >= NUM_TERMINALS) {
                    for (int j = 1; j <= NUM_TERMINALS; j++) {
                        if (first_sets[right - NUM_TERMINALS]->term[j] == 1) {
                            pt.table[i][j] =
                                gram->nonterminals[i]->productions[k];
                        }
                    }
                    if (first_sets[right - NUM_TERMINALS]->term[0] == 0) {
                        flag = 1;
                        break;
                    }
                }
            }
            // epsilon in first set
            if (!flag) {
                for (int l = 1; l <= NUM_TERMINALS + 1; l++) {
                    if (follow_sets[i]->term[l] == 1) {
                        pt.table[i][l] =
                            gram->nonterminals[i]->productions[num_prod - 1];
                    }
                }
            }
        }
    }

    // for (int i = 0; i < NUM_NONTERMINALS; i++) {
    //     for (int j = 1; j <= NUM_TERMINALS + 1; j++) {
    //         if (pt.table[i][j] != NULL) {
    //             printf("-------------NONTERMINAL %s-------------\n",
    //                     non_terminals[i]);
    //             if (j <= NUM_TERMINALS)
    //                 printf("TERMINAL %s \n", token_str[j - 1]);
    //             else
    //                 printf("TERMINAL $ \n");
    //             int num_right = pt.table[i][j]->num_right;
    //             printf("%s -> ", non_terminals[i]);
    //             if (num_right == 0) printf("SYNCH");
    //             for (int l = 0; l < num_right; l++) {
    //                 int right = pt.table[i][j]->right[l];
    //                 if (right == -1)
    //                     printf("EPSILON ");
    //                 else if (right <= NUM_TERMINALS)
    //                     printf("%s ", token_str[right]);
    //                 else
    //                     printf("%s ", non_terminals[right - NUM_TERMINALS]);
    //             }
    //             printf("\n");
    //             printf("\n");
    //         }
    //     }
    // }

    // printf("%d\n",
    // gram->nonterminals[RELATIONALOP-NUM_TERMINALS]->productions[3]->num_right);
    return pt;
}

/* STACK */
stack_t *create_stack() {
    stack_t *stack = (stack_t *)malloc(sizeof(stack_t));
    stack->size = 0;
    return stack;
}

void push(stack_t *stack, tnode_t *node) {
    stack->size++;
    stack->nodes =
        (tnode_t **)realloc(stack->nodes, stack->size * sizeof(tnode_t *));
    stack->nodes[stack->size - 1] = node;
}

void pop(stack_t *stack) {
    if (stack->size == 0) {
        printf("Stack underflow\n");
        return;
    }
    stack->size--;
    stack->nodes =
        (tnode_t **)realloc(stack->nodes, stack->size * sizeof(tnode_t *));
}

tnode_t *top(stack_t *stack) {
    if (stack->size == 0) {
        printf("Stack underflow\n");
        return NULL;
    }
    return stack->nodes[stack->size - 1];
}

bool is_empty(stack_t *stack) { return stack->size == 0; }

void clear_stack(stack_t *stack) {
    free(stack->nodes);
    free(stack);
}

/* TREE */
tree_t *create_tree() {
    tree_t *tree = (tree_t *)malloc(sizeof(tree_t));
    tree->root = NULL;
    return tree;
}

tnode_t *create_tnode(int val) {
    tnode_t *node = (tnode_t *)malloc(sizeof(tnode_t));
    node->val = val;
    node->num_children = 0;
    node->children = NULL;
    return node;
}

void insert_tnode(tnode_t *parent, tnode_t *child) {
    parent->num_children++;
    parent->children = (tnode_t **)realloc(
        parent->children, parent->num_children * sizeof(tnode_t *));
    parent->children[parent->num_children - 1] = child;
}

void clear_node(tnode_t *node) {
    for (int i = 0; i < node->num_children; i++) {
        clear_node(node->children[i]);
    }
    free(node->children);
    free(node);
}

void clear_tree(tree_t *tree) {
    for (int i = 0; i < tree->root->num_children; i++) {
        clear_node(tree->root->children[i]);
    }
    free(tree);
}

tree_t *create_parse_tree(pt_t pt, char *src_filename, ht_t *symbol_table,
                          char *lexer_op_file) {
    tree_t *parse_tree = create_tree();
    stack_t *stack = create_stack();
    tnode_t *node = create_tnode(BOTTOMMARKER);
    push(stack, node);
    node = create_tnode(PROGRAM);
    push(stack, node);
    parse_tree->root = node;

    tokeninfo_t ret_token =
        get_next_token(src_filename, symbol_table, lexer_op_file);
    while (ret_token.token_type != -1) {
        if (ret_token.token_type == -2) {
            ret_token =
                get_next_token(src_filename, symbol_table, lexer_op_file);
        }

        if (stack->size == 1) {
            break;
        }
        // printf("Top: %d, Size: %d\n", top(stack)->val, stack->size);
        tnode_t *curr_node = top(stack);
        if (curr_node->val >= NUM_TERMINALS) {
            // error -> skip
            if (pt.table[curr_node->val - NUM_TERMINALS]
                        [ret_token.token_type + 1] == NULL) {
                printf("Line No. %d: SYNTAX ERROR! at token type %s\n",
                       ret_token.line_no, token_str[ret_token.token_type]);
                ret_token =
                    get_next_token(src_filename, symbol_table, lexer_op_file);
            }
            // synch -> error recovery
            else if (pt.table[curr_node->val - NUM_TERMINALS]
                             [ret_token.token_type + 1]
                                 ->num_right == 0) {
                pop(stack);
                pop(stack);
                printf("Line No. %d: SYNTAX ERROR! at token type %s\n",
                       ret_token.line_no, token_str[ret_token.token_type]);
            } else {
                pop(stack);
                printf("Pop %s\n",
                       non_terminals[curr_node->val - NUM_TERMINALS]);
                int num_right = pt.table[curr_node->val - NUM_TERMINALS]
                                        [ret_token.token_type + 1]
                                            ->num_right;
                if (num_right == 1 && pt.table[curr_node->val - NUM_TERMINALS]
                                              [ret_token.token_type + 1]
                                                  ->right[0] == -1) {
                    node = create_tnode(pt.table[curr_node->val - NUM_TERMINALS]
                                                [ret_token.token_type + 1]
                                                    ->right[0]);
                    insert_tnode(curr_node, node);
                    printf("Push EPSILON\n");
                    continue;
                }
                for (int j = 0; j < num_right; j++) {
                    node = create_tnode(pt.table[curr_node->val - NUM_TERMINALS]
                                                [ret_token.token_type + 1]
                                                    ->right[j]);
                    insert_tnode(curr_node, node);
                }
                for (int j = num_right - 1; j >= 0; j--) {
                    push(stack, curr_node->children[j]);
                }
            }
        }
        // top is a terminal
        else {
            pop(stack);
            if (curr_node->val == ret_token.token_type) {
                printf("Pop %s\n", token_str[ret_token.token_type]);
                ret_token =
                    get_next_token(src_filename, symbol_table, lexer_op_file);
            } else {
                printf("Line No. %d: SYNTAX ERROR! Token: %s\n", ret_token.line_no, token_str[ret_token.token_type]);
            }
        }
    }
    if (ret_token.token_type >= 0)
        printf("%s\n", token_str[ret_token.token_type]);
    ret_token = get_next_token(src_filename, symbol_table, lexer_op_file);
    if (ret_token.token_type == -1) {
        printf("Parse Successful\n");
    } else {
        if (ret_token.token_type >= 0)
            printf("%s\n", token_str[ret_token.token_type]);
        printf("Lexical Error, Parser could not be run\n");
        exit(-1);
    }

    return parse_tree;
}
