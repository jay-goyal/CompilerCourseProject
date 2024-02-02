#include <stdlib.h>

struct Node {
    int val;
    struct Node* next;
};

struct Node* makeNode(int val){
    struct Node* temp=(struct Node*)malloc(sizeof(struct Node));
    if(temp==NULL){
        printf("Mem Alloc failed");
    }
    temp->val=val;
    temp->next=NULL;
    return temp;
}

void insert_tail_node(struct Node* head, int val){
    struct Node* tail=makeNode(val);

    if(head==NULL){
        head=tail;
        return;
    }
    struct Node* temp=head;
    while(temp->next != NULL){
        temp=temp->next;
    }
    temp->next=tail;
}

void delete_tail_node(struct Node* head){
    if(head==NULL){
        return;
    }
    if(head->next==NULL){
        free(head);
        head=NULL;
        return;
    }
    struct Node* temp=head;
    while(temp->next->next != NULL){
        temp=temp->next;

    }
    free(temp->next);
    temp->next=NULL;
}
