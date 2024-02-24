#include "lexer.h"

#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>

#include "lexer_types.h"
#include "transition_diagram.h"

tokeninfo_t get_next_token(char* filename) {
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
    tokeninfo_t token = {0, {0}};
    if (!is_lexer_init) {
        buffer = (char*)calloc(BUF_SIZE * 2, sizeof(char));
        is_lexer_init = true;
        fptr = open(filename, O_RDONLY);
        td = create_transition_diagram();
        res_read = read(fptr, buffer, BUF_SIZE);
    }

    printf("BYTES READ: %d\n", res_read);
    printf("%s\n", buffer);
    printf("****************\n");

    while (forward < res_read) {
        char curr_char = buffer[forward];
        curr_state = get_next_state(curr_state, curr_char, td);
        if (curr_state == -1) {
            forward += 1;
            char value[forward - begin + 1];
            value[forward - begin] = '\0';
            for (int i = 0; i < sizeof(value) - 1; i++)
                value[i] = buffer[begin++];
            printf("'%s' -> LEXICAL ERROR\n", value);
            begin = forward;
            curr_state = 0;
        }
        if (td[curr_state]->is_final) {
            int token = td[curr_state]->token;
            forward -= td[curr_state]->retract - 1;
            char value[forward - begin + 1];
            value[forward - begin] = '\0';
            for (int i = 0; i < sizeof(value) - 1; i++)
                value[i] = buffer[begin++];
            if (token > 0)
                printf("'%s' -> %s on line %d\n", value, token_str[token],
                       line_number);
            if (td[curr_state]->line_increment) line_number++;
            if (!td[curr_state]->exit)
                curr_state = 0;
            else
                is_end = true;
        } else {
            forward += 1;
        }
    }

    if (is_end) {
        if (buffer != NULL) free(buffer);
        if (fptr != -1) close(fptr);
        if (td != NULL) clear_transition_diagram(td);
        buffer = NULL;
        fptr = -1;
        td = NULL;
        token.token_type = -1;
        return token;
    }
    return token;
}
