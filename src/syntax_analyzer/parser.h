#ifndef PARSER_H
#define PARSER_H

#include "grammar.h"

typedef struct ParseTable {
    prod_t ***table;
} pt_t;

pt_t create_parse_table(gram_t *gram, set_t **first_sets, set_t **follow_sets);

#endif