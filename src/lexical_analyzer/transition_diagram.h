#ifndef TRANSITION_DIAGRAM_H
#define TRANSITION_DIAGRAM_H

#include <stdlib.h>
#include <stdbool.h>

#define NUM_STATES 65

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
    add_transition(td[0],"0255",64); //trap state
    add_transition(td[1],"--",2);
    add_transition(td[1],"0255",5);
    add_transition(td[1],"==",6);
    add_transition(td[2],"--",3);
    add_transition(td[2],"0255",60);
    add_transition(td[3],"--",4);
    add_transition(td[3],"0255",64); //trap state


    add_transition(td[0], "..", 7);


    add_transition(td[0], "09", 8);
    add_transition(td[8],"09",8);
    add_transition(td[8],"0255",9);
    add_transition(td[8],"..",11);
    // add_transition(td[11],"",63); //input nahi padha jaa raha vro //iska trap state agar ho mat bhoolna
    add_transition(td[11],"09",12);
    add_transition(td[12],"09",13);
    add_transition(td[12],"0255",64); //trap state
    add_transition(td[13],"0255",18);
    add_transition(td[13],"EE",14);
    add_transition(td[14],"+-",15);
    add_transition(td[14],"09",16);
    add_transition(td[14],"0255",64); //trap state
    add_transition(td[15],"09",16);
    add_transition(td[16],"09",17);
    add_transition(td[16],"0255",64); //trap state



    add_transition(td[0], "--", 10);



    add_transition(td[0], "__", 19);
    add_transition(td[19],"0255",64); //trap state
    add_transition(td[19],"aZ",20); //LOWER+UPPER=LETTER
    add_transition(td[20],"aZ",20);
    add_transition(td[20],"09",21);
    add_transition(td[20],"0255",22);
    add_transition(td[21],"0255",22);
    add_transition(td[21],"09",21);


    add_transition(td[0], "@@", 23);
    add_transition(td[23],"0255",64); //trap state
    add_transition(td[23],"@@",24);
    add_transition(td[24],"@@",25);
    add_transition(td[24],"0255",64); //trap state



    add_transition(td[0], "##", 26);
    add_transition(td[26],"0255",64); //trap state
    add_transition(td[26],"az",27); //az=Lower
    add_transition(td[27],"az",27);
    add_transition(td[27],"0255",28);


    add_transition(td[0], "**", 56);



    add_transition(td[0], "[[", 59);



    add_transition(td[0], "&&", 29);
    add_transition(td[29],"0255",64); //trap state
    add_transition(td[29],"&&",30);
    add_transition(td[30],"0255",64); //trap state
    add_transition(td[30],"&&",31);


    add_transition(td[0], "]]", 58);


    add_transition(td[0],",,",53); //check if comma or apostrophe

    add_transition(td[0],"//",32);

    add_transition(td[0],"%%",33);
    add_transition(td[33],"0255",33); //check this once
    add_transition(td[33],"\\n",34); //only new line char

    add_transition(td[0],"))",37);

    add_transition(td[0],"blank\\t",35);
    add_transition(td[35],"blank\\t",35);
    add_transition(td[35],"0255",36);


    add_transition(td[0],"((",38);


    add_transition(td[0],"bd",39); //bd=BTOD
    add_transition(td[39],"0255",44);
    add_transition(td[39],"az",43); //LOWER
    add_transition(td[39],"27",40); //TTOS
    add_transition(td[40],"bd",40);
    add_transition(td[40],"0255",42);
    add_transition(td[40],"27",41);
    add_transition(td[41],"27",42);
    add_transition(td[41],"0255",42);

    add_transition(td[0],"\\n",61); //only new line char

    add_transition(td[0],"aez",43); //NBTOD
    add_transition(td[43],"az",43);
    add_transition(td[43],"0255",44);


    add_transition(td[0],"++",45);


    add_transition(td[0],"!!",46);
    add_transition(td[46],"0255",64);
    add_transition(td[46],"==",47);


    add_transition(td[0],"==",48);
    add_transition(td[48],"0255",64); //trap state
    add_transition(td[48],"==",49);
    


    add_transition(td[0],">>",50);
    add_transition(td[50],"0255",51);
    add_transition(td[50],"==",52);


    add_transition(td[0],"::",53);


    add_transition(td[0],";;",54);

    add_transition(td[0],"~~",55);


    add_transition(td[0],"EOF",62);








    return td;
}

#endif