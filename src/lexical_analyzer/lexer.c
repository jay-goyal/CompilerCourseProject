#include "lexer.h"

#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>

#include "lexer_types.h"
#include "transition_diagram.h"

tokeninfo_t get_next_token(char* filename, ht_t* symbol_table) {
    static unsigned int begin = 0;
    static unsigned int forward = 0;
    static int res_read;
    static bool is_lexer_init = false;
    static bool is_end = false;
    static char* buffer = NULL;
    static int fptr = -1;
    static state_t** td = NULL;
    static int curr_state = 0;
    static int line_number = 1;
    tokeninfo_t ret_token = {0, {0}};
    if (!is_lexer_init) {
        buffer = (char*)calloc(BUF_SIZE * 2, sizeof(char));
        is_lexer_init = true;
        fptr = open(filename, O_RDONLY);
        td = create_transition_diagram();
        res_read = read(fptr, buffer, BUF_SIZE);

        printf("BYTES READ: %d\n", res_read);
        printf("%s\n", buffer);
        printf("****************\n");
    }

    if (is_end) {
        if (buffer != NULL) free(buffer);
        if (fptr != -1) close(fptr);
        if (td != NULL) clear_transition_diagram(td);
        buffer = NULL;
        fptr = -1;
        td = NULL;
        ret_token.token_type = -1;
        return ret_token;
    }

start_parsing:
    while (!td[curr_state]->is_final) {
        char curr_char = buffer[forward];
        curr_state = get_next_state(curr_state, curr_char, td);
        if (curr_state == -1) {
            forward += 1;
            int val_len = forward - begin + 1;
            char value[val_len];
            value[val_len - 1] = '\0';
            for (int i = 0; i < sizeof(value) - 1; i++)
                value[i] = buffer[begin++];
            printf("'%s' -> LEXICAL ERROR\n", value);
            begin = forward;
            curr_state = 0;
            ret_token.token_type = -1;
            return ret_token;
        } else {
            forward += 1;
        }
    }
    int token = td[curr_state]->token;
    forward -= td[curr_state]->retract - 1;
    int val_len = forward - begin + 1;
    char value[val_len];
    value[val_len - 1] = '\0';
    for (int i = 0; i < val_len - 1; i++) value[i] = buffer[begin++];
    if (token > 0) {
        ret_token.token_type = token;
        switch (token) {
            case TK_NUM:
                ret_token.info.num_val = atol(value);
                break;
            case TK_RNUM:
                ret_token.info.rnum_val = atof(value);
                break;
            case TK_FUNID:
            case TK_FIELDID:
            case TK_ID:
            case TK_RUID:
                char* val_heap = (char*)calloc(val_len, sizeof(char));
                strcpy(val_heap, value);
                stentry_t* entry = (stentry_t*)calloc(1, sizeof(stentry_t));
                entry->lexeme = val_heap;
                entry->token_type = token;
                stentry_t* existing_entry = insert_entry(symbol_table, entry);
                if (existing_entry != NULL) {
                    free(entry);
                    entry = existing_entry;
                }
                ret_token.info.stentry = entry;
                break;
        }
    } else
        goto start_parsing;
    if (td[curr_state]->line_increment) line_number++;
    if (!td[curr_state]->exit)
        curr_state = 0;
    else {
        is_end = true;
        free(buffer);
        close(fptr);
        clear_transition_diagram(td);
        buffer = NULL;
        fptr = -1;
        td = NULL;
    }

    return ret_token;
}
