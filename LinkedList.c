/*
GROUP 20
VAIBHAV SINGLA - 2021A7PS2227P
JAY GOYAL - 2021A7PS2418P
SANJEEV MALLICK - 2021A7PS2217P
TRAYAMBAK SHRIVASTAVA - 2021A7PS1629P
PRANAV TANNA - 2021A7PS2685P
ARYAN BANSAL - 2021A7PS2776P
*/

#include "LinkedList.h"

#include <stdio.h>
#include <stdlib.h>

// create a new node
node_t* make_node(stentry_t* key) {
    node_t* temp = (node_t*)calloc(1, sizeof(node_t));
    if (temp == NULL) {
        printf("Mem Alloc failed");
    }
    temp->key = key;
    temp->next = NULL;
    return temp;
}

// insert a new node at the end of the list
node_t* insert_tail_node(node_t* head, stentry_t* key) {
    node_t* tail = make_node(key);

    if (head == NULL) {
        head = tail;
        return tail;
    }
    node_t* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = tail;
    return tail;
}

// delete the last node in the list
void delete_tail_node(node_t* head) {
    if (head == NULL) {
        return;
    }
    if (head->next == NULL) {
        free(head);
        head = NULL;
        return;
    }
    node_t* temp = head;
    while (temp->next->next != NULL) {
        temp = temp->next;
    }
    free(temp->next);
    temp->next = NULL;
}

// delete the entire list
void delete_list(node_t* head) {
    if (head == NULL) {
        return;
    }

    node_t* temp = head;
    while (temp != NULL) {
        node_t* next = temp->next;
        if (temp->key->lexeme != NULL) free(temp->key->lexeme);
        free(temp->key);
        free(temp);
        temp = next;
    }
}
