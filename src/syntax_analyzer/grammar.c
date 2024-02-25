#include "grammar.h"
#include "../lexical_analyzer/lexer_types.h"
#include <stdlib.h>

#define NUM_TERMINALS 57

gram_t *create_grammar() {
    gram_t *gram = (gram_t *) malloc(sizeof(gram_t));
    gram->nonterminals = (nt_t **) calloc(55, sizeof(nt_t *));
    populate_productions(gram);
    first_t *f = compute_first(gram, gram->nonterminals[0]);
    printf("First(FUNCALLSTMT):\n");
    for(int i=0; i<58; i++) {
        if(f->term[i] == 1) {
            if(i == 0)
                printf("EPSILON\n");
            else
            printf("%s\n", token_str[i-1]);
        }
    }
    return gram;
}

// Todo: Clear Grammar

first_t* compute_first(gram_t* gram, nt_t* nonterm) {
    first_t* first = (first_t *) malloc(sizeof(first_t));
    int num_prod = nonterm->num_prod;
    for(int i=0; i<num_prod; i++) {
        // printf("Production %d\n", gram->nonterminals[30]->productions[i]->right[0]);
        for(int k=0; k<nonterm->productions[i]->num_right; k++) {
            int symb = nonterm->productions[i]->right[k];
                // printf("%d %d\n", k, symb);
            if(symb <= NUM_TERMINALS) {
                first->term[symb + 1] = 1;
                break;
            }
            else {
                first_t* firstN = compute_first(gram, gram->nonterminals[symb-NUM_TERMINALS]);
                for(int j=0; j<=NUM_TERMINALS; j++) {
                    if(firstN->term[j] == 1)    first->term[j] = 1;
                }
                // epsilon
                if(gram->nonterminals[symb-NUM_TERMINALS]->productions[gram->nonterminals[symb-NUM_TERMINALS]->num_prod-1]->right[0] != EPSILON) {
                    break;
                }
            }
        }
    }
    
    return first;
}

nt_t* add_nonterminal(gram_t* gram, int nt) {
    gram->nonterminals[nt-NUM_TERMINALS] = (nt_t *) malloc(sizeof(nt_t));
    gram->nonterminals[nt-NUM_TERMINALS]->num_prod = 0;
    gram->nonterminals[nt-NUM_TERMINALS]->productions = (prod_t **) malloc(sizeof(prod_t *));
    return gram->nonterminals[nt-NUM_TERMINALS];
}

prod_t* create_production() {
    prod_t* prod = (prod_t *) malloc(sizeof(prod_t));
    prod->num_right = 0;
    return prod;
}

void add_production(nt_t* nonterm, prod_t* prod) {
    nonterm->num_prod++;
    nonterm->productions = (prod_t **) realloc(nonterm->productions, nonterm->num_prod * sizeof(prod_t *));
    nonterm->productions[nonterm->num_prod-1] = prod;
}

void add_right(prod_t* prod, int right) {
    prod->num_right++;
    prod->right = (int *) realloc(prod->right, prod->num_right * sizeof(int));
    prod->right[prod->num_right-1] = right;
}

void populate_productions(gram_t* gram) {
    nt_t* nonterm = add_nonterminal(gram, PROGRAM);
    prod_t* prod = create_production();
    add_right(prod, OTHERFUNCTIONS);
    add_right(prod, MAINFUNCTION);
    add_production(nonterm, prod);

    nonterm = add_nonterminal(gram, MAINFUNCTION);
    prod = create_production();
    add_right(prod, TK_MAIN);
    add_right(prod, STMTS);
    add_right(prod, TK_END);
    add_production(nonterm, prod);

    nonterm = add_nonterminal(gram, OTHERFUNCTIONS);
    prod = create_production();
    add_right(prod, FUNCTION);
    add_right(prod, OTHERFUNCTIONS);
    add_production(nonterm, prod);
    prod = create_production();
    add_right(prod, EPSILON);
    add_production(nonterm, prod);

    nonterm = add_nonterminal(gram, FUNCALLSTMT);
    prod = create_production();
    add_right(prod, OUTPUTPARAMETERS);
    add_right(prod, TK_CALL);
    add_right(prod, TK_FUNID);
    add_right(prod, TK_WITH);
    add_right(prod, TK_PARAMETERS);
    add_right(prod, INPUTPARAMETERS);
    add_right(prod, TK_SEM);
    add_production(nonterm, prod);

    nonterm = add_nonterminal(gram, OUTPUTPARAMETERS);
    prod = create_production();
    add_right(prod, TK_SQL);
    add_right(prod, IDLIST);
    add_right(prod, TK_SQR);
    add_right(prod, TK_ASSIGNOP);
    add_production(nonterm, prod);
    prod = create_production();
    add_right(prod, EPSILON);
    add_production(nonterm, prod);

    nonterm = add_nonterminal(gram, TERM);
    prod = create_production();
    add_right(prod, FACTOR);
    add_right(prod, TERMPRIME);
    add_production(nonterm, prod);
    
    nonterm = add_nonterminal(gram, INPUTPARAMETERS);
    prod = create_production();
    add_right(prod, TK_SQL);
    add_right(prod, IDLIST);
    add_right(prod, TK_SQR);
    add_production(nonterm, prod);
    
    nonterm = add_nonterminal(gram, IDLIST);
    prod = create_production();
    add_right(prod, TK_ID);
    add_right(prod, MORE_IDS);
    add_production(nonterm, prod);
    
    nonterm = add_nonterminal(gram, MORE_IDS);
    prod = create_production();
    add_right(prod, TK_COMMA);
    add_right(prod, IDLIST);
    add_production(nonterm, prod);
    prod = create_production();
    add_right(prod, EPSILON);
    add_production(nonterm, prod);
}