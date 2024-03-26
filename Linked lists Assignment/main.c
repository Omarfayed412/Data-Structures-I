#include <stdio.h>
#include <stdlib.h>

typedef struct {
    struct Node *next;
    int data;
} Node;

typedef struct {
    Node *head, *tail;
} LinkedList;

LinkedList *init_LL(void) {
    LinkedList *l = malloc(sizeof(LinkedList));
    l->head = l->tail = NULL;
    return l;
}

Node *init_N(int data) {
    Node *n = malloc(sizeof(Node));\
    n->data = data;
    n->next = NULL;
    return n;
}

void destruct_LL(LinkedList *l) {
    while (l->head != NULL) {
        destruct_N(l->head);
        l->head = l->head->next;
    }
    free(l);
    l = NULL;
}

void destruct_N(Node *n) {
    n->next = NULL;
    free(n);
    n = NULL;
}

//Acts like push in Stack
void insertBegin(LinkedList *l, int item) {
    Node *n = init_N(item);
    //Checking if the list is empty
    if (l->head == NULL)
        l->head = l->tail = n;
    else {
        n->next = l->head;
        l->head = n;
    }
}
//Acts like enqueue in Queue
void insertEnd(LinkedList *l, int item) {
    Node *n = init_N(item);
    if (l->head == NULL)
        l->head = l->tail = n;
    else {
        l->tail->next = n;
        l->tail = n;
    }
}

void deleteBegin(LinkedList *l) {
    if (l->head == NULL) printf("ERROR: List is empty\n");
    else {
        Node *temp;
        temp = l->head;
        l->head = temp->next;
        destruct_N(temp);
        temp = NULL;
    }
}

void deleteEnd(LinkedList *l) {
    if (l->head == NULL) printf("ERROR: List is empty\n");
    else {
        Node *temp1 = l->head;
        Node *temp2;
        while (temp1->next != NULL) {
            temp2 = temp1;
            temp1 = temp1->next;
        }
        l->tail = temp2;
        l->tail->next = NULL;
        destruct_N(temp1);
        temp1 = NULL;
    }
}

void display_LL(LinkedList *l) {
    Node *temp = l->head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}
//Filling a list from an array by adding elements from rear
void fillArray_LL_E(LinkedList *l, int *arr, size_t size) {
    for (size_t i = 0; i < size; i++) {
        insertEnd(l, *(arr + i));
    }
}

//Filling list from an array by adding elements from front
void fillArray_LL_B(LinkedList *l, int *arr, size_t size) {
    for (size_t i = 0; i < size; i++) {
        insertBegin(l, *(arr + i));
    }
}

///Task 1

int main()
{
    LinkedList *l = init_LL();
    int arr[] = {5, 6, 7, 8};
    fillArray_LL_E(l, arr, sizeof(arr)/4);
    display_LL(l);
    deleteBegin(l);
    deleteBegin(l);
    display_LL(l);
    return 0;
}
