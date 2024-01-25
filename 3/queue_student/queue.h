/**
		@file
		@author Mark Boady <mwb33@drexel.edu>
		@date 2022-2023
		@section DESCRIPTION

		This is the header file for a classic queue data structure.
		It includes the Queue Structure and all methods needed.
 */

/*-----You May NOT change this file-----*/

#ifndef _QUEUE_H_
#define _QUEUE_H_

/**
		A structure to represent a single node in a one directional linked list.
 */
struct Node {
  int value;         /**< The value stored at this node. */
  struct Node *next; /**< A pointer to the next node in the list. */
};
// Give the struct a short name
typedef struct Node Node;

/**
		A structure to represent a classic Queue.
 */
struct Queue {
  Node *head; /**< Pointer to the first value in queue. */
  Node *tail; /**< Pointer to last value in the queue. */
};
// Give the Queue a short name
typedef struct Queue Queue;

/**
		Create a new empty queue.
		@return A pointer to the new queue struct
*/
Queue *newQueue();

/**
		Determine if the queue is empty
		@param Q is the queue to check
		@return 1 for True and 0 for false
 */
char isEmpty(Queue *Q);

/**
		Add a new value to the end of the queue
		@param v is the value to add
		@param Q is the Q to add the value to
 */
void enqueue(int v, Queue *Q);

/**
		Determine the value at the front of the queue
		@param Q is the queue to look at
		@return The first value in the queue or -1 if the queue is empty
 */
int front(Queue *Q);

/**
		Remove the first value from the queue
		@param Q is the queue to remove from
 */
void dequeue(Queue *Q);

/**
		Print the Queue to STD out. Used for debugging.
		@param Q is the queue to print
 */
void printQueue(Queue *Q);

/**
 Solve the Josephus Puzzle Using a Queue. Print out the people in the order
 killed. Josephus sits in the last position printed.
 @param n is the number of people
 @param m is the m-th person to kill, m=2 means kill every other person
 */
void josephus(int n, int m);

#endif
