/*
GROUP 20
VAIBHAV SINGLA - 2021A7PS2227P
JAY GOYAL - 2021A7PS2418P
SANJEEV MALLICK - 2021A7PS2217P
TRAYAMBAK SHRIVASTAVA - 2021A7PS1629P
PRANAV TANNA - 2021A7PS2685P
ARYAN BANSAL - 2021A7PS2776P
*/

#include "hash_table.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// check if the node exists in the hash table
node_t* check_node_exists(ht_t* hashtable, stentry_t* key) {
    unsigned int hash_value = hash(key->lexeme);
    node_t** entries = hashtable->entries;
    node_t* curr_node = entries[hash_value];
    while (curr_node != NULL) {
        if (strcmp(curr_node->key->lexeme, key->lexeme) == 0) return curr_node;
        curr_node = curr_node->next;
    }
    return NULL;
}

// compute hash value for the key
unsigned int hash(char* key) {
    unsigned int value = 0;
    unsigned int len = strlen(key);

    for (unsigned int i = 0; i < len; i++) {
        value = (value * 57 + key[i]) % TABLE_SIZE;
    }

    return value;
}

// create an empty hash table
ht_t* create_hash_table() {
    ht_t* hashtable = (ht_t*)calloc(1, sizeof(ht_t));
    if (hashtable == NULL) {
        printf("Cannot allocate the Hash Table");
        exit(-1);
    }

    hashtable->entries = (node_t**)calloc(TABLE_SIZE, sizeof(node_t*));

    return hashtable;
}

// insert a new node in the hash table if key does not exist
stentry_t* insert_entry(ht_t* hashtable, stentry_t* key) {
    unsigned int hash_value = hash(key->lexeme);
    node_t** entries = hashtable->entries;
    node_t* node = check_node_exists(hashtable, key);

    // if node existed, don't insert and return existing node
    if (node != NULL) {
        return node->key;
    }

    // if head did not exist, create a new linked list
    if (entries[hash_value] == NULL) {
        node = make_node(key);
        entries[hash_value] = node;
        return NULL;
    }

    // insert existing node
    node = insert_tail_node(entries[hash_value], key);
    return NULL;
}

// free the hash table
void free_hashtable(ht_t* hashtable) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        delete_list(hashtable->entries[i]);
    }
    free(hashtable->entries);
    free(hashtable);
}
