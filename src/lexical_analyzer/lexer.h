#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>

#include "lexer_types.h"

#define BUF_SIZE 512

tokeninfo_t get_next_token(char* filename);
void remove_comments(FILE* fin, FILE* fout);

#endif  // !LEXER_H
