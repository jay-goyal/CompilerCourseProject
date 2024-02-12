#include <stdio.h>

#include "hash_table/hash_table.h"
#include "linked_list/LinkedList.h"
#include "lexical_analyzer/transition_diagram.h"

int main(int argc, char* argv[]) {
    printf("RUNNING\n");
    ht_t* hashtable = create_hash_table();
    char* s1 = "STRING1";
    char* s2 = "STRING2";
    char* s3 = "STRING3";
    char* s4 = "STRING4";
    char* s5 = "STRING5";
    char* s6 = "STRING6";
    insert_key_val(hashtable, &s1, 1);
    insert_key_val(hashtable, &s2, 2);
    insert_key_val(hashtable, &s3, 3);
    insert_key_val(hashtable, &s4, 4);
    insert_key_val(hashtable, &s5, 5);
    insert_key_val(hashtable, &s6, 6);
    node_t** entries = hashtable->entries;
    for (int i = 0; i < TABLE_SIZE; i++) {
        node_t* node = entries[i];
        if (node != NULL) {
            printf("Slot [%d]: ", i);
        }
        while (node != NULL) {
            printf("{key: %s, value: %d}, ", *node->key, node->val);
            node = node->next;
        }
        if (entries[i] != NULL) {
            printf("\n");
        }
    }
    
    State* td = create_transition_diagram();
    for(int i=0; i<64; i++) {
        printf("State %d: ", i);
        printf("Transitions: %d ", td[i]->transitions.size);
        printf("Retract: %d ", td[i]->retract);
        printf("Exit: %d ", td[i]->exit);
        printf("Line Increment: %d ", td[i]->line_increment);
        printf("Is Final: %d\n", td[i]->is_final);
    }

    for(int i=0; i<td[0]->transitions.size; i++) {
        printf("Symbol: %s, Next State: %d\n", td[0]->transitions.symbol[i], td[0]->transitions.next_state[i]);
    }

    return 0;
}
