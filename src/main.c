#include <stdio.h>

#include "hash_table/hash_table.h"

int main(int argc, char *argv[]) {
    unsigned int val = hash("HELLO");
    printf("%du\n", val);
    return 0;
}
