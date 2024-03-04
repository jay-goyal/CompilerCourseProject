/*
GROUP 20
VAIBHAV SINGLA - 2021A7PS2227P
JAY GOYAL - 2021A7PS2418P
SANJEEV MALLICK - 2021A7PS2217P
TRAYAMBAK SHRIVASTAVA - 2021A7PS1629P
PRANAV TANNA - 2021A7PS2685P
ARYAN BANSAL - 2021A7PS2776P
*/

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
