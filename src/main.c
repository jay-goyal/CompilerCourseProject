#include <stdio.h>

#include "lexical_analyzer/transition_diagram.h"

int main(int argc, char* argv[]) {
    printf("RUNNING\n");
    State_t** td = create_transition_diagram();
    clear_transition_diagram(td);
    return 0;
}
