#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

//LIFO
typedef struct {
    int top;        //Index of last element in stack
    int item[SIZE]; //Array of elements
} Stack;

Stack* Cnstrct_Stack(void){
    Stack *s = malloc(sizeof(Stack));
    s->top = -1; //Set initial index as -1
    return s;
}

void Dstrct_Stack(Stack *s){
    free(s);
}

void push (Stack *s, int val){
    if (isFull(s) == 1)
        printf("Stack is full!\n");

    else {
        s->top++;
        s->item[s->top] = val; //Adding value
       // printf("%d added to Stack at %d\n", val, s->top);
    }
}

void pop (Stack *s){
    if (isEmpty(s) == 1)
        printf("Stack is empty!\n");

    else {
       // printf("%d at %d is popped from stack\n", s->item[s->top], s->top);
        s->top--;
    }
}

int isEmpty (Stack *s) {
    if (s->top == -1)
        return 1;

    else
        return 0;
}

int isFull (Stack *s) {
    if (s->top == SIZE - 1)
        return 1;
    else
        return 0;
}

int peak(Stack *s){
    return s->item[s->top];
}

void StackDisp (Stack *s) {
    Stack *sCoppy = Cnstrct_Stack();

    //Creating a copy of the stack
    for (size_t i = 0; !isEmpty(s); i++){
        push(sCoppy, peak(s));
        printf("%d\n", peak(s));
        pop(s);
    }

    //Re-filling the stack
    for (size_t i = 0; !isEmpty(sCoppy); i++){
        push(s, peak(sCoppy));
        pop(sCoppy);
    }

    Dstrct_Stack(sCoppy);
}

int countEven (Stack *s) {
    Stack *sCoppy = Cnstrct_Stack();
    int count = 0;

    //creating a copy of the stack
    for (size_t i = 0; !isEmpty(s); i++){
        push(sCoppy, peak(s));
        if ((peak(s)) % 2 == 0){
            count++;
        }
        pop(s);
    }

    // Re-filling the stack
    for (size_t i = 0; !isEmpty(s); i++){
        push(s, peak(sCoppy));
        pop(sCoppy);
    }

    Dstrct_Stack(sCoppy);
    return count;
}

int main()
{
    Stack *s = Cnstrct_Stack();
    push(s, 1);
    push(s, 6);
    push(s, 4);
    push(s, 6);

    //printf("%d\n", countEven(s));

    StackDisp(s);

    Dstrct_Stack(s);
    return 0;
}
