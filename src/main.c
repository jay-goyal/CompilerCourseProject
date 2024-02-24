#include <stdio.h>

#include "lexical_analyzer/lexer.h"

int main(int argc, char* argv[]) {
    printf("RUNNING\n");

    get_next_token("test.txt");

    return 0;
}
