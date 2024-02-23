#ifndef TRANSITION_DIAGRAM_H
#define TRANSITION_DIAGRAM_H

#include <stdbool.h>
#include <stdlib.h>

#define NUM_STATES 64

typedef struct Transitions Transitions_t;
typedef struct State state_t;

struct Transitions {
    int size;
    char** symbol;
    int* next_state;
};

struct State {
    Transitions_t transitions;
    int retract;
    int token;
    bool exit;
    bool is_final;
    bool line_increment;
};

state_t* create_state(int retract, bool exit, bool line_increment,
                      bool is_final);
void add_transition(state_t* state, char symbol[], int next_state);
state_t** create_transition_diagram();
void clear_transition_diagram(state_t** td);

#endif
