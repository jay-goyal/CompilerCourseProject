#include <stdio.h>

#include "hash_table/hash_table.h"
#include "lexical_analyzer/transition_diagram.h"

int main(int argc, char* argv[]) {
    printf("RUNNING\n");

    char* str1 = "STRING1";
    ht_t* ht = create_hash_table();
    insert_entry(ht, str1);
    node_t* node = check_node_exists(ht, str1);
    printf("%s\n", node->key);

    state_t** td = create_transition_diagram();
    clear_transition_diagram(td);
    return 0;
}
