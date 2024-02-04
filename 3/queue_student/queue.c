/**
 * @file queue.c
 * @author John Nguyen <jn866@drexel.edu>
 * @date 2024-01-27
 * @section DESCRIPTION
 * 
 * This file is an implementation of the queue data structure with a function to solve the Josephus problem
 */

#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

/**
 * Create a new empty queue
 * @return pointer to the queue
 */
Queue* newQueue();

/**
 * Add an element at the end of the queue
 * @param v value to add
 * @param Q the queue to add the value to
 */
void enqueue(int v, Queue *Q);

/**
 * Get the value at the front of the queue
 * @param Q the queue to look at
 * @return the first value in the queue or -1 if the queue is empty
 */
int front(Queue *Q);

/**
 * Determine if the queue is empty
 * @param Q the queue to look at
 * @return 1 for True and 0 for False
 */
char isEmpty(Queue *Q);

/**
 * Remove the first value from the queue
 * @param Q the queue to remove from
 */
void dequeue(Queue *Q);

/**
 * Print the queue to STD out
 * @param Q the queue to print
 */
void printQueue(Queue *Q);

/**
 * Solve the Josephus puzzle
 * @param n number of people
 * @param m the m-th person to kill
 */
void josephus(int n, int m);

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

int front(Queue *Q)
{
    if (!isEmpty(Q)){
        return Q->head->value;
    } else {
        return -1;
    }
}

char isEmpty(Queue *Q)
{
    if (Q->head == NULL){
        return 1;
    }
    return 0;
}

void dequeue(Queue *Q)
{
    if (!isEmpty(Q)) {
        Node* temp = Q->head;
        Q->head = Q->head->next;
        free(temp);
    }
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

    // removing people
    int count = 0;
    while (isEmpty(Q) == 0) {
        count++;
        if (count == m) {
            count = 0;
            printf("%d ", front(Q));
            dequeue(Q);
        } else {
            enqueue(front(Q), Q);
            dequeue(Q);
        }
    }
    printf("\n");
}
