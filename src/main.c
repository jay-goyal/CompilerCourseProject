#include <stdio.h>

#include "hash_table/hash_table.h"
#include "lexical_analyzer/lexer.h"
#include "lexical_analyzer/lexer_types.h"

int main(int argc, char* argv[]) {
    printf("RUNNING\n");

    ht_t* symbol_table = create_hash_table();
    tokeninfo_t ret_token = get_next_token("test.txt", symbol_table);
    while (ret_token.token_type != -1) {
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
