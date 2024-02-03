#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include <stdbool.h>

#include "../linked_list/LinkedList.h"

#define TABLE_SIZE 10000
// #define TABLE_SIZE 7
typedef struct HashTable {
    node_t** entries;
} ht_t;

unsigned int hash(char** key);
ht_t* create_hash_table();
void insert_key_val(ht_t* hashtable, char** key, int val);
void free_hashtable(ht_t* hashtable);
int search_key(ht_t* hashtable, char** key);

#endif  // !HASH_TABLE_H
