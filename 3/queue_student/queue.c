#include <stdlib.h>
#include <stdio.h>
#include "queue.h"
#include <stdbool.h>

Queue* newQueue() {
    Queue* q = malloc(sizeof(Queue));
    q->head = 0;
    q->tail = 0;
    return q;
};

char isEmpty(Queue *Q)
{
    if (Q->head == NULL && Q->tail == NULL){
        return 1;
    } else {
        return 0;
    }; 
}

void enqueue(int v, Queue *Q)
{
    Q->tail->next->value = v;
    Q->tail = Q->tail->next;
}

int front(Queue *Q)
{
    if (!isEmpty(Q)){
        return Q->head->value;
    } else {
        return -1;
    };
}

void dequeue(Queue *Q)
{
}

void printQueue(Queue *Q)
{
}

void josephus(int n, int m)
{
}
