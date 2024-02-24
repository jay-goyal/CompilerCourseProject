#include <stdio.h>
#include <stdlib.h>

#include "hash_table/hash_table.h"
#include "lexical_analyzer/lexer.h"
#include "lexical_analyzer/lexer_types.h"

int main(int argc, char* argv[]) {
    printf("RUNNING\n");

    ht_t* symbol_table = create_hash_table();
    tokeninfo_t ret_token = get_next_token("test.txt", symbol_table);
    while (ret_token.token_type != -2) {
        switch (ret_token.token_type) {
            case TK_NUM:
                printf("%ld -> %s\n", ret_token.info.num_val,
                       token_str[TK_NUM]);
                break;
            case TK_RNUM:
                printf("%f -> %s\n", ret_token.info.rnum_val,
                       token_str[TK_RNUM]);
                break;
            case TK_FUNID:
            case TK_FIELDID:
            case TK_ID:
            case TK_RUID:
                printf("%s -> %s\n", ret_token.info.stentry->lexeme,
                       token_str[ret_token.token_type]);
        }
        ret_token = get_next_token("test.txt", symbol_table);
    }

    return 0;
}

void populate_symbol_table(ht_t* st) {
    stentry_t* entry = (stentry_t*)calloc(1, sizeof(stentry_t));
    char* lexeme = (char*)calloc(5, sizeof(char));
    lexeme = "with";
    entry->lexeme = lexeme;
    entry->token_type = TK_WITH;
    insert_entry(st, entry);
}
