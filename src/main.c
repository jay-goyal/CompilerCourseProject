#include <stdio.h>
#include <stdlib.h>

#include "hash_table/hash_table.h"
#include "lexical_analyzer/lexer.h"
#include "lexical_analyzer/lexer_types.h"
#include "syntax_analyzer/grammar.h"
#include "syntax_analyzer/parser.h"

// void populate_symbol_table(ht_t* st) {
//     stentry_t* entry = (stentry_t*)calloc(1, sizeof(stentry_t));
//     char* lexeme = (char*)calloc(5, sizeof(char));
//     lexeme = "with";
//     entry->lexeme = lexeme;
//     entry->token_type = TK_WITH;
//     insert_entry(st, entry);

//     entry = (stentry_t*)calloc(1, sizeof(stentry_t));
//     lexeme = (char*)calloc(11, sizeof(char));
//     lexeme = "parameters";
//     entry->lexeme = lexeme;
//     entry->token_type = TK_PARAMETERS;
//     insert_entry(st, entry);

//     entry = (stentry_t*)calloc(1, sizeof(stentry_t));
//     lexeme = (char*)calloc(4, sizeof(char));
//     lexeme = "end";
//     entry->lexeme = lexeme;
//     entry->token_type = TK_END;
//     insert_entry(st, entry);

//     entry = (stentry_t*)calloc(1, sizeof(stentry_t));
//     lexeme = (char*)calloc(6, sizeof(char));
//     lexeme = "while";
//     entry->lexeme = lexeme;
//     entry->token_type = TK_WHILE;
//     insert_entry(st, entry);

//     entry = (stentry_t*)calloc(1, sizeof(stentry_t));
//     lexeme = (char*)calloc(6, sizeof(char));
//     lexeme = "union";
//     entry->lexeme = lexeme;
//     entry->token_type = TK_UNION;
//     insert_entry(st, entry);

//     entry = (stentry_t*)calloc(1, sizeof(stentry_t));
//     lexeme = (char*)calloc(9, sizeof(char));
//     lexeme = "endunion";
//     entry->lexeme = lexeme;
//     entry->token_type = TK_ENDUNION;
//     insert_entry(st, entry);

//     entry = (stentry_t*)calloc(1, sizeof(stentry_t));
//     lexeme = (char*)calloc(11, sizeof(char));
//     lexeme = "definetype";
//     entry->lexeme = lexeme;
//     entry->token_type = TK_DEFINETYPE;
//     insert_entry(st, entry);

//     entry = (stentry_t*)calloc(1, sizeof(stentry_t));
//     lexeme = (char*)calloc(3, sizeof(char));
//     lexeme = "as";
//     entry->lexeme = lexeme;
//     entry->token_type = TK_AS;
//     insert_entry(st, entry);

//     entry = (stentry_t*)calloc(1, sizeof(stentry_t));
//     lexeme = (char*)calloc(5, sizeof(char));
//     lexeme = "type";
//     entry->lexeme = lexeme;
//     entry->token_type = TK_TYPE;
//     insert_entry(st, entry);

//     entry = (stentry_t*)calloc(1, sizeof(stentry_t));
//     lexeme = (char*)calloc(5, sizeof(char));
//     lexeme = "main";
//     entry->lexeme = lexeme;
//     entry->token_type = TK_MAIN;
//     insert_entry(st, entry);

//     entry = (stentry_t*)calloc(1, sizeof(stentry_t));
//     lexeme = (char*)calloc(7, sizeof(char));
//     lexeme = "global";
//     entry->lexeme = lexeme;
//     entry->token_type = TK_GLOBAL;
//     insert_entry(st, entry);

//     entry = (stentry_t*)calloc(1, sizeof(stentry_t));
//     lexeme = (char*)calloc(10, sizeof(char));
//     lexeme = "parameter";
//     entry->lexeme = lexeme;
//     entry->token_type = TK_PARAMETER;
//     insert_entry(st, entry);

//     entry = (stentry_t*)calloc(1, sizeof(stentry_t));
//     lexeme = (char*)calloc(5, sizeof(char));
//     lexeme = "list";
//     entry->lexeme = lexeme;
//     entry->token_type = TK_LIST;
//     insert_entry(st, entry);

//     entry = (stentry_t*)calloc(1, sizeof(stentry_t));
//     lexeme = (char*)calloc(6, sizeof(char));
//     lexeme = "input";
//     entry->lexeme = lexeme;
//     entry->token_type = TK_INPUT;
//     insert_entry(st, entry);

//     entry = (stentry_t*)calloc(1, sizeof(stentry_t));
//     lexeme = (char*)calloc(7, sizeof(char));
//     lexeme = "output";
//     entry->lexeme = lexeme;
//     entry->token_type = TK_OUTPUT;
//     insert_entry(st, entry);

//     entry = (stentry_t*)calloc(1, sizeof(stentry_t));
//     lexeme = (char*)calloc(4, sizeof(char));
//     lexeme = "int";
//     entry->lexeme = lexeme;
//     entry->token_type = TK_INT;
//     insert_entry(st, entry);

//     entry = (stentry_t*)calloc(1, sizeof(stentry_t));
//     lexeme = (char*)calloc(5, sizeof(char));
//     lexeme = "real";
//     entry->lexeme = lexeme;
//     entry->token_type = TK_REAL;
//     insert_entry(st, entry);

//     entry = (stentry_t*)calloc(1, sizeof(stentry_t));
//     lexeme = (char*)calloc(9, sizeof(char));
//     lexeme = "endwhile";
//     entry->lexeme = lexeme;
//     entry->token_type = TK_ENDWHILE;
//     insert_entry(st, entry);

//     entry = (stentry_t*)calloc(1, sizeof(stentry_t));
//     lexeme = (char*)calloc(3, sizeof(char));
//     lexeme = "if";
//     entry->lexeme = lexeme;
//     entry->token_type = TK_IF;
//     insert_entry(st, entry);

//     entry = (stentry_t*)calloc(1, sizeof(stentry_t));
//     lexeme = (char*)calloc(5, sizeof(char));
//     lexeme = "then";
//     entry->lexeme = lexeme;
//     entry->token_type = TK_THEN;
//     insert_entry(st, entry);

//     entry = (stentry_t*)calloc(1, sizeof(stentry_t));
//     lexeme = (char*)calloc(6, sizeof(char));
//     lexeme = "endif";
//     entry->lexeme = lexeme;
//     entry->token_type = TK_ENDIF;
//     insert_entry(st, entry);

//     entry = (stentry_t*)calloc(1, sizeof(stentry_t));
//     lexeme = (char*)calloc(5, sizeof(char));
//     lexeme = "read";
//     entry->lexeme = lexeme;
//     entry->token_type = TK_READ;
//     insert_entry(st, entry);

//     entry = (stentry_t*)calloc(1, sizeof(stentry_t));
//     lexeme = (char*)calloc(6, sizeof(char));
//     lexeme = "write";
//     entry->lexeme = lexeme;
//     entry->token_type = TK_WRITE;
//     insert_entry(st, entry);

//     entry = (stentry_t*)calloc(1, sizeof(stentry_t));
//     lexeme = (char*)calloc(7, sizeof(char));
//     lexeme = "return";
//     entry->lexeme = lexeme;
//     entry->token_type = TK_RETURN;
//     insert_entry(st, entry);

//     entry = (stentry_t*)calloc(1, sizeof(stentry_t));
//     lexeme = (char*)calloc(5, sizeof(char));
//     lexeme = "call";
//     entry->lexeme = lexeme;
//     entry->token_type = TK_CALL;
//     insert_entry(st, entry);

