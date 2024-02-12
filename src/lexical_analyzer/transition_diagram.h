#ifndef TRANSITION_DIAGRAM_H
#define TRANSITION_DIAGRAM_H

#include <stdlib.h>
#include <stdbool.h>

#define NUM_STATES 64

typedef struct Transitions Transitions;
typedef struct State* State;

struct Transitions {
    int size;
    char** symbol;
    int* next_state;
};

struct State {
    Transitions transitions;
    int retract;
    bool exit;
    bool is_final;
    bool line_increment;
};

State create_state(int retract, bool exit, bool line_increment, bool is_final);
void add_transition(State state, char* symbol, int next_state);
State* create_transition_diagram();

State create_state(int retract, bool exit, bool line_increment, bool is_final) {
    State state = (State) malloc(sizeof(struct State));
    state->transitions.size = 0;
    state->retract = retract;
    state->exit = exit;
    state->line_increment = line_increment;
    state->is_final = is_final;
    return state;
}

void add_transition(State state, char* symbol, int next_state) {
    state->transitions.symbol = realloc(state->transitions.symbol, (state->transitions.size + 1) * sizeof(char*));
    state->transitions.next_state = realloc(state->transitions.next_state, (state->transitions.size + 1) * sizeof(int));
    state->transitions.size++;
    state->transitions.symbol[state->transitions.size - 1] = (char*) malloc(2 * sizeof(char));
    state->transitions.symbol[state->transitions.size - 1] = symbol;
    state->transitions.next_state[state->transitions.size - 1] = next_state;
}

State* create_transition_diagram() {
    // Create states
    State* td = (State*) malloc(NUM_STATES * sizeof(State));
    for(int i=0; i<NUM_STATES; i++) {
        int retract = 0;
        bool exit = false, line_increment = false, is_final = false;

        if(i == 62)
            exit = true;
        if(i == 34 || i == 61)
            line_increment = true;
        if(i == 5 || i == 9 || i == 18 || i == 22 || i == 28 || i == 36 || i == 42 || i == 44 || i == 51 || i == 60 || i == 63)
            retract++;
        if(i == 60 || i == 63)
            retract++;

        td[i] = create_state(retract, exit, line_increment, is_final);
    }

    int final_states[35] = {4,5,6,7,9,10,17,18,22,25,28,31,32,34,36,37,38,42,44,45,47,49,51,52,53,54,55,56,57,58,59,60,61,62,63};
    for(int i=0; i<35; i++) {
        td[final_states[i]]->is_final = true;
    }

    // Create transitions
    // Using $$ for Other transition
    add_transition(td[0], "<<", 1);
    add_transition(td[0], "..", 7);
    add_transition(td[0], "09", 8);
    add_transition(td[0], "--", 10);
    add_transition(td[0], "__", 19);
    add_transition(td[0], "@@", 23);
    add_transition(td[0], "##", 26);
    add_transition(td[0], "**", 56);
    add_transition(td[0], "[[", 59);
    add_transition(td[0], "&&", 29);
    add_transition(td[0], "]]", 58);

    return td;
}

#endif