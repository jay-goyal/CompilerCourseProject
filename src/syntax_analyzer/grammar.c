#include "grammar.h"
#include "../lexical_analyzer/lexer_types.h"
#include <stdlib.h>

#define NUM_TERMINALS 57

gram_t *create_grammar()
{
    gram_t *gram = (gram_t *)malloc(sizeof(gram_t));
    gram->nonterminals = (nt_t **)calloc(55, sizeof(nt_t *));
    populate_productions(gram);
    first_t *f = compute_first(gram, gram->nonterminals[22]);
    for (int i = 0; i < 58; i++)
    {
        if (f->term[i] == 1)
        {
            if (i == 0)
                printf("EPSILON\n");
            else
                printf("%s\n", token_str[i - 1]);
        }
    }
    return gram;
}

// Todo: Clear Grammar

first_t *compute_first(gram_t *gram, nt_t *nonterm)
{
    first_t *first = (first_t *)malloc(sizeof(first_t));
    int num_prod = nonterm->num_prod;
    for (int i = 0; i < num_prod; i++)
    {
        for (int k = 0; k < nonterm->productions[i]->num_right; k++)
        {
            int symb = nonterm->productions[i]->right[k];
            if (symb <= NUM_TERMINALS)
            {
                first->term[symb + 1] = 1;
                break;
            }
            else
            {
                first_t *firstN = compute_first(gram, gram->nonterminals[symb - NUM_TERMINALS]);
                for (int j = 0; j <= NUM_TERMINALS; j++)
                {
                    if (firstN->term[j] == 1)
                        first->term[j] = 1;
                }
                // epsilon
                if (gram->nonterminals[symb - NUM_TERMINALS]->productions[gram->nonterminals[symb - NUM_TERMINALS]->num_prod - 1]->right[0] != EPSILON)
                {
                    break;
                }
            }
        }
    }

    return first;
}

nt_t *add_nonterminal(gram_t *gram, int nt)
{
    gram->nonterminals[nt - NUM_TERMINALS] = (nt_t *)malloc(sizeof(nt_t));
    gram->nonterminals[nt - NUM_TERMINALS]->num_prod = 0;
    gram->nonterminals[nt - NUM_TERMINALS]->productions = (prod_t **)malloc(sizeof(prod_t *));
    return gram->nonterminals[nt - NUM_TERMINALS];
}

prod_t *create_production()
{
    prod_t *prod = (prod_t *)malloc(sizeof(prod_t));
    prod->num_right = 0;
    return prod;
}

void add_production(nt_t *nonterm, prod_t *prod)
{
    nonterm->num_prod++;
    nonterm->productions = (prod_t **)realloc(nonterm->productions, nonterm->num_prod * sizeof(prod_t *));
    nonterm->productions[nonterm->num_prod - 1] = prod;
}

void add_right(prod_t *prod, int right)
{
    prod->num_right++;
    prod->right = (int *)realloc(prod->right, prod->num_right * sizeof(int));
    prod->right[prod->num_right - 1] = right;
}

void populate_productions(gram_t *gram)
{
    nt_t *nonterm = add_nonterminal(gram, PROGRAM);
    prod_t *prod = create_production();
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

    nonterm = add_nonterminal(gram, FUNCTION);
    prod = create_production();
    add_right(prod, TK_FUNID);
    add_right(prod, INPUT_PAR);
    add_right(prod, OUTPUT_PAR);
    add_right(prod, TK_SEM);
    add_right(prod, STMTS);
    add_right(prod, TK_END);
    add_production(nonterm, prod);

    nonterm = add_nonterminal(gram, INPUT_PAR);
    prod = create_production();
    add_right(prod, TK_INPUT);
    add_right(prod, TK_PARAMETER);
    add_right(prod, TK_LIST);
    add_right(prod, TK_SQL);
    add_right(prod, PARAMETER_LIST);
    add_right(prod, TK_SQR);
    add_production(nonterm, prod);

    nonterm = add_nonterminal(gram, OUTPUT_PAR);
    prod = create_production();
    add_right(prod, TK_OUTPUT);
    add_right(prod, TK_PARAMETER);
    add_right(prod, TK_LIST);
    add_right(prod, TK_SQL);
    add_right(prod, PARAMETER_LIST);
    add_right(prod, TK_SQR);
    add_production(nonterm, prod);
    prod = create_production();
    add_right(prod, EPSILON);
    add_production(nonterm, prod);

    nonterm = add_nonterminal(gram, PARAMETER_LIST);
    prod = create_production();
    add_right(prod, DATATYPE);
    add_right(prod, TK_ID);
    add_right(prod, REMAINING_LIST);
    add_production(nonterm, prod);

    nonterm = add_nonterminal(gram, DATATYPE);
    prod = create_production();
    add_right(prod, PRIMITIVEDATATYPE);
    add_production(nonterm, prod);
    prod = create_production();
    add_right(prod, CONSTRUCTEDDATATYPE);
    add_production(nonterm, prod);

    nonterm = add_nonterminal(gram, PRIMITIVEDATATYPE);
    prod = create_production();
    add_right(prod, TK_INT);
    add_production(nonterm, prod);
    prod = create_production();
    add_right(prod, TK_REAL);
    add_production(nonterm, prod);

    nonterm = add_nonterminal(gram, CONSTRUCTEDDATATYPE);
    prod = create_production();
    add_right(prod, TK_RECORD);
    add_right(prod, TK_RUID);
    add_production(nonterm, prod);
    prod = create_production();
    add_right(prod, TK_UNION);
    add_right(prod, TK_RUID);
    add_production(nonterm, prod);
    prod = create_production();
    add_right(prod, TK_RUID);
    add_production(nonterm, prod);

    nonterm = add_nonterminal(gram, REMAINING_LIST);
    prod = create_production();
    add_right(prod, TK_COMMA);
    add_right(prod, PARAMETER_LIST);
    add_production(nonterm, prod);
    prod = create_production();
    add_right(prod, EPSILON);
    add_production(nonterm, prod);

    nonterm = add_nonterminal(gram, STMTS);
    prod = create_production();
    add_right(prod, TYPEDEFINITIONS);
    add_right(prod, DECLARATIONS);
    add_right(prod, OTHERSTMTS);
    add_right(prod, RETURNSTMT);
    add_production(nonterm, prod);

    nonterm = add_nonterminal(gram, TYPEDEFINITIONS);
    prod = create_production();
    add_right(prod, ACTUALORREDEFINED);
    add_right(prod, TYPEDEFINITIONS);
    add_production(nonterm, prod);
    prod = create_production();
    add_right(prod, EPSILON);
    add_production(nonterm, prod);

    nonterm = add_nonterminal(gram, ACTUALORREDEFINED);
    prod = create_production();
    add_right(prod, TYPEDEFINITION);
    add_production(nonterm, prod);
    prod = create_production();
    add_right(prod, DEFINETYPESTMT);
    add_production(nonterm, prod);

    nonterm = add_nonterminal(gram, TYPEDEFINITION);
    prod = create_production();
    add_right(prod, TK_RECORD);
    add_right(prod, TK_RUID);
    add_right(prod, FIELDDEFINITIONS);
    add_right(prod, TK_ENDRECORD);
    add_production(nonterm, prod);

    nonterm = add_nonterminal(gram, TYPEDEFINITION);
    prod = create_production();
    add_right(prod, TK_UNION);
    add_right(prod, TK_RUID);
    add_right(prod, FIELDDEFINITIONS);
    add_right(prod, TK_ENDUNION);
    add_production(nonterm, prod);

    nonterm = add_nonterminal(gram, FIELDDEFINITIONS);
    prod = create_production();
    add_right(prod, FIELDDEFINITION);
    add_right(prod, FIELDDEFINITION);
    add_right(prod, MOREFIELDS);
    add_production(nonterm, prod);

    nonterm = add_nonterminal(gram, FIELDDEFINITION);
    prod = create_production();
    add_right(prod, TK_TYPE);
    add_right(prod, FIELDTYPE);
    add_right(prod, TK_COLON);
    add_right(prod, TK_FIELDID);
    add_right(prod, TK_SEM);
    add_production(nonterm, prod);

    nonterm = add_nonterminal(gram, FIELDTYPE);
    prod = create_production();
    add_right(prod, PRIMITIVEDATATYPE);
    add_production(nonterm, prod);
    prod = create_production();
    add_right(prod, TK_RUID);
    add_production(nonterm, prod);

    nonterm = add_nonterminal(gram, MOREFIELDS);
    prod = create_production();
    add_right(prod, FIELDDEFINITION);
    add_right(prod, MOREFIELDS);
    add_production(nonterm, prod);
    prod = create_production();
    add_right(prod, EPSILON);
    add_production(nonterm, prod);

    nonterm = add_nonterminal(gram, DECLARATIONS);
    prod = create_production();
    add_right(prod, DECLARATION);
    add_right(prod, DECLARATIONS);
    add_production(nonterm, prod);
    prod = create_production();
    add_right(prod, EPSILON);
    add_production(nonterm, prod);

    nonterm = add_nonterminal(gram, DECLARATION);
    prod = create_production();
    add_right(prod, TK_TYPE);
    add_right(prod, DATATYPE);
    add_right(prod, TK_COLON);
    add_right(prod, TK_ID);
    add_right(prod, GLOBAL_OR_NOT);
    add_right(prod, TK_SEM);
    add_production(nonterm, prod);

    nonterm = add_nonterminal(gram, GLOBAL_OR_NOT);
    prod = create_production();
    add_right(prod, TK_COLON);
    add_right(prod, TK_GLOBAL);
    add_production(nonterm, prod);
    prod = create_production();
    add_right(prod, EPSILON);
    add_production(nonterm, prod);

    nonterm = add_nonterminal(gram, OTHERSTMTS);
    prod = create_production();
    add_right(prod, STMT);
    add_right(prod, OTHERSTMTS);
    add_production(nonterm, prod);
    prod = create_production();
    add_right(prod, EPSILON);
    add_production(nonterm, prod);

    nonterm = add_nonterminal(gram, STMT);
    prod = create_production();
    add_right(prod, ASSIGNMENTSTMT);
    add_production(nonterm, prod);
    prod = create_production();
    add_right(prod, ITERATIVESTMT);
    add_production(nonterm, prod);
    prod = create_production();
    add_right(prod, CONDITIONALSTMT);
    add_production(nonterm, prod);
    prod = create_production();
    add_right(prod, IOSTMT);
    add_production(nonterm, prod);
    prod = create_production();
    add_right(prod, FUNCALLSTMT);
    add_production(nonterm, prod);

    nonterm = add_nonterminal(gram, ASSIGNMENTSTMT);
    prod = create_production();
    add_right(prod, SINGLEORRECID);
    add_right(prod, TK_ASSIGNOP);
    add_right(prod, ARITHMETICEXPRESSION);
    add_right(prod, TK_SEM);
    add_production(nonterm, prod);

    nonterm = add_nonterminal(gram, SINGLEORRECID);
    prod = create_production();
    add_right(prod, TK_ID);
    add_production(nonterm, prod);
    prod = create_production();
    add_right(prod, CONSTRUCTEDVARIABLE);
    add_production(nonterm, prod);

    nonterm = add_nonterminal(gram, CONSTRUCTEDVARIABLE);
    prod = create_production();
    add_right(prod, TK_ID);
    add_right(prod, ONEEXPANSION);
    add_right(prod, MOREEXPANSIONS);
    add_production(nonterm, prod);

    nonterm = add_nonterminal(gram, ONEEXPANSION);
    prod = create_production();
    add_right(prod, TK_DOT);
    add_right(prod, TK_FIELDID);
    add_production(nonterm, prod);

    nonterm = add_nonterminal(gram, MOREEXPANSIONS);
    prod = create_production();
    add_right(prod, ONEEXPANSION);
    add_right(prod, MOREEXPANSIONS);
    add_production(nonterm, prod);
    prod = create_production();
    add_right(prod, EPSILON);
    add_production(nonterm, prod);

    nonterm = add_nonterminal(gram, SINGLEORRECID);
    prod = create_production();
    add_right(prod, TK_ID);
    add_right(prod, OPTIONSINGLECONSTRUCTED);
    add_production(nonterm, prod);

    nonterm = add_nonterminal(gram, OPTIONSINGLECONSTRUCTED);
    prod = create_production();
    add_right(prod, ONEEXPANSION);
    add_right(prod, MOREEXPANSIONS);
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

    nonterm = add_nonterminal(gram, INPUTPARAMETERS);
    prod = create_production();
    add_right(prod, TK_SQL);
    add_right(prod, IDLIST);
    add_right(prod, TK_SQR);
    add_production(nonterm, prod);

    nonterm = add_nonterminal(gram, ITERATIVESTMT);
    prod = create_production();
    add_right(prod, TK_WHILE);
    add_right(prod, TK_OP);
    add_right(prod, BOOLEANEXPRESSION);
    add_right(prod, TK_CL);
    add_right(prod, STMT);
    add_right(prod, OTHERSTMTS);
    add_right(prod, TK_ENDWHILE);
    add_production(nonterm, prod);

    nonterm = add_nonterminal(gram, CONDITIONALSTMT);
    prod = create_production();
    add_right(prod, TK_IF);
    add_right(prod, BOOLEANEXPRESSION);
    add_right(prod, TK_THEN);
    add_right(prod, STMT);
    add_right(prod, OTHERSTMTS);
    add_right(prod, TK_ELSE);
    add_right(prod, OTHERSTMTS);
    add_right(prod, TK_ENDIF);
    add_production(nonterm, prod);

    nonterm = add_nonterminal(gram, CONDITIONALSTMT);
    prod = create_production();
    add_right(prod, TK_IF);
    add_right(prod, TK_OP);
    add_right(prod, BOOLEANEXPRESSION);
    add_right(prod, TK_CL);
    add_right(prod, TK_THEN);
    add_right(prod, STMT);
    add_right(prod, OTHERSTMTS);
    add_right(prod, ELSEPART);
    add_production(nonterm, prod);

    nonterm = add_nonterminal(gram, ELSEPART);
    prod = create_production();
    add_right(prod, TK_ELSE);
    add_right(prod, STMT);
    add_right(prod, OTHERSTMTS);
    add_right(prod, TK_ENDIF);
    add_production(nonterm, prod);
    prod = create_production();
    add_right(prod, TK_ENDIF);
    add_production(nonterm, prod);

    nonterm = add_nonterminal(gram, IOSTMT);
    prod = create_production();
    add_right(prod, TK_READ);
    add_right(prod, TK_OP);
    add_right(prod, VAR);
    add_right(prod, TK_CL);
    add_right(prod, TK_SEM);
    add_production(nonterm, prod);
    prod = create_production();
    add_right(prod, TK_WRITE);
    add_right(prod, TK_OP);
    add_right(prod, VAR);
    add_right(prod, TK_CL);
    add_right(prod, TK_SEM);
    add_production(nonterm, prod);

    nonterm = add_nonterminal(gram, ARITHMETICEXPRESSION);
    prod = create_production();
    add_right(prod, TERM);
    add_right(prod, EXPPRIME);
    add_production(nonterm, prod);

    nonterm = add_nonterminal(gram, EXPPRIME);
    prod = create_production();
    add_right(prod, LOWPRECEDENCEOPERATORS);
    add_right(prod, TERM);
    add_right(prod, EXPPRIME);
    add_production(nonterm, prod);
    prod = create_production();
    add_right(prod, EPSILON);
    add_production(nonterm, prod);

    nonterm = add_nonterminal(gram, TERM);
    prod = create_production();
    add_right(prod, FACTOR);
    add_right(prod, TERMPRIME);
    add_production(nonterm, prod);

    nonterm = add_nonterminal(gram, TERMPRIME);
    prod = create_production();
    add_right(prod, HIGHPRECEDENCEOPERATORS);
    add_right(prod, FACTOR);
    add_right(prod, TERMPRIME);
    add_production(nonterm, prod);
    prod = create_production();
    add_right(prod, EPSILON);
    add_production(nonterm, prod);

    nonterm = add_nonterminal(gram, FACTOR);
    prod = create_production();
    add_right(prod, TK_OP);
    add_right(prod, ARITHMETICEXPRESSION);
    add_right(prod, TK_CL);
    add_production(nonterm, prod);
    prod = create_production();
    add_right(prod, VAR);
    add_production(nonterm, prod);

    nonterm = add_nonterminal(gram, HIGHPRECEDENCEOPERATORS);
    prod = create_production();
    add_right(prod, TK_MUL);
    add_production(nonterm, prod);
    prod = create_production();
    add_right(prod, TK_DIV);
    add_production(nonterm, prod);

    nonterm = add_nonterminal(gram, LOWPRECEDENCEOPERATORS);
    prod = create_production();
    add_right(prod, TK_PLUS);
    add_production(nonterm, prod);
    prod = create_production();
    add_right(prod, TK_MINUS);
    add_production(nonterm, prod);

    nonterm = add_nonterminal(gram, BOOLEANEXPRESSION);
    prod = create_production();
    add_right(prod, TK_OP);
    add_right(prod, BOOLEANEXPRESSION);
    add_right(prod, TK_CL);
    add_right(prod, LOGICALOP);
    add_right(prod, TK_OP);
    add_right(prod, BOOLEANEXPRESSION);
    add_right(prod, TK_CL);
    add_production(nonterm, prod);

    nonterm = add_nonterminal(gram, BOOLEANEXPRESSION);
    prod = create_production();
    add_right(prod, VAR);
    add_right(prod, RELATIONALOP);
    add_right(prod, VAR);
    add_production(nonterm, prod);

    nonterm = add_nonterminal(gram, BOOLEANEXPRESSION);
    prod = create_production();
    add_right(prod, TK_NOT);
    add_right(prod, TK_OP);
    add_right(prod, BOOLEANEXPRESSION);
    add_right(prod, TK_CL);
    add_production(nonterm, prod);

    nonterm = add_nonterminal(gram, VAR);
    prod = create_production();
    add_right(prod, SINGLEORRECID);
    add_production(nonterm, prod);
    prod = create_production();
    add_right(prod, TK_NUM);
    add_production(nonterm, prod);
    prod = create_production();
    add_right(prod, TK_RNUM);
    add_production(nonterm, prod);

    nonterm = add_nonterminal(gram, LOGICALOP);
    prod = create_production();
    add_right(prod, TK_AND);
    add_production(nonterm, prod);
    prod = create_production();
    add_right(prod, TK_OR);
    add_production(nonterm, prod);

    nonterm = add_nonterminal(gram, RELATIONALOP);
    prod = create_production();
    add_right(prod, TK_LT);
    add_production(nonterm, prod);
    prod = create_production();
    add_right(prod, TK_LE);
    add_production(nonterm, prod);
    prod = create_production();
    add_right(prod, TK_EQ);
    add_production(nonterm, prod);
    prod = create_production();
    add_right(prod, TK_GT);
    add_production(nonterm, prod);
    prod = create_production();
    add_right(prod, TK_GE);
    add_production(nonterm, prod);
    prod = create_production();
    add_right(prod, TK_NE);
    add_production(nonterm, prod);

    nonterm = add_nonterminal(gram, RETURNSTMT);
    prod = create_production();
    add_right(prod, TK_RETURN);
    add_right(prod, OPTIONALRETURN);
    add_right(prod, TK_SEM);
    add_production(nonterm, prod);

    nonterm = add_nonterminal(gram, OPTIONALRETURN);
    prod = create_production();
    add_right(prod, TK_SQL);
    add_right(prod, IDLIST);
    add_right(prod, TK_SQR);
    add_production(nonterm, prod);
    prod = create_production();
    add_right(prod, EPSILON);
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

    nonterm = add_nonterminal(gram, DEFINETYPESTMT);
    prod = create_production();
    add_right(prod, TK_DEFINETYPE);
    add_right(prod, A);
    add_right(prod, TK_RUID);
    add_right(prod, TK_AS);
    add_right(prod, TK_RUID);
    add_production(nonterm, prod);

    nonterm = add_nonterminal(gram, A);
    prod = create_production();
    add_right(prod, TK_RECORD);
    add_production(nonterm, prod);
    prod = create_production();
    add_right(prod, TK_UNION);
    add_production(nonterm, prod);
}