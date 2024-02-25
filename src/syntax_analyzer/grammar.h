#ifndef GRAMMAR_H
#define GRAMMAR_H

#include "../lexical_analyzer/lexer.h"

#define PROGRAM 57
#define MAINFUNCTION 58
#define OTHERFUNCTIONS 59
#define FUNCTION 60
#define INPUT_PAR 61
#define OUTPUT_PAR 62
#define PARAMETER_LIST 63
#define DATATYPE 64
#define PRIMITIVEDATATYPE 65
#define CONSTRUCTEDDATATYPE 66
#define REMAINING_LIST 67
#define STMTS 68
#define TYPEDEFINITIONS 69
#define ACTUALORREDEFINED 70
#define TYPEDEFINITION 71
#define FIELDDEFINITIONS 72
#define FIELDDEFINITION 73
#define FIELDTYPE 74
#define MOREFIELDS 75
#define DECLARATIONS 76
#define DECLARATION 77
#define GLOBAL_OR_NOT 78
#define OTHERSTMTS 79
#define STMT 80
#define ASSIGNMENTSTMT 81
#define SINGLEORRECID 82
#define CONSTRUCTEDVARIABLE 83
#define ONEEXPANSION 84
#define MOREEXPANSIONS 85
#define FUNCALLSTMT 86
#define OUTPUTPARAMETERS 87
#define INPUTPARAMETERS 88
#define ITERATIVESTMT 89
#define CONDITIONALSTMT 90
#define ELSEPART 91
#define IOSTMT 92
#define ARITHMETICEXPRESSION 93
#define EXPPRIME 94
#define TERM 95
#define TERMPRIME 96
#define FACTOR 97
#define HIGHPRECEDENCEOPERATOR 98
#define LOWPRECEDENCEOPERATORS 99
#define OPERATOR 100
#define BOOLEANEXPRESSION 101
#define VAR 102
#define BOOLEANEXPRESSION 103
#define LOGICALOP 104
#define RELATIONALOP 105
#define RETURNSTMT 106
#define OPTIONALRETURN 107
#define IDLIST 108
#define MORE_IDS 109
#define DEFINETYPESTMT 110
#define A 111

typedef struct Production {
    int num_right;
    int *right;
} prod_t;

typedef struct Nonterminal {
    int num_prod;
    prod_t **productions;
} nt_t;

typedef struct Grammar {
    nt_t **nonterminals;
} gram_t;

gram_t *create_grammar();
// nt_t *add_nonterminal(int nt, prod_t *prod);
// prod_t *add_production(int *right);

#endif