/*
GROUP 20
VAIBHAV SINGLA - 2021A7PS2227P
JAY GOYAL - 2021A7PS2418P
SANJEEV MALLICK - 2021A7PS2217P
TRAYAMBAK SHRIVASTAVA - 2021A7PS1629P
PRANAV TANNA - 2021A7PS2685P
ARYAN BANSAL - 2021A7PS2776P
*/

#include "parser.h"

#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

#include "helper.h"

// create parse table
pt_t createParseTable(gram_t *gram, set_t **first_sets, set_t **follow_sets) {
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
        pt.table[i][TK_SEM + 1] = synch;
        pt.table[i][TK_END + 1] = synch;
        pt.table[i][TK_ENDRECORD + 1] = synch;
        pt.table[i][TK_ENDUNION + 1] = synch;
        pt.table[i][TK_ENDIF + 1] = synch;
        pt.table[i][TK_ENDWHILE + 1] = synch;
        pt.table[i][TK_ELSE + 1] = synch;
        pt.table[i][TK_CL + 1] = synch;
        pt.table[i][TK_SQR + 1] = synch;
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

tnode_t *create_tnode(int val, tokeninfo_t tokeninfo) {
    tnode_t *node = (tnode_t *)malloc(sizeof(tnode_t));
    node->val = val;
    node->tokeninfo = tokeninfo;
    node->num_children = 0;
    node->children = NULL;
    node->parent = NULL;
    return node;
}

void insert_tnode(tnode_t *parent, tnode_t *child) {
    parent->num_children++;
    parent->children = (tnode_t **)realloc(
        parent->children, parent->num_children * sizeof(tnode_t *));
    parent->children[parent->num_children - 1] = child;
    child->parent = parent;
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

// parse the input source code
tree_t *parseInputSourceCode(pt_t pt, char *src_filename, ht_t *symbol_table) {
    tokeninfo_t ret_token = getNextToken(src_filename, symbol_table, 1);
    bool lerr_flag = false;
    bool perr_flag = false;

    tree_t *parse_tree = create_tree();
    stack_t *stack = create_stack();
    tnode_t *node = create_tnode(BOTTOMMARKER, ret_token);
    push(stack, node);
    node = create_tnode(PROGRAM, ret_token);
    push(stack, node);
    parse_tree->root = node;
    int new_token = 1;
    bool err = 0;

    while (ret_token.token_type != -1 && stack->size > 1) {
        if (ret_token.token_type < -1) {
            ret_token = getNextToken(src_filename, symbol_table, 1);
            lerr_flag = true;
            err = 0;
            continue;
        }

        tnode_t *curr_node = top(stack);
        if (curr_node->val >= NUM_TERMINALS) {
            // error -> skip
            if (pt.table[curr_node->val - NUM_TERMINALS]
                        [ret_token.token_type + 1] == NULL) {
                    if(!err)
                    printf(
                        "Line No. %d\t|" ANSI_COLOR_RED
                        "  SYNTAX ERROR! Unexpected token %s encountered with "
                        "value '%s' "
                        "\n" ANSI_COLOR_RESET,
                        ret_token.line_no, token_str[ret_token.token_type],
                        ret_token.lexeme,
                        non_terminals[curr_node->val - NUM_NONTERMINALS]);
                ret_token = getNextToken(src_filename, symbol_table, 1);
                err = 0;
                perr_flag = true;
            }
            // synch -> error recovery
            else if (pt.table[curr_node->val - NUM_TERMINALS]
                             [ret_token.token_type + 1]
                                 ->num_right == 0) {
                pop(stack);
                    if(!err)
                    printf(
                        "Line No. %d\t|" ANSI_COLOR_RED
                        "  SYNTAX ERROR! Unexpected token %s encountered with "
                        "value '%s' "
                        "\n" ANSI_COLOR_RESET,
                        ret_token.line_no, token_str[ret_token.token_type],
                        ret_token.lexeme,
                        non_terminals[curr_node->val - NUM_NONTERMINALS]);
                perr_flag = true;
                err = 1;
            } else {
                pop(stack);
                int num_right = pt.table[curr_node->val - NUM_TERMINALS]
                                        [ret_token.token_type + 1]
                                            ->num_right;
                if (num_right == 1 && pt.table[curr_node->val - NUM_TERMINALS]
                                              [ret_token.token_type + 1]
                                                  ->right[0] == -1) {
                    node = create_tnode(pt.table[curr_node->val - NUM_TERMINALS]
                                                [ret_token.token_type + 1]
                                                    ->right[0],
                                        ret_token);
                    insert_tnode(curr_node, node);
                    continue;
                }
                for (int j = 0; j < num_right; j++) {
                    node = create_tnode(pt.table[curr_node->val - NUM_TERMINALS]
                                                [ret_token.token_type + 1]
                                                    ->right[j],
                                        ret_token);
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
                ret_token = getNextToken(src_filename, symbol_table, 1);
                err = 0;
            } else {
                    if(!err)
                    printf(
                        "Line No. %d\t|" ANSI_COLOR_RED
                        "  SYNTAX ERROR! The token %s for lexeme '%s' does not "
                        "match with the expected token %s\n" ANSI_COLOR_RESET,
                        ret_token.line_no, token_str[ret_token.token_type],
                        ret_token.lexeme, token_str[curr_node->val]);
                err = 1;
                perr_flag = true;
            }
        }
    }

    // tokens finished
    if (ret_token.token_type == -1) {
        if (!perr_flag && !lerr_flag)
            printf(ANSI_COLOR_GREEN ANSI_COLOR_BOLD
                   "\n\nParse Successful\n" ANSI_COLOR_RESET);
        else
            printf(ANSI_COLOR_RED ANSI_COLOR_BOLD
                   "\n\nParse Unsuccessful\n" ANSI_COLOR_RESET);
        if (lerr_flag)
            printf(ANSI_COLOR_RED ANSI_COLOR_BOLD
                   "Lexical Errors Reported\n" ANSI_COLOR_RESET);
        if (perr_flag)
            printf(ANSI_COLOR_RED ANSI_COLOR_BOLD
                   "Syntax Errors Reported\n" ANSI_COLOR_RESET);

    }
    // tokens remaining after main
    else {
        if (ret_token.token_type >= 0)
            printf("Line No. %d\t|" ANSI_COLOR_RED
                   "  SYNTAX ERROR! No Token Expected"
                   "\n" ANSI_COLOR_RESET,
                   ret_token.line_no);
        printf(ANSI_COLOR_RED ANSI_COLOR_BOLD
               "\n\nSyntax Error, Tokens after _main function provided "
               "run\n\n" ANSI_COLOR_RESET);
    }

    return parse_tree;
}

// print the node
void print_node(tnode_t *node, int fptr) {
    int num_children = node->num_children;
    char buf[1500];
    int len;

    // leaf node
    if (num_children == 0) {
        // epsilon
        if (node->val == -1) {
            len = sprintf(buf,
                          "----                 %-4d   EPSILON          ----   "
                          "       %-30s yes      ----\n",
                          node->tokeninfo.line_no,
                          non_terminals[node->parent->val - NUM_TERMINALS]);
            write(fptr, buf, len);
        } else {
            len = sprintf(buf, "%-20s %-4d   %-16s", node->tokeninfo.lexeme,
                          node->tokeninfo.line_no,
                          token_str[node->tokeninfo.token_type]);
            write(fptr, buf, len);
            if (node->tokeninfo.token_type == TK_NUM)
                len = sprintf(buf, " %-7ld", node->tokeninfo.info.num_val);
            else if (node->tokeninfo.token_type == TK_NUM)
                len = sprintf(buf, " %-7f", node->tokeninfo.info.rnum_val);
            else
                len = sprintf(buf, " ----   ");
            write(fptr, buf, len);
            len = sprintf(buf, "       %-30s yes      ----\n",
                          non_terminals[node->parent->val - NUM_TERMINALS]);
            write(fptr, buf, len);
        }
        return;
    }

    // print the first child
    print_node(node->children[0], fptr);

    // print the current node
    len = sprintf(buf, "----                 %-4d   ----             ----   ",
                  node->tokeninfo.line_no);
    write(fptr, buf, len);
    if (node->val == PROGRAM) {
        len = sprintf(buf, "       ROOT                          ");
        write(fptr, buf, len);
    } else {
        len = sprintf(buf, "       %-30s",
                      non_terminals[node->val - NUM_TERMINALS]);
        write(fptr, buf, len);
    }
    len = sprintf(buf, " no       %s\n",
                  non_terminals[node->val - NUM_TERMINALS]);
    write(fptr, buf, len);
    

    // print the remaining children
    for (int i = 1; i < num_children; i++) {
        print_node(node->children[i], fptr);
    }
}


// print the parse tree to the file
void printParseTree(tree_t *tree, char *parser_op_file) {
    int fptr = open(parser_op_file, O_RDWR | O_CREAT, 0666);
    char buf[1500];
    int len =
        sprintf(buf,
                "Lexeme               LineNo TokenName        ValueIfNumber "
                "Parent                         isLeaf   Node\n");
    write(fptr, buf, len);
    print_node(tree->root, fptr);
    close(fptr);
}
