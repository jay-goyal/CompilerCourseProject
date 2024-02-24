#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>

#include "../hash_table/hash_table.h"
#include "lexer_types.h"

#define BUF_SIZE 512
#define TBUF_SIZE (BUF_SIZE * 2)

tokeninfo_t get_next_token(char* filename, ht_t* symbol_table);
void remove_comments(FILE* fin, FILE* fout);

#endif  // !LEXER_H
