#include <stdio.h>
#include <stdlib.h>
#define SIZE 10
//FIFO
//Add from rear
//Delete from front

///Code for stack used in task 4 and 5
typedef struct {
    int top;
    int* array;
    int capacity;
} Stack;

Stack* init_S(int size) {
    Stack *s = malloc(sizeof(Stack));
    s->array = malloc(size * sizeof(int));
    s->capacity = size - 1;
    s->top = -1;
    return s;
}

void push(Stack *s, int item) {
    if (isFull_S(s))
        printf("\nERROR: Stack Overflow!\n");

    else {
    (s->top)++;
    s->array[s->top] = item;
   // printf("%d pushed at %d\n", s->array[s->top], s->top);
    }
}

void pop(Stack *s) {
    if (isEmpty_S(s))
        printf("\nERROR: Stack Underflow!!\n");

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

void destruct_S(Stack *s){
    free(s->array);
    free(s);
}

void display_S(Stack *s) {
    Stack *sCoppy = init_S(SIZE);

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

    destruct_S(sCoppy);
}
///End of stack code


///Start of Queue code
typedef struct {
    int front, rear, count, capacity;
    int *items;
} Queue;

Queue* init_Q(int size) {
    Queue *q = malloc(sizeof(Queue));
    q->items = malloc(size * sizeof(int));
    q->count = q->front = 0;
    q->capacity = size;
    q->rear = 0;
    return q;
}

void enqueue(Queue *q, int data) {
    if (isFull_Q(q))
        printf("ERROR: Overflow!\n");
    else {
        (q->count)++;
        q->items[q->rear] = data;
        //printf("%d added from rear\n", q->items[q->rear]);
        q->rear = (q->rear + 1) % q->capacity; //Circular queue
    }
}

int dequeue(Queue *q) {
    if (isEmpty_Q(q))
        printf("\nERROR: Underflow!\n");
    else {
        int num = q->items[q->front];
       // printf("%d removed from front at %d\n", num, q->front);
        q->front = (q->front + 1) % q->capacity;
        q->count--;
        return num;
    }
}

void destruct_Q(Queue *q) {
    free(q->items);
    free(q);
}

int isEmpty_Q(Queue *q) {
    if (q->count == 0)
        return 1;
    else
        return 0;
}

int isFull_Q(Queue *q) {
    if (q->count == q->capacity)
        return 1;
    else
        return 0;
}

int qSize(Queue *q) {
    return q->count;
}

void fill_Q(Queue *q, int *arr, size_t size) {
    for (size_t i = 0; (!isFull_Q(q)) && (i < size); i++) {
        enqueue(q, *(arr + i));
    }
}

void display_Q(Queue *q) {
    Queue *qCoppy = init_Q(qSize(q));
    int num;
    while (!isEmpty_Q(q) && !isFull_Q(qCoppy)) {
        num = dequeue(q);
        enqueue(qCoppy, num);
        printf("%d ", num);
    }

    while (!isEmpty_Q(qCoppy) && !isFull_Q(q)) {
        enqueue(q, dequeue(qCoppy));
    }
    printf("\n");
    destruct_Q(qCoppy);
}

///Task 1
int getMax_Q(Queue *q) {
    Queue *qCoppy = init_Q(qSize(q));
    int max = dequeue(q);
    int temp;
    enqueue(qCoppy, max);
    while (!isEmpty_Q(q)) {
        temp = dequeue(q);
        enqueue(qCoppy, temp);
        if (max < temp) {
            max = temp;
        }
    }

    while (!isEmpty_Q(qCoppy)) {
        enqueue(q, dequeue(qCoppy));
    }

    destruct_Q(qCoppy);
    return max;
}

///Task 2
void swapFirstLast_Q(Queue *q) {
    int first = dequeue(q);
    Queue *qCoppy = init_Q(qSize(q) - 1);
    while (qSize(q) - 1) { //Stop at the last item
        enqueue(qCoppy, dequeue(q));
    }
    //The last element is the only element in original queue
    //So it will be the first element
    while (qSize(qCoppy)) {
        enqueue(q, dequeue(qCoppy));
    }
    enqueue(q, first);

    destruct_Q(qCoppy);
}

///Task 3
void insert_Q(Queue *q, int value, int index) {
    if (isFull_Q(q)) printf("\nERROR: Queue Overflow!\n");

    else if (index > (qSize(q))) printf("\nERROR: Index out of range!\n");

    else {
        int count = 0;
        Queue *qCoppy = init_Q(qSize(q) + 1);
        while (count < index){ //Stop at the intended index
            enqueue(qCoppy, dequeue(q));
            count++;
        }
        //add the element in the second queue
        enqueue(qCoppy, value);
        //Complete filling the rest of the elements
        while (!isEmpty_Q(q)) {
            enqueue(qCoppy, dequeue(q));
        }

        while (!isEmpty_Q(qCoppy)) {
            enqueue(q, dequeue(qCoppy));
        }

        destruct_Q(qCoppy);
    }
}

///Task 4
void reverseOdd_Q(Queue *q) {
    Queue *oddQ = init_Q(qSize(q));
    Queue *qCoppy = init_Q(qSize(q));

    int temp;

    while (!isEmpty_Q(q)) {
        temp = dequeue(q);
        if (temp % 2 == 0) {
            enqueue(qCoppy, temp);
        }
        else {
            enqueue(qCoppy, temp);
            enqueue(oddQ, temp);
        }
    }

    //Reverse the odd queue using stack
    Stack *oddS = init_S(qSize(oddQ));
    while (!isEmpty_Q(oddQ)) {
        push(oddS, dequeue(oddQ));
    }
    while (!isEmpty_S(oddS)) {
        enqueue(oddQ, peak(oddS));
        pop(oddS);
    }

    while (!isEmpty_Q(qCoppy)) {
        temp = dequeue(qCoppy);
        if (temp % 2 == 0)
            enqueue(q, temp);
        else
            enqueue(q, dequeue(oddQ));
    }

    destruct_S(oddS);
    destruct_Q(oddQ);
    destruct_Q(qCoppy);
}

///Task 5
void reverse_Q(Queue *q, int k) {
    if (k > qSize(q)) printf("\nERROR: Size greater than queue!\n");
    else {
        Queue *qCoppy = init_Q(qSize(q));
        Stack *sCoppy = init_S(k);
        int count = 0;
        //Selecting first K elements and placing them in stack
        while (count++ < k) {
            push(sCoppy, dequeue(q));
        }
        //placing the elements in stack in another queue so that they are reversed
        while (!isEmpty_S(sCoppy)) {
            enqueue(qCoppy, peak(sCoppy));
            pop(sCoppy);
        }
        //Copping the rest of the elements in queue
        while (!isEmpty_Q(q)) enqueue(qCoppy, dequeue(q));
        //Re-filling the original queue with the intended order
        while (!isEmpty_Q(qCoppy)) enqueue(q, dequeue(qCoppy));
        destruct_S(sCoppy);
        destruct_Q(qCoppy);
    }
}

int main()
{
    int arr[] = {10, 7, 1, 1,100, 5, 66};

    Queue *q = init_Q(SIZE);
    fill_Q(q, arr, sizeof(arr) / sizeof(int));
    printf("Queue: ");
    display_Q(q);

    ///Task 1
    printf("\n1)%d is the maximum element in queue\n", getMax_Q(q));

    ///Task 2
    printf("\n2)Swapping first & last: ");
    swapFirstLast_Q(q);
    display_Q(q);

    ///task 3
    printf("\n3)Adding %d at index %d : ", 15, 5);
    insert_Q(q, 15, 5);
    display_Q(q);

    ///Task 4
    printf("\n4)Reversing odd numbers: ");
    reverseOdd_Q(q);
    display_Q(q);

    ///Task 5
    printf("\n5)Reversing first %d elements: ", 4);
    reverse_Q(q, 4);
    display_Q(q);

    destruct_Q(q);
    return 0;
}
