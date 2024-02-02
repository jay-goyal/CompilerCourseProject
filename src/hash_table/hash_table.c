#include "hash_table.h"

#include <string.h>

unsigned int hash(const char *key) {
    unsigned int value = 0;
    unsigned int len = strlen(key);

    for (unsigned int i = 0; i < len; i++) {
        value = (value * 41 + key[i]) % TABLE_SIZE;
    }

    return value;
}
