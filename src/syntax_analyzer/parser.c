#include "parser.h"

pt_t create_parse_table(gram_t *gram, set_t **first_sets, set_t **follow_sets) {
    pt_t pt;
    pt.table = (prod_t ***) calloc(NUM_NONTERMINALS, sizeof(prod_t **));
    prod_t *synch = create_production();

    for(int i=0; i<NUM_NONTERMINALS; i++) {
        // include epsilon and $ in the table
        pt.table[i] = (prod_t **) calloc(NUM_TERMINALS+2, sizeof(prod_t *));
        for(int j=0; j<NUM_TERMINALS+2; j++) {
            pt.table[i][j] = NULL;
            if(follow_sets[i]->term[j] == 1) {
                pt.table[i][j] = synch;
            }
        }
    }

    for(int i=0; i<NUM_NONTERMINALS; i++) {
        int num_prod = gram->nonterminals[i]->num_prod;
        for(int k=0; k<num_prod; k++) {
            // each terminal in First(alpha)
            int num_right = gram->nonterminals[i]->productions[k]->num_right;
            bool flag = 0;
            for(int l=0; l<num_right; l++) {
                int right = gram->nonterminals[i]->productions[k]->right[l];
                if(right == -1) {
                    for(int m=1; m<=NUM_TERMINALS+1; m++) {
                        if(follow_sets[i]->term[m] == 1) {
                            pt.table[i][m] = gram->nonterminals[i]->productions[k];
                        }
                    }
                    flag = 1;
                    // break;
                }
                else if(right < NUM_TERMINALS) {
                    pt.table[i][right+1] = gram->nonterminals[i]->productions[k];
                    flag = 1;
                    break;
                }
                else if(right >= NUM_TERMINALS) {
                    for(int j=1; j<=NUM_TERMINALS; j++) {
                        if(first_sets[right-NUM_TERMINALS]->term[j] == 1) {
                            pt.table[i][j] = gram->nonterminals[i]->productions[k];
                        }
                    }
                    if(first_sets[right-NUM_TERMINALS]->term[0] == 0) {
                        flag = 1;
                        break;
                    }
                }
            }
            // epsilon in first set
            if(!flag) {
                for(int l=1; l<=NUM_TERMINALS+1; l++) {
                    if(follow_sets[i]->term[l] == 1) {
                        pt.table[i][l] = gram->nonterminals[i]->productions[num_prod-1];
                    }
                }
            }
        }
    }

    for(int i=0; i<NUM_NONTERMINALS; i++) {
        for(int j=1; j<=NUM_TERMINALS+1; j++) {
            if(pt.table[i][j] != NULL) {
                printf("-------------NONTERMINAL %s-------------\n", non_terminals[i]);
                if(j <= NUM_TERMINALS)
                    printf("TERMINAL %s \n", token_str[j-1]);
                else
                    printf("TERMINAL $ \n");
                    int num_right = pt.table[i][j]->num_right;
                    printf("%s -> ", non_terminals[i]);
                    if(num_right == 0)
                        printf("SYNCH");
                    for(int l=0; l<num_right; l++) {
                        int right = pt.table[i][j]->right[l];
                        if(right == -1)
                            printf("EPSILON ");
                        else if(right <= NUM_TERMINALS)
                            printf("%s ", token_str[right]);
                        else
                            printf("%s ", non_terminals[right-NUM_TERMINALS]);
                    }
                    printf("\n");
                printf("\n");
            }
        }
    }
    return pt;
}

/* STACK */
stack_t *create_stack() {
    stack_t *stack = (stack_t *) malloc(sizeof(stack_t));
    stack->size = 0;
    return stack;
}

void push(stack_t *stack, int val) {
    stack->size++;
    stack->data = (int *) realloc(stack->data, stack->size * sizeof(int));
    stack->data[stack->size-1] = val;
}

void pop(stack_t *stack) {
    if(stack->size == 0) {
        printf("Stack underflow\n");
        return;
    }
    stack->size--;
    stack->data = (int *) realloc(stack->data, stack->size * sizeof(int));
}

int top(stack_t *stack) {
    if(stack->size == 0) {
        printf("Stack underflow\n");
        return -1;
    }
    return stack->data[stack->size-1];
}

bool is_empty(stack_t *stack) {
    return stack->size == 0;
}

void clear_stack(stack_t *stack) {
    free(stack->data);
    free(stack);
}

/* TREE */
tree_t *create_tree() {
    tree_t *tree = (tree_t *) malloc(sizeof(tree_t));
    tree->root = NULL;
    return tree;
}

void insert_tree(tree_t *tree, tnode_t *node) {
    tree->root = node;
}

tnode_t *create_node(int val) {
    tnode_t *node = (tnode_t *) malloc(sizeof(tnode_t));
    node->val = val;
    node->num_children = 0;
    node->children = NULL;
    return node;
}

void insert_node(tnode_t *parent, tnode_t *child) {
    parent->num_children++;
    parent->children = (tnode_t **) realloc(parent->children, parent->num_children * sizeof(tnode_t *));
    parent->children[parent->num_children-1] = child;
}

void clear_node(tnode_t *node) {
    for(int i=0; i<node->num_children; i++) {
        clear_node(node->children[i]);
    }
    free(node->children);
    free(node);
}

void clear_tree(tree_t *tree) {
    for(int i=0; i<tree->root->num_children; i++) {
        clear_node(tree->root->children[i]);
    }
    free(tree);
}