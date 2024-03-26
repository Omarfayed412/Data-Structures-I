#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node *head, *tail;
} Linkedlist;

Node* init_Node(int item) {
    Node* n = malloc(sizeof(Node));
    n->data = item;
    n->next = NULL;
    return n;
}

Linkedlist* init_List() {
    Linkedlist *list1 = malloc(sizeof(Linkedlist));
    list1->head = NULL;
    list1->tail = NULL;
}

void destruct_List(Linkedlist *l) {
    while (l->head != NULL) {
        free(l->head);
        l->head = l->head->next;
    }
    free(l);
}
//Adding element between two nodes
void insert_bet(Node *prev) {

}
//Adding head
void add_H(Linkedlist *l, int data) {
    Node* n = init_Node(data);
    Node* temp = l->head;
    if (l->head == NULL) {
        l->head = n;
        l->tail = n;
    }
    else {
        l->head = n;
        l->head->next = temp;
    }
}
//Adding tail
void add_T(Linkedlist *l, int data) {
    Node* n = init_Node(data);
    if (l->head == NULL) {
        l->head = n;
        l->tail = n;
    }
    else {
        l->tail->next = n;
        l->tail = n;
    }
}

void delete_H(Linkedlist *l) {
    Node *temp = l->head;
    l->head = l->head->next;
    free(temp);
    temp = NULL;
}

void delete_T(Linkedlist *l) {
    Node *temp = l->head;
    Node *temp2;
    while(temp->next != NULL) {
        temp2 = temp->next;
        if (temp2->next) {
            temp = temp->next;
        }
        else {
            l->tail = temp;
            l->tail->next = NULL;
            free(temp->next);
            break;
        }
    }
}

Node* search(Linkedlist *l, int item) {


}

void display_List(Linkedlist *l) {
    Node* temp = l->head;
    while (temp != NULL) {
        printf("[%d] [%d]\n", temp->data, temp->next, temp);
        temp = temp->next;
    }
    printf("\n");
    free(temp);
}

int main()
{
    Linkedlist *l = init_List();
    add_H(l, 5);
    add_H(l, 8);
    display_List(l);

    add_T(l, 4);
    add_T(l, 6);
    add_T(l, 7);
    display_List(l);

    delete_H(l);
    display_List(l);

    delete_T(l);
    display_List(l);

    delete_T(l);
    display_List(l);

    add_H(l, 88);
    add_T(l, 9898);
    display_List(l);

    destruct_List(l);
    return 0;
}
