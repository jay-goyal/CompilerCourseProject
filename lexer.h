#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>

#include "hash_table.h"
#include "lexerDef.h"

#define BUF_SIZE 512
#define TBUF_SIZE (BUF_SIZE * 2)

tokeninfo_t getNextToken(char* ip_filename, ht_t* symbol_table, bool parse);
void removeComments(char* fin);

#endif  // !LEXER_H
