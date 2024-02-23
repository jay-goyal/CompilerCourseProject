#include "transition_diagram.h"

state_t* create_state(int retract, bool exit, bool line_increment,
                      bool is_final) {
    state_t* state = (state_t*)malloc(sizeof(struct State));
    state->transitions.size = 0;
    state->retract = retract;
    state->exit = exit;
    state->line_increment = line_increment;
    state->is_final = is_final;
    return state;
}

void add_transition(state_t* state, char symbol[], int next_state) {
    state->transitions.symbol =
        (char**)realloc(state->transitions.symbol,
                        (state->transitions.size + 1) * sizeof(char*));
    state->transitions.next_state =
        (int*)realloc(state->transitions.next_state,
                      (state->transitions.size + 1) * sizeof(int));
    state->transitions.size++;
    state->transitions.symbol[state->transitions.size - 1] =
        (char*)malloc(2 * sizeof(char));
    state->transitions.symbol[state->transitions.size - 1][0] = symbol[0];
    state->transitions.symbol[state->transitions.size - 1][1] = symbol[1];
    state->transitions.next_state[state->transitions.size - 1] = next_state;
}

state_t** create_transition_diagram() {
    // Create states
    state_t** td = (state_t**)malloc(NUM_STATES * sizeof(state_t*));
    for (int i = 0; i < NUM_STATES; i++) {
        int retract = 0;
        bool exit = false, line_increment = false, is_final = false;

        if (i == 62) exit = true;
        if (i == 34 || i == 61) line_increment = true;
        if (i == 5 || i == 9 || i == 18 || i == 22 || i == 28 || i == 36 ||
            i == 42 || i == 44 || i == 51 || i == 60 || i == 63)
            retract++;
        if (i == 60 || i == 63) retract++;

        td[i] = create_state(retract, exit, line_increment, is_final);
    }

    int final_states[35] = {4,  5,  6,  7,  9,  10, 17, 18, 22, 25, 28, 31,
                            32, 34, 36, 37, 38, 42, 44, 45, 47, 49, 51, 52,
                            53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63};
    for (int i = 0; i < 35; i++) {
        td[final_states[i]]->is_final = true;
    }

    // TODO: Return Values

    // TODO: Create transitions
    add_transition(td[0], "09", 8);
    add_transition(td[0], "az", 43);

    add_transition(td[43], "az", 43);
    add_transition(td[43], "\0\x7f", 44);

    add_transition(td[8], "09", 8);
    add_transition(td[8], "..", 11);
    add_transition(td[8], "\0\x7f", 9);

    add_transition(td[11], "09", 12);
    add_transition(td[11], "\0\x7f", 63);

    add_transition(td[12], "09", 13);

    add_transition(td[13], "EE", 14);
    add_transition(td[13], "\0\x7f", 18);

    add_transition(td[14], "++", 15);
    add_transition(td[14], "--", 15);
    add_transition(td[14], "09", 16);

    add_transition(td[15], "09", 16);

    add_transition(td[16], "09", 17);
    return td;
}

void clear_transition_diagram(state_t** td) {
    for (int i = 0; i < NUM_STATES; i++) {
        state_t* state = td[i];
        int size = state->transitions.size;
        if (size > 0) {
            for (int j = 0; j < size; j++) {
                free(state->transitions.symbol[j]);
            }
            free(state->transitions.symbol);
            free(state->transitions.next_state);
        }
        free(state);
    }
    free(td);
}
