#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include <stdbool.h>

#include "LinkedList.h"
#include "lexerDef.h"

#define TABLE_SIZE 1000
// #define TABLE_SIZE 7
typedef struct HashTable {
    node_t** entries;
} ht_t;

unsigned int hash(char* key);
ht_t* create_hash_table();
stentry_t* insert_entry(ht_t* hashtable, stentry_t* key);
void free_hashtable(ht_t* hashtable);
node_t* check_node_exists(ht_t* hashtable, stentry_t* key);

#endif  // !HASH_TABLE_H
