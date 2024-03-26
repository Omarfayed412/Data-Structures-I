#include <stdio.h>
#include <stdlib.h>

typedef struct {
    struct Node *prev, *next;
    int data;
} Node;

typedef struct {
    Node *head, *tail;
} DLL;

Node* constructNode(int data) {
    Node *n = malloc(sizeof(Node));
    n->prev = n->next = NULL;
    n->data = data;
    return n;
}

void destructNode( ) {

}

DLL *initDLL(void) {
    DLL *ll = malloc(sizeof(DLL));
    ll->head = ll->tail = NULL;
    return ll;
}

void insertBegining(DLL *ll, int item) {
    Node *n = constructNode(item);
    if (ll->head == NULL) {
        ll->head = ll->tail = n;
    }
    else {
        (ll->head)->prev = n;
        n->next = ll->head;
        ll->head = n;
    }
}

void insertEnd(DLL *ll, int item) {
    Node *newNode = constructNode(item);
    if (ll->head == NULL) {
        ll->head = ll->tail = newNode;
    }
    else {
        (ll->tail)->next = newNode;
        newNode->prev = ll->tail;
        ll->tail = newNode;
    }
}


void deinitDLL (DLL *ll) {
    while(ll->head != NULL) {
        free(ll->head);
        ll->head = (ll->head)->next;
        (ll->head)->prev = NULL;
    }
    free(ll);
}

void displayReverse(DLL *ll) {
    Node *temp = ll->tail;
    if (ll->head == NULL) return ;
    else if (ll->head == ll->tail) {
        printf("%d ", ll->head->data);
        return ;
    }
    else {
        while(temp->prev != NULL) {
            printf("%d ", temp->data);
            temp = temp->prev;
        }
    }
    printf("\n");
}


int main()
{
    DLL *ll = initDLL();
    insertBegining(ll, 5);
    insertBegining(ll, 6);
    displayReverse(ll);
    return 0;
}
