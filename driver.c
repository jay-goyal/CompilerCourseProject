/*
GROUP 20
VAIBHAV SINGLA - 2021A7PS2227P
JAY GOYAL - 2021A7PS2418P
SANJEEV MALLICK - 2021A7PS2217P
TRAYAMBAK SHRIVASTAVA - 2021A7PS1629P
PRANAV TANNA - 2021A7PS2685P
ARYAN BANSAL - 2021A7PS2776P
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "grammar.h"
#include "hash_table.h"
#include "helper.h"
#include "lexer.h"
#include "lexerDef.h"
#include "parser.h"

int main(int argc, char* argv[]) {
    // Check for the number of arguments
    if (argc != 3) {
        printf("Invalid number of arguments. Expected 3 got %d\n", argc);
        exit(-1);
    }

    // Check if the input file exists
    if (access(argv[1], F_OK) == -1) {
        printf(ANSI_COLOR_RED ANSI_COLOR_BOLD
               "File %s does not exist\n" ANSI_COLOR_RESET,
               argv[1]);
        exit(-1);
    }

    // Create Symbol Table

    // Print Status of Submission
    printf(
        ANSI_COLOR_BLUE ANSI_COLOR_BOLD
        "\n"
        "---------------------------------------------------------------------"
        "\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_BLUE ANSI_COLOR_BOLD
           "IMPLEMENTATION STATUS:\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_BLUE ANSI_COLOR_BOLD
           "FIRST and FOLLOW Sets automatically computed\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_BLUE ANSI_COLOR_BOLD
           "Both Lexical and Syntax Analysis modules "
           "developed\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_BLUE ANSI_COLOR_BOLD
           "Parse Tree can be generated\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_BLUE ANSI_COLOR_BOLD
           "Error Reporting done " ANSI_COLOR_RED
           "but errors may deviate from ones specified\n" ANSI_COLOR_RESET);
    printf(
        ANSI_COLOR_BLUE ANSI_COLOR_BOLD
        "---------------------------------------------------------------------"
        "\n\n" ANSI_COLOR_RESET);

    // Determine the operation to be performed
    int op;
take_input:
    printf("Input the Operation:\n");
    scanf("%d", &op);
    printf("\n\n");

    switch (op) {
        // Exit
        case 0: {
            printf(ANSI_COLOR_GREEN ANSI_COLOR_BOLD
                   "Exit Requested. Bye\n\n" ANSI_COLOR_RESET);
            return 0;
        }

        // Remove Comments
        case 1: {
            removeComments(argv[1]);
            goto take_input;
        }

        // Lexical Analysis
        case 2: {
            ht_t* symbol_table = create_hash_table();
            populate_symbol_table(symbol_table);
            tokeninfo_t ret_token;
            bool err_flag = false;
            do {
                ret_token = getNextToken(argv[1], symbol_table, 0);
                if (ret_token.token_type < -2) err_flag = true;
            } while (ret_token.token_type != -1);
            if (err_flag)
                printf(ANSI_COLOR_RED ANSI_COLOR_BOLD
                       "\n\nLexical Errors Reported\n\n" ANSI_COLOR_RESET);
            else
                printf(ANSI_COLOR_GREEN ANSI_COLOR_BOLD
                       "\n\nLexical Analysis Finished. No Errors "
                       "Reported\n\n" ANSI_COLOR_RESET);
            free_hashtable(symbol_table);
            goto take_input;
        }

        // Lexical, Syntax Analysis and Print Parse Tree
        case 3: {
            ht_t* symbol_table = create_hash_table();
            populate_symbol_table(symbol_table);

            gram_t* gram = create_grammar();

            set_t** first_sets = computeFirstSets(gram);

            set_t** follow_sets = comuteFollowSets(gram, first_sets);

            pt_t pt = createParseTable(gram, first_sets, follow_sets);

            tree_t* parse_tree =
                parseInputSourceCode(pt, argv[1], symbol_table);
            printParseTree(parse_tree, argv[2]);

            free_hashtable(symbol_table);
            clear_grammar(gram);
            clear_parse_table(pt);
            clear_sets(first_sets);
            clear_sets(follow_sets);
            clear_tree(parse_tree);
            goto take_input;
        }

        // Time the Lexical, Syntax Analysis and Print Parse Tree
        case 4: {
            ht_t* symbol_table = create_hash_table();
            populate_symbol_table(symbol_table);

            gram_t* gram = create_grammar();

            set_t** first_sets = computeFirstSets(gram);

            set_t** follow_sets = comuteFollowSets(gram, first_sets);

            pt_t pt = createParseTable(gram, first_sets, follow_sets);

            clock_t start_time, end_time;
            double total_cpu_time, total_cpu_time_in_seconds;
            start_time = clock();

            tree_t* parse_tree =
                parseInputSourceCode(pt, argv[1], symbol_table);

            end_time = clock();
            total_cpu_time = (double)(end_time - start_time);
            total_cpu_time_in_seconds = total_cpu_time / CLOCKS_PER_SEC;

            printParseTree(parse_tree, argv[2]);
            printf(ANSI_COLOR_GREEN ANSI_COLOR_BOLD
                   "\n"
                   "-----------------------------------------------------------"
                   "----------"
                   "\n" ANSI_COLOR_RESET);
            printf(ANSI_COLOR_GREEN ANSI_COLOR_BOLD
                   "Total CPU Time: %f\n" ANSI_COLOR_RESET,
                   total_cpu_time);
            printf(ANSI_COLOR_GREEN ANSI_COLOR_BOLD
                   "Total CPU Time in Seconds: %f\n" ANSI_COLOR_RESET,
                   total_cpu_time_in_seconds);
            printf(ANSI_COLOR_GREEN ANSI_COLOR_BOLD
                   "-----------------------------------------------------------"
                   "----------"
                   "\n\n" ANSI_COLOR_RESET);

            free_hashtable(symbol_table);
            clear_grammar(gram);
            clear_parse_table(pt);
            clear_sets(first_sets);
            clear_sets(follow_sets);
            clear_tree(parse_tree);
            goto take_input;
        }

        // Take input again for invalid input
        default: {
            printf("Invalid Input\n");
            goto take_input;
        }
    }

    return 0;
}
