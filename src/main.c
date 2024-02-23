#include <stdio.h>

#include "hash_table/hash_table.h"
#include "lexical_analyzer/lexer_types.h"
#include "lexical_analyzer/transition_diagram.h"

int main(int argc, char* argv[]) {
    printf("RUNNING\n");

    char* str1 = "STRING1";
    ht_t* ht = create_hash_table();
    stentry_t st = {str1, 0};
    insert_entry(ht, &st);
    node_t* node = check_node_exists(ht, &st);
    printf("%s\n", node->key->lexeme);

    state_t** td = create_transition_diagram();
    clear_transition_diagram(td);
    return 0;
}
