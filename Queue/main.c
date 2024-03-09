#include <stdio.h>
#include <stdlib.h>

//FIFO
//Front used for deletion
//Rear used for addition
//Circular queue for better memory consumption
//Use the mod method to ensure that the rear won't get larger than the capacity
//5%5 = 0

typedef struct {
    int rear, front, count;
    int capacity;
    int* array;
} Queue;

Queue* initQueue (int capacity) {
    Queue* q = malloc(sizeof(Queue));
    q->front = q->count = 0;
    q->capacity = capacity;
    q->rear = q->count;
    q->array = malloc(q->capacity * sizeof(int));
    return q;
}

void destruct (Queue *q) {
    free(q->array);
    free(q);
}

//Addition in the rear
void enqueue(Queue *q, int item){
    if (isFull(q))
        printf("Queue full!\n");
    else {
        //Shift the index to froward unless it's equal to the capacity
        //So it will reverse back
        q->array[q->rear] = item;
        q->rear = (q->rear + 1 ) % (q->capacity);
        q->count ++;
       // printf("%d added to queue at %d\n", item, q->rear - 1);
    }
}

//Deletion from the front
int dequeue (Queue *q) {
    int item = q->array[q->front];
     if (isEmpty(q))
        printf("Queue empty!\n");
    else {
        //printf("%d deleted from queue at %d\n", item, q->front);
        q->front = (q->front + 1) % q->capacity;
        (q->count)--;
        return item;
    }
}

int isFull(Queue *q) {
    if (q->count == q->capacity)
        return 1;
    else
        return 0;
}

int isEmpty(Queue *q) {
    if (q->count == 0)
        return 1;
    else
        return 0;
}

int front (Queue *q) {
    return q->array[q->front];
}

int rear (Queue *q) {
    return q->array[q->rear];
}

void displayQueue (Queue *q) {
    Queue *qC = initQueue(50);
    int temp;
    while (!isEmpty(q)){
        temp = dequeue(q);
        enqueue(qC, temp);
        printf("%d\n", temp);
    }

    while (!isEmpty(qC)){
        temp = dequeue(qC);
        enqueue(q, temp);
    }
    destruct(qC);
}

int main()
{
    Queue* q = initQueue(50);
    enqueue(q, 5);
    enqueue(q, 8);
    enqueue(q, 7);
    displayQueue(q);
    destruct(q);
    return 0;
}
