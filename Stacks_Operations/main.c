#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10

typedef struct {
    int top;
    int* array;
    int capacity;
} Stack;

Stack* initStack(int size) {
    Stack *s = malloc(sizeof(Stack));
    s->array = malloc(size * sizeof(int));
    s->capacity = size - 1;
    s->top = -1;
    return s;
}

void push(Stack *s, int item) {
    if (isFull_S(s))
        printf("Stack Overflow!\n");

    else {
    (s->top)++;
    s->array[s->top] = item;
   // printf("%d pushed at %d\n", s->array[s->top], s->top);
    }
}

void pop(Stack *s) {
    if (isEmpty_S(s))
        printf("Stack Underflow!!\n");

    else {
      //  printf("%d popped from %d\n", s->array[s->top], s->top);
        (s->top)--;
    }
}

int peak(Stack *s) {
    return s->array[s->top];
}

int isFull_S (Stack *s) {
    return ((s->top) == (s->capacity)) ? 1 : 0;
}

int isEmpty_S (Stack *s) {
    return ((s->top) == -1) ? 1 : 0;
}

void destructS(Stack *s){
    free(s->array);
    free(s);
}

void displaySt(Stack *s) {
    Stack *sCoppy = initStack(SIZE);

    while (!isEmpty_S(s) && !isFull_S(sCoppy)) {
        push(sCoppy, peak(s));
        pop (s);
    }

    while (!isFull_S(s) && !isEmpty_S(sCoppy)) {
        push(s, peak(sCoppy));
        printf("%d ", peak(sCoppy));
        pop(sCoppy);
    }
    printf("\n");

    destructS(sCoppy);
}

//Filling a stack with an array
void fillStack(Stack *s, int *arr, int size) {
    for (size_t i = 0; !isFull_S(s) && i < size; i++){
        push(s, *(arr + i));
    }
}

///Task 1 Reversing a string
char* reverseSt(char* str) {
    Stack* s = initStack(strlen(str) + 1);
    for (size_t i = 0; (*(str + i) != '\0') && (!isFull_S(s)); i++) {
        push(s, *(str + i));
    }

    for (size_t i = 0; (*(str + i) != '\0') && (!isEmpty_S(s)); i++) {
        *(str + i) = peak(s);
        pop(s);
    }

    destructS(s);
    return str;
}

///Task 2 Check Sorting
void checkSort_Stk(Stack *s) {
    Stack *sCoppy = initStack(SIZE);

    int flag = 1;
    int max = peak(s);

     while (!isEmpty_S(s)) {
        push(sCoppy, peak(s));
        if (max < peak(s))
            flag = 0;

        max = peak(s);
        pop(s);
    }

    if (flag != 0)
        printf("Stack is sorted 0_0\n");
    else
        printf("Stack not sorted!\n");

    while (!isFull_S(s) && !isEmpty_S(sCoppy)) {
        push(s, peak(sCoppy));
        pop(sCoppy);
    }

    destructS(sCoppy);
}

///Task 3 Deleting prime numbers
int isPrime(int num) {
    if (num == 2) return 1;
    else if (num < 2) return 0;
    else {
      for (int i = 2; i < (num / 2); i++) {
        if ((num % i) == 0)
            return 0;
      }
      return 1;
    }
}

void deletePrime(Stack *s) {
    Stack *sCoppy = initStack(SIZE);

    while (!isEmpty_S(s)) {
        if (!isPrime(peak(s))) {
            push(sCoppy, peak(s));
            //printf("%d\n", peak(s));
            pop(s);
        }

        else
            pop(s);
    }
    while (!isFull_S(s) && !isEmpty_S(sCoppy)) {
        push(s, peak(sCoppy));
        pop(sCoppy);
    }

    destructS(sCoppy);
}

///Task 4 Merging
Stack *merge(Stack *sMin, Stack *sMax) {
    Stack *sNew = initStack(SIZE * 2);
    Stack *sCopp1 = initStack(SIZE);
    Stack *sCopp2 = initStack(SIZE);
    //Filling copied stacks
    while (!isEmpty_S(sMin)) {
        push(sCopp1, peak(sMin));
        pop(sMin);
    }

    while (!isEmpty_S(sMax)) {
        push(sCopp2, peak(sMax));
        pop(sMax);
    }

    //Comparing and copying
    while (!isEmpty_S(sCopp1) && !isEmpty_S(sCopp2)) {
        if (peak(sCopp1) <= peak(sCopp2)) {
            push(sNew, peak(sCopp1));
            pop(sCopp1);
        }
        else {
            push(sNew, peak(sCopp2));
            pop(sCopp2);
        }
    }

    if (!isEmpty_S(sCopp1)){
        while (!isEmpty_S(sCopp1)) {
            push(sNew, peak(sCopp1));
            pop(sCopp1);
        }
    }
    else if (!isEmpty_S(sCopp2)){
        while (!isEmpty_S(sCopp2)) {
            push(sNew, peak(sCopp2));
            pop(sCopp2);
        }
    }
    //Refilling original stacks
    while (!isEmpty_S(sCopp1)) {
        push(sMin, peak(sCopp1));
        pop(sCopp1);
    }

    while (!isEmpty_S(sCopp2)) {
        push(sMax, peak(sCopp2));
        pop(sCopp2);
    }

    destructS(sCopp1);
    destructS(sCopp2);

    return sNew;
}

int main()
{
    Stack *s = initStack(SIZE);
    Stack *sMin = initStack(SIZE);
    Stack *sMax = initStack(SIZE);
    Stack *merged;

    int arr[] = {10, 25, 44, 788, 8999, 7008, 8888, 1000};
    int sortMin[] = {1, 2, 4, 10};
    int sortMax[] = {1, 3, 5, 12, 20};

    fillStack(s, arr, sizeof(arr) / sizeof(int));
    fillStack(sMin, sortMin, sizeof(sortMin) / sizeof(int));
    fillStack(sMax, sortMax, sizeof(sortMax) / sizeof(int));

    ///Task 1
    char string[] = "Hello world";
    printf("Original String: %s\n", string);
    printf("Reversed String: %s\n\n", reverseSt(string));

    ///Task 2
    printf("\nChecking sort of stack: ");
    displaySt(s);
    checkSort_Stk(s);

    ///Task 3
    printf("\nOriginal Stak: ");
    displaySt(s);
    deletePrime(s);
    printf("Deleted Primes Stack: ");
    displaySt(s);

    ///Task 4
    printf("\nStack 1: ");
    displaySt(sMin);
    printf("Stack 2: ");
    displaySt(sMax);
    printf("Merged Stack: ");
    merged = merge(sMin, sMax);
    displaySt(merged);

    destructS(s);
    return 0;
}
