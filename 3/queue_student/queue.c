#include <stdlib.h>
#include <stdio.h>
#include "queue.h"
#include <stdbool.h>

Queue* newQueue() {
    Queue* q = malloc(sizeof(Queue));
    q->tail = NULL;
    q->head = NULL;
    //q->head->next = q->tail;
    return q;
};

void enqueue(int v, Queue *Q)
{
    Node* newNode = malloc(sizeof(Node));
    newNode->value = v;
    if (isEmpty) {
        Q->head = newNode;
        Q->tail = newNode;
    } else {
        Q->tail->next = newNode;
        Q->tail = newNode;
    }
}

char isEmpty(Queue *Q)
{
    if (Q->head == NULL){
        return 1;
    }
    return 0;
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
