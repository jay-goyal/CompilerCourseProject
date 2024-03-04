/*
GROUP 20
VAIBHAV SINGLA - 2021A7PS2227P
JAY GOYAL - 2021A7PS2418P
SANJEEV MALLICK - 2021A7PS2217P
TRAYAMBAK SHRIVASTAVA - 2021A7PS1629P
PRANAV TANNA - 2021A7PS2685P
ARYAN BANSAL - 2021A7PS2776P
*/

#include "helper.h"

#include <stdlib.h>

#include "lexerDef.h"


// populate the symbol table with the keywords
void populate_symbol_table(ht_t* st) {
    stentry_t* entry = (stentry_t*)calloc(1, sizeof(stentry_t));
    char* lexeme = (char*)calloc(5, sizeof(char));
    strcpy(lexeme,"with");
    entry->lexeme = lexeme;
    entry->token_type = TK_WITH;
    insert_entry(st, entry);

    entry = (stentry_t*)calloc(1, sizeof(stentry_t));
    lexeme = (char*)calloc(11, sizeof(char));
    strcpy(lexeme,"parameters");
    entry->lexeme = lexeme;
    entry->token_type = TK_PARAMETERS;
    insert_entry(st, entry);

    entry = (stentry_t*)calloc(1, sizeof(stentry_t));
    lexeme = (char*)calloc(4, sizeof(char));
    strcpy(lexeme,"end");
    entry->lexeme = lexeme;
    entry->token_type = TK_END;
    insert_entry(st, entry);

    entry = (stentry_t*)calloc(1, sizeof(stentry_t));
    lexeme = (char*)calloc(6, sizeof(char));
    strcpy(lexeme,"while");
    entry->lexeme = lexeme;
    entry->token_type = TK_WHILE;
    insert_entry(st, entry);

    entry = (stentry_t*)calloc(1, sizeof(stentry_t));
    lexeme = (char*)calloc(6, sizeof(char));
    strcpy(lexeme,"union");
    entry->lexeme = lexeme;
    entry->token_type = TK_UNION;
    insert_entry(st, entry);

    entry = (stentry_t*)calloc(1, sizeof(stentry_t));
    lexeme = (char*)calloc(9, sizeof(char));
    strcpy(lexeme,"endunion");
    entry->lexeme = lexeme;
    entry->token_type = TK_ENDUNION;
    insert_entry(st, entry);

    entry = (stentry_t*)calloc(1, sizeof(stentry_t));
    lexeme = (char*)calloc(11, sizeof(char));
    strcpy(lexeme,"definetype");
    entry->lexeme = lexeme;
    entry->token_type = TK_DEFINETYPE;
    insert_entry(st, entry);

    entry = (stentry_t*)calloc(1, sizeof(stentry_t));
    lexeme = (char*)calloc(3, sizeof(char));
    strcpy(lexeme,"as");
    entry->lexeme = lexeme;
    entry->token_type = TK_AS;
    insert_entry(st, entry);

    entry = (stentry_t*)calloc(1, sizeof(stentry_t));
    lexeme = (char*)calloc(5, sizeof(char));
    strcpy(lexeme,"type");
    entry->lexeme = lexeme;
    entry->token_type = TK_TYPE;
    insert_entry(st, entry);

    entry = (stentry_t*)calloc(1, sizeof(stentry_t));
    lexeme = (char*)calloc(5, sizeof(char));
    strcpy(lexeme,"_main");
    entry->lexeme = lexeme;
    entry->token_type = TK_MAIN;
    insert_entry(st, entry);

    entry = (stentry_t*)calloc(1, sizeof(stentry_t));
    lexeme = (char*)calloc(7, sizeof(char));
    strcpy(lexeme,"global");
    entry->lexeme = lexeme;
    entry->token_type = TK_GLOBAL;
    insert_entry(st, entry);

    entry = (stentry_t*)calloc(1, sizeof(stentry_t));
    lexeme = (char*)calloc(10, sizeof(char));
    strcpy(lexeme,"parameter");
    entry->lexeme = lexeme;
    entry->token_type = TK_PARAMETER;
    insert_entry(st, entry);

    entry = (stentry_t*)calloc(1, sizeof(stentry_t));
    lexeme = (char*)calloc(5, sizeof(char));
    strcpy(lexeme,"list");
    entry->lexeme = lexeme;
    entry->token_type = TK_LIST;
    insert_entry(st, entry);

    entry = (stentry_t*)calloc(1, sizeof(stentry_t));
    lexeme = (char*)calloc(6, sizeof(char));
    strcpy(lexeme,"input");
    entry->lexeme = lexeme;
    entry->token_type = TK_INPUT;
    insert_entry(st, entry);

    entry = (stentry_t*)calloc(1, sizeof(stentry_t));
    lexeme = (char*)calloc(7, sizeof(char));
    strcpy(lexeme,"output");
    entry->lexeme = lexeme;
    entry->token_type = TK_OUTPUT;
    insert_entry(st, entry);

    entry = (stentry_t*)calloc(1, sizeof(stentry_t));
    lexeme = (char*)calloc(4, sizeof(char));
    strcpy(lexeme,"int");
    entry->lexeme = lexeme;
    entry->token_type = TK_INT;
    insert_entry(st, entry);

    entry = (stentry_t*)calloc(1, sizeof(stentry_t));
    lexeme = (char*)calloc(5, sizeof(char));
    strcpy(lexeme,"real");
    entry->lexeme = lexeme;
    entry->token_type = TK_REAL;
    insert_entry(st, entry);

    entry = (stentry_t*)calloc(1, sizeof(stentry_t));
    lexeme = (char*)calloc(9, sizeof(char));
    strcpy(lexeme,"endwhile");
    entry->lexeme = lexeme;
    entry->token_type = TK_ENDWHILE;
    insert_entry(st, entry);

    entry = (stentry_t*)calloc(1, sizeof(stentry_t));
    lexeme = (char*)calloc(3, sizeof(char));
    strcpy(lexeme,"if");
    entry->lexeme = lexeme;
    entry->token_type = TK_IF;
    insert_entry(st, entry);

    entry = (stentry_t*)calloc(1, sizeof(stentry_t));
    lexeme = (char*)calloc(5, sizeof(char));
    strcpy(lexeme,"then");
    entry->lexeme = lexeme;
    entry->token_type = TK_THEN;
    insert_entry(st, entry);

    entry = (stentry_t*)calloc(1, sizeof(stentry_t));
    lexeme = (char*)calloc(6, sizeof(char));
    strcpy(lexeme,"endif");
    entry->lexeme = lexeme;
    entry->token_type = TK_ENDIF;
    insert_entry(st, entry);

    entry = (stentry_t*)calloc(1, sizeof(stentry_t));
    lexeme = (char*)calloc(5, sizeof(char));
    strcpy(lexeme,"read");
    entry->lexeme = lexeme;
    entry->token_type = TK_READ;
    insert_entry(st, entry);

    entry = (stentry_t*)calloc(1, sizeof(stentry_t));
    lexeme = (char*)calloc(6, sizeof(char));
    strcpy(lexeme,"write");
    entry->lexeme = lexeme;
    entry->token_type = TK_WRITE;
    insert_entry(st, entry);

    entry = (stentry_t*)calloc(1, sizeof(stentry_t));
    lexeme = (char*)calloc(7, sizeof(char));
    strcpy(lexeme,"return");
    entry->lexeme = lexeme;
    entry->token_type = TK_RETURN;
    insert_entry(st, entry);

    entry = (stentry_t*)calloc(1, sizeof(stentry_t));
    lexeme = (char*)calloc(5, sizeof(char));
    strcpy(lexeme,"call");
    entry->lexeme = lexeme;
    entry->token_type = TK_CALL;
    insert_entry(st, entry);

    entry = (stentry_t*)calloc(1, sizeof(stentry_t));
    lexeme = (char*)calloc(7, sizeof(char));
    strcpy(lexeme,"record");
    entry->lexeme = lexeme;
    entry->token_type = TK_RECORD;
    insert_entry(st, entry);

    entry = (stentry_t*)calloc(1, sizeof(stentry_t));
    lexeme = (char*)calloc(10, sizeof(char));
    strcpy(lexeme,"endrecord");
    entry->lexeme = lexeme;
    entry->token_type = TK_ENDRECORD;
    insert_entry(st, entry);

    entry = (stentry_t*)calloc(1, sizeof(stentry_t));
    lexeme = (char*)calloc(5, sizeof(char));
    strcpy(lexeme,"else");
    entry->lexeme = lexeme;
    entry->token_type = TK_ELSE;
    insert_entry(st, entry);
}
