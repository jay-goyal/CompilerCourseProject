#include "hash_table.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static node_t* check_node_exists(ht_t* hashtable, char** key) {
    unsigned int hash_value = hash(key);
    node_t** entries = hashtable->entries;
    node_t* curr_node = entries[hash_value];
    while (curr_node != NULL) {
        if (strcmp(*curr_node->key, *key) == 0) return curr_node;
        curr_node = curr_node->next;
    }
    return NULL;
}

unsigned int hash(char** key) {
    const char* key_str = *key;
    unsigned int value = 0;
    unsigned int len = strlen(key_str);

    for (unsigned int i = 0; i < len; i++) {
        value = (value * 41 + key_str[i]) % TABLE_SIZE;
    }

    return value;
}

ht_t* create_hash_table() {
    ht_t* hashtable = (ht_t*)malloc(sizeof(ht_t) * 1);
    if (hashtable == NULL) {
        printf("Cannot allocate the Hash Table");
        return NULL;
    }

    hashtable->entries = (node_t**)calloc(TABLE_SIZE, sizeof(node_t*));

    return hashtable;
}

void insert_key_val(ht_t* hashtable, char** key, int val) {
    unsigned int hash_value = hash(key);
    printf("INSERTING %s: %d at hash %u\n", *key, val, hash_value);
    node_t** entries = hashtable->entries;
    node_t* node = check_node_exists(hashtable, key);
    if (entries[hash_value] == NULL) {
        node_t* node = make_node(key, val);
        entries[hash_value] = node;
        return;
    }
    if (node != NULL) {
        node->val = val;
        return;
    }
    insert_tail_node(entries[hash_value], key, val);
}

int search_key(ht_t* hashtable, char** key) {
    node_t* node = check_node_exists(hashtable, key);
    if (node == NULL) {
        return node->val;
    }
    return -1;
}

void free_hashtable(ht_t* hashtable) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        delete_list(hashtable->entries[i]);
    }
    free(hashtable->entries);
    free(hashtable);
}
