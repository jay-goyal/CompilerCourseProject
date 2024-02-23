#include "lexer.h"

#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
    tokeninfo_t token = {0, {0}};
    if (!is_lexer_init) {
        buffer = (char*)calloc(BUF_SIZE * 2, sizeof(char));
        is_lexer_init = true;
        fptr = open(filename, O_RDONLY);
        td = create_transition_diagram();
        res_read = read(fptr, buffer, BUF_SIZE);
    }

    if (is_end) {
        free(buffer);
        close(fptr);
        clear_transition_diagram(td);
        token.token_type = -1;
        return token;
    }
    return token;
}
