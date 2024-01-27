#include <stdlib.h>
#include <stdio.h>
#include "queue.h"
#include <stdbool.h>

Queue* newQueue() {
    Queue* q = malloc(sizeof(Queue));
    q->tail = NULL;
    q->head = NULL;
    return q;
};

void enqueue(int v, Queue *Q)
{
    Node* newNode = malloc(sizeof(Node));
    newNode->value = v;
    newNode->next = NULL;
    if (isEmpty(Q) == 1) {
        Q->head = newNode;
        Q->tail = newNode;
    } else {
        Q->tail->next = newNode;
        Q->tail = Q->tail->next;
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
    Q->head = Q->head->next;
}

void printQueue(Queue *Q)
{
    struct Node *ptr = Q->head;
    while (ptr != NULL) {
        printf("%d ", ptr->value);
        ptr = ptr->next;
    }
    printf("\n");
}

void josephus(int n, int m)
{
    // create queue
    struct Queue *Q = newQueue();
    for (int i = 0; i < n; i++) {
	    enqueue(i, Q);
    }

    struct Queue *k = newQueue();

    enqueue(0, Q);

    // killing people
    struct Node *ptr = Q->head;
    int count = 0;
    while (isEmpty(Q) == 0) {
        if (count == m-1) {
            count = 0;
            enqueue(ptr->value, k);
            printf("%d ", ptr->value);
            dequeue(Q);
            ptr=ptr->next;
        } else {
            ptr = ptr->next;
            count++;
            enqueue(ptr->next->value, Q);
        }   
    }
    printQueue(k);
}
