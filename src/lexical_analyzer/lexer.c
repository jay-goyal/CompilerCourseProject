#include "lexer.h"

#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "lexer_types.h"
#include "transition_diagram.h"

int populate_twin_buffers(int begin, int forward, char* buffer, int* fptr,
                          int* prev_buf) {
    int active = begin / BUF_SIZE;
    int next = forward / BUF_SIZE;
    if (next == *prev_buf || next == active) {
        return -1;
    }
    *prev_buf = next;
    return read(*fptr, buffer + (BUF_SIZE * next), BUF_SIZE);
}

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
    static int prev_buf = 0;
    tokeninfo_t ret_token = {0, {0}};
    if (!is_lexer_init) {
        buffer = (char*)calloc(TBUF_SIZE, sizeof(char));
        is_lexer_init = true;
        fptr = open(filename, O_RDONLY);
        td = create_transition_diagram();
        res_read = read(fptr, buffer, BUF_SIZE);
    }

    if (res_read < BUF_SIZE && forward % BUF_SIZE >= res_read) {
        is_end = true;
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
        if (curr_char == '\0') {
            is_end = true;
            free(buffer);
            close(fptr);
            clear_transition_diagram(td);
            buffer = NULL;
            fptr = -1;
            td = NULL;
            ret_token.token_type = -1;
            return ret_token;
        }
        curr_state = get_next_state(curr_state, curr_char, td);
        if (curr_state == -1) {
            forward += 1;
            int val_len = forward - begin + 1;
            if (val_len < 0) {
                val_len = TBUF_SIZE - begin + forward;
            }
            forward = forward % TBUF_SIZE;
            int tmp =
                populate_twin_buffers(begin, forward, buffer, &fptr, &prev_buf);
            if (tmp != -1) res_read = tmp;
            char value[val_len];
            value[val_len - 1] = '\0';
            for (int i = 0; i < val_len - 1; i++) {
                value[i] = buffer[begin];
                begin = (begin + 1) % TBUF_SIZE;
            }
            printf("'%s' -> LEXICAL ERROR at Line Number %d\n", value,
                   line_number);
            begin = forward;
            curr_state = 0;
            ret_token.token_type = -2;
            return ret_token;
        } else if (!td[curr_state]->is_final) {
            forward = (forward + 1) % TBUF_SIZE;
            int tmp =
                populate_twin_buffers(begin, forward, buffer, &fptr, &prev_buf);
            if (tmp != -1) res_read = tmp;
        }
    }

    int token = td[curr_state]->token;
    forward -= td[curr_state]->retract - 1;
    int val_len = forward - begin + 1;
    if (val_len < 0) {
        val_len = TBUF_SIZE - begin + forward;
    }
    forward = forward % TBUF_SIZE;
    int tmp = populate_twin_buffers(begin, forward, buffer, &fptr, &prev_buf);
    if (tmp != -1) res_read = tmp;

    char value[val_len];
    value[val_len - 1] = '\0';
    for (int i = 0; i < val_len - 1; i++) {
        value[i] = buffer[begin];
        begin = (begin + 1) % TBUF_SIZE;
    }
    if (td[curr_state]->line_increment) line_number++;

    if (token >= 0 && token != TK_COMMENT) {
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
            case TK_RUID: {
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
                ret_token.token_type = entry->token_type;
                ret_token.info.stentry = entry;
                break;
            }
        }
    } else {
        curr_state = 0;
        goto start_parsing;
    }

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

    ret_token.line_no = line_number;
    return ret_token;
}