//     entry = (stentry_t*)calloc(1, sizeof(stentry_t));
//     lexeme = (char*)calloc(7, sizeof(char));
//     lexeme = "record";
//     entry->lexeme = lexeme;
//     entry->token_type = TK_RECORD;
//     insert_entry(st, entry);

//     entry = (stentry_t*)calloc(1, sizeof(stentry_t));
//     lexeme = (char*)calloc(10, sizeof(char));
//     lexeme = "endrecord";
//     entry->lexeme = lexeme;
//     entry->token_type = TK_ENDRECORD;
//     insert_entry(st, entry);

//     entry = (stentry_t*)calloc(1, sizeof(stentry_t));
//     lexeme = (char*)calloc(5, sizeof(char));
//     lexeme = "else";
//     entry->lexeme = lexeme;
//     entry->token_type = TK_ELSE;
//     insert_entry(st, entry);
// }
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
void print_tree_nodes(tnode_t *node) {
    if (node == NULL)
        return;

    printf("%d ", node->val); // Print the current node's value

    // Recursively print the children nodes
    for (int i = 0; i < node->num_children; i++) {
        print_tree_nodes(node->children[i]);
    }
}

void test_tree_functions() {
    printf("Testing tree functions...\n");

    // Test create_tree() and insert_tree()
    printf("Creating tree...\n");
    tree_t *tree = create_tree();
    tnode_t *node1 = create_node(1);
    insert_tree(tree, node1);
    printf("Tree created and root node inserted.\n");

    // Test create_node() and insert_node()
    printf("Creating and inserting child nodes...\n");
    tnode_t *node2 = create_node(3);
    insert_node(node1, node2);
    tnode_t *node3 = create_node(2);
    insert_node(node1, node3);
    printf("Child nodes created and inserted.\n");

    // Add 10 more nodes
    for (int i = 0; i < 10; i++) {
        tnode_t *new_node = create_node(i + 4); // Values start from 4
        insert_node(node2, new_node); // Inserting under node2
    }
    printf("10 more nodes added.\n");

    // Print the nodes of the tree
    printf("Printing tree nodes: ");
    print_tree_nodes(tree->root);
    printf("\n");

    // Test clear_tree() and clear_node()
    printf("Clearing tree...\n");
    clear_tree(tree);
    printf("Tree cleared.\n");

    printf("Tree functions test passed!\n");
}



int main(int argc, char* argv[]) {
    printf("RUNNING\n");
    test_tree_functions();
    // ht_t* symbol_table = create_hash_table();
    // populate_symbol_table(symbol_table);

    // gram_t* gram = create_grammar();

    // set_t **first_sets = compute_first_sets(gram);
    
    // set_t **follow_sets = compute_follow_sets(gram, first_sets);
    
    // pt_t pt = create_parse_table(gram, first_sets, follow_sets);

    // tokeninfo_t ret_token = get_next_token("test.txt", symbol_table);
    // while (ret_token.token_type != -2) {
    //     switch (ret_token.token_type) {
    //         case TK_NUM:
    //             printf("%ld -> %s\n", ret_token.info.num_val,
    //                    token_str[TK_NUM]);
    //             break;
    //         case TK_RNUM:
    //             printf("%f -> %s\n", ret_token.info.rnum_val,
    //                    token_str[TK_RNUM]);
    //             break;
    //         case TK_FUNID:
    //         case TK_FIELDID:
    //         case TK_ID:
    //         case TK_RUID:
    //             printf("%s -> %s\n", ret_token.info.stentry->lexeme,
    //                    token_str[ret_token.token_type]);
    //             break;
    //         default:
    //             printf("%s\n", token_str[ret_token.token_type]);
    //             break;
    //     }
    //     ret_token = get_next_token("test.txt", symbol_table);
    // }
    
    // clear_grammar(gram);
    // clear_sets(first_sets);
    // clear_sets(follow_sets);
    // printf("%d")

    return 0;
}
