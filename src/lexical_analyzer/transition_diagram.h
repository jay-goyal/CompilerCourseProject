#ifndef TRANSITION_DIAGRAM_H
#define TRANSITION_DIAGRAM_H

#include <stdbool.h>
#include <stdlib.h>

#define NUM_STATES 64

typedef struct Transitions Transitions_t;
typedef struct State State_t;

struct Transitions {
    int size;
    char** symbol;
    int* next_state;
};

struct State {
    Transitions_t transitions;
    int retract;
    bool exit;
    bool is_final;
    bool line_increment;
};

State_t* create_state(int retract, bool exit, bool line_increment,
                      bool is_final);
void add_transition(State_t* state, char symbol[], int next_state);
State_t** create_transition_diagram();
void clear_transition_diagram(State_t** td);

#endif
