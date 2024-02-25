#include "grammar.h"
#include "../lexical_analyzer/lexer_types.h"
#include <stdlib.h>

#define NUM_TERMINALS 57

gram_t *create_grammar() {
    gram_t *gram = (gram_t *) malloc(sizeof(gram_t));
    gram->nonterminals = (nt_t **) calloc(55, sizeof(nt_t *));
    populate_productions(gram);
    return gram;
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
    nonterm->productions = (prod_t **) realloc(nonterm->productions, sizeof(prod_t *));
    nonterm->productions[nonterm->num_prod-1] = prod;
}

void add_right(prod_t* prod, int right) {
    prod->num_right++;
    prod->right = (int *) realloc(prod->right, sizeof(int));
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
}