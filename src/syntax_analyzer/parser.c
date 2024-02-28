#include "parser.h"

pt_t create_parse_table(gram_t *gram, set_t **first_sets, set_t **follow_sets) {
    pt_t pt;
    pt.table = (prod_t ***) calloc(NUM_NONTERMINALS, sizeof(prod_t **));

    for(int i=0; i<NUM_NONTERMINALS; i++) {
        // include epsilon and $ in the table
        pt.table[i] = (prod_t **) calloc(NUM_TERMINALS+2, sizeof(prod_t *));
        for(int j=0; j<NUM_TERMINALS+2; j++) {
            pt.table[i][j] = NULL;
        }
    }

    for(int i=0; i<NUM_NONTERMINALS; i++) {
        int num_prod = gram->nonterminals[i]->num_prod;
        for(int k=0; k<num_prod; k++) {
            // each terminal in First(alpha)
            int num_right = gram->nonterminals[i]->productions[k]->num_right;
            bool flag = 0;
            for(int l=0; l<num_right; l++) {
                int right = gram->nonterminals[i]->productions[k]->right[l];
                if(right == -1) {
                    for(int m=1; m<=NUM_TERMINALS+1; m++) {
                        if(follow_sets[i]->term[m] == 1) {
                            pt.table[i][m] = gram->nonterminals[i]->productions[k];
                        }
                    }
                    flag = 1;
                    // break;
                }
                else if(right < NUM_TERMINALS) {
                    pt.table[i][right+1] = gram->nonterminals[i]->productions[k];
                    flag = 1;
                    break;
                }
                else if(right >= NUM_TERMINALS) {
                    for(int j=1; j<=NUM_TERMINALS; j++) {
                        if(first_sets[right-NUM_TERMINALS]->term[j] == 1) {
                            pt.table[i][j] = gram->nonterminals[i]->productions[k];
                        }
                    }
                    if(first_sets[right-NUM_TERMINALS]->term[0] == 0) {
                        flag = 1;
                        break;
                    }
                }
            }
            // epsilon in first set
            if(!flag) {
                for(int l=1; l<=NUM_TERMINALS+1; l++) {
                    if(follow_sets[i]->term[l] == 1) {
                        pt.table[i][l] = gram->nonterminals[i]->productions[num_prod-1];
                    }
                }
            }
        }
    }

    for(int i=0; i<NUM_NONTERMINALS; i++) {
        for(int j=1; j<=NUM_TERMINALS+1; j++) {
            if(pt.table[i][j] != NULL) {
                printf("-------------NONTERMINAL %s-------------\n", non_terminals[i]);
                printf("TERMINAL %s \n", token_str[j-1]);
                    int num_right = pt.table[i][j]->num_right;
                    printf("%s -> ", non_terminals[i]);
                    for(int l=0; l<num_right; l++) {
                        int right = pt.table[i][j]->right[l];
                        if(right == -1)
                            printf("EPSILON ");
                        else if(right <= NUM_TERMINALS)
                            printf("%s ", token_str[right]);
                        else
                            printf("%s ", non_terminals[right-NUM_TERMINALS]);
                    }
                    printf("\n");
                printf("\n");
            }
        }
    }

    return pt;
}