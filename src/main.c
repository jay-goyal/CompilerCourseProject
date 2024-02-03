#include <stdio.h>

#include "hash_table/hash_table.h"
#include "linked_list/LinkedList.h"

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
    return 0;
}
