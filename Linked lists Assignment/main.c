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
    if (l->head == NULL) printf("\nERROR: List is empty\n");
    else {
        Node *temp;
        temp = l->head;
        l->head = temp->next;
        destruct_N(temp);
        temp = NULL;
    }
}

void deleteEnd(LinkedList *l) {
    if (l->head == NULL) printf("\nERROR: List is empty\n");
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
Node *search(LinkedList *l, int key) {
    Node *temp = l->head;
    while (temp != NULL) {
        if (temp->data == key) {
            printf("%d found at @%p\n", key, temp);
            return temp;
        }
        else
            temp = temp->next;
    }
    printf("%d is not found in this list\n", key);
    return NULL;
}

///Task 2
void insert(LinkedList *l, int index, int item) {
    Node *temp1 = l->head;
    int size = 0;
    while (temp1 != NULL) {
        size++;
        temp1 = temp1->next;
    }

    if (index < 0 || index > size) printf("\nERROR: Index out of range\n");
    else if (index == 0) insertBegin(l, item);
    else if (index == size) insertEnd(l, item);
    else {
        Node *n = init_N(item);
        Node *temp2;
        temp1 = l->head;
        int count = 0;
        while (count < index - 1) {
            temp1 = temp1->next;
            count++;
        }
        temp2 = temp1->next;
        temp1->next = n;
        n->next = temp2;
    }
}

///Task 3
int identical(LinkedList *l1, LinkedList *l2) {
    Node *temp1 = l1->head;
    Node *temp2 = l2->head;
    while (temp1 != NULL && temp2 != NULL) {
        if (temp1->data != temp2->data) {
            printf("The two lists aren't identical!\n");
            return 0;
        }
        temp1 = temp1->next;
        temp2 = temp2->next;
    }
    if (temp1 != NULL || temp2 != NULL) {
        printf("The two lists aren't identical!\n");
        return 0;
    }
    printf("The two lists are identical\n");
    return 1;
}

///Task 4
//Comparing each element from the two lists
//If one of the elements is smaller insert it at
//the end of the list ad increment the pointer to next node
//The loop exits when one of the pointers = NULL
//so one of the lists might be still not empty
//check again for each list and insert all the elements in the non-empty list
LinkedList *merge(LinkedList *l1, LinkedList *l2) {
    LinkedList *newll = init_LL();
    Node *temp1 = l1->head;
    Node *temp2 = l2->head;
    while (temp1 != NULL && temp2 != NULL) {
        if (temp1->data < temp2->data) {
            insertEnd(newll, temp1->data);
            temp1 = temp1->next;
        }
        else if (temp1->data == temp2->data) {
            insertEnd(newll, temp1->data);
            insertEnd(newll, temp2->data);
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
        else {
            insertEnd(newll, temp2->data);
            temp2 = temp2->next;
        }
    }
    if (temp1 != NULL) {
        while (temp1 != NULL) {
            insertEnd(newll, temp1->data);
            temp1 = temp1->next;
        }
    }
    else if (temp2 != NULL) {
        while (temp2 != NULL) {
            insertEnd(newll, temp2->data);
            temp2 = temp2->next;
        }
    }

    return newll;
}

///Task 5
LinkedList *intersection(LinkedList *l1, LinkedList *l2) {
    LinkedList *intersect = init_LL();
    Node *temp1 = l1->head;
    Node *temp2 = l2->head;
    while (temp1 != NULL) {
        temp2 = l2->head;
        while (temp2 != NULL) {
            if (temp1->data == temp2->data) {
                insertEnd(intersect, temp1->data);
                break;
            }
            temp2 = temp2->next;
        }
        temp1 = temp1->next;
    }
    return intersect;
}

int main()
{
    LinkedList *l1 = init_LL();
    LinkedList *l2 = init_LL();
    int arr1[] = {2, 4, 5, 8, 9, 10, 12};
    int arr2[] = {1, 5, 7, 8, 11, 12 ,15};

    fillArray_LL_E(l1, arr1, sizeof(arr1) / 4);
    fillArray_LL_E(l2, arr2, sizeof(arr2) / 4);
    printf("Original List: ");
    display_LL(l1);
    ///Task 1
    int key =  9;
    printf("\n1) ...Searching for %d ...\n", key);
    search(l1, key);

    ///Task 2
    int index = 4;
    printf("\n2)Adding %d at index %d : ", key, index);
    insert(l1, index, key);
    display_LL(l1);

    ///Task 3
    printf("\n3)List 1: ");
    display_LL(l1);
    printf("  List 2: ");
    display_LL(l2);
    identical(l1, l2);

    ///Task 4
    printf("\n4)Merging list 1:");
    display_LL(l1);
    printf("With list 2:");
    display_LL(l2);
    LinkedList *merged = merge(l1, l2);
    printf("New merged list: ");
    display_LL(merged);

    ///Task 5
    printf("\n5)The intersection between \nList 1: ");
    display_LL(l1);
    printf("List 2: ");
    display_LL(l2);
    LinkedList *intersect = intersection(l1, l2);
    display_LL(intersect);

    destruct_LL(l1);
    destruct_LL(l2);
    return 0;
}
