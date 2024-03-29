/**
 * @file heap.c
 * @author John Nguyen (jn866@drexel.edu)
 * @date 2024-02-27
 * @section DESCRIPTION
 * 
 * This file contains an implementation of heaps and heap sort.
 */

#include "heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 Implement Heap Sort using the heap data structure.
 
 @param array is the array to sort
 @param size is the number of elements in the array
 */
void heapSort(int* array, int size);

/**
 Create a new empty Heap
 @return A pointer to the new heap
 */
Heap* makenull(int capacity);

/**
 Free all memory used by the heap
 @param myHeap is the heap to free
 */
void deleteHeap(Heap* myHeap);

/**
 Ask if the heap is currently empty
 @param myHeap is a pointer to the heap
 @return true if empty and false otherwise
 */
bool empty(Heap* myHeap);

/**
 What is the smallest value in the heap?
 @param myHeap is the heap to find min of
 @return The smallest value in the heap
 */
int min(Heap* myHeap);

/**
 Delete the minimum from the heap
 @param myHeap is the heap to delete from
 */
void deletemin(Heap* myHeap);

/**
 Downheap starting at the node at index i
 @param myHeap is the heap to modify
 @param i is the index to start from
 */
void downheap(Heap* myHeap, int i);

/**
 Insert value x into the Heap
 @param x is the value to insert
 @param myHeap is the heap to insert into
 */
void insert(int x, Heap* myHeap);

/**
 Upheap starting at node indexed to i
 @param myHeap is the heap to fix
 @param i is the index of the node to start upheaping at
 */
void upheap(struct Heap* myHeap,int i);

/**
 What is the index of node n's parent?
 @param n is the child node's index
 @return n's parent's index
 */
int parent(int n);

/**
 What index contains the left child of n?
 @param n is the index of the parent
 @return the index of the left child of n
 */
int leftChild(int n);

/**
 What index contains the right child of n?
 @param n is the index of the parent
 @return the index of the right child of n
 */
int rightChild(int n);

/**
 Swap the values at indexes i and j in the heap.
 @param myHeap is the heap to modify
 @param i is the first index to swap
 @param j is the second index to swap with
 */
void swap(Heap* myHeap, int i, int j);

/**
 This function prints the heap and will help you debug.
 @param myHeap is the heap to print
 */
void printHeap(Heap* myHeap);

Heap* makenull(int capacity) {
    Heap* heap = malloc(sizeof(Heap));
    heap->data = malloc(sizeof(int) * capacity);
    heap->maxSize = capacity;
    heap->currentSize = 0;
    return heap;
}

void deleteHeap(Heap* myHeap) {
    free(myHeap->data);
    free(myHeap);
}

bool empty(Heap* myHeap) {
    return myHeap->currentSize == 0;
}

int min(Heap* myHeap) {
    if (!empty(myHeap)) {
        return myHeap->data[0];
    }
    return -1;
}

void swap(Heap* myHeap, int i, int j) {
    int temp = myHeap->data[i];
    myHeap->data[i] = myHeap->data[j];
    myHeap->data[j] = temp;
}

int parent(int n) {
    return (n - 1) / 2;
}

int leftChild(int n) {
    return 2 * n + 1;
}

int rightChild(int n) {
    return 2 * n + 2;
}

void upheap(Heap* myHeap,int i) {
    while (i != 0 && myHeap->data[parent(i)] > myHeap->data[i]) {
        swap(myHeap, i, parent(i));
        i = parent(i);
    }
}

void downheap(Heap* myHeap, int i) {
    int smallest = i;
    int left = leftChild(i);
    int right = rightChild(i);

    if (left < myHeap->currentSize && myHeap->data[left] < myHeap->data[smallest])
        smallest = left;

    if (right < myHeap->currentSize && myHeap->data[right] < myHeap->data[smallest])
        smallest = right;

    if (smallest != i) {
        swap(myHeap, i, smallest);
        downheap(myHeap, smallest);
    }
}

void insert(int x, Heap* myHeap) {
    if (myHeap->currentSize == myHeap->maxSize) {
        return;
    }

    myHeap->currentSize++;
    int i = myHeap->currentSize - 1;
    myHeap->data[i] = x;

    upheap(myHeap, i);
}

void deletemin(Heap* myHeap) {
    if (empty(myHeap)) {
        return;
    }

    myHeap->data[0] = myHeap->data[myHeap->currentSize - 1];
    myHeap->currentSize--;
    downheap(myHeap, 0);
}

void heapSort(int* array, int size) {
    Heap* myHeap = makenull(size);
    for (int i = 0; i < size; ++i) {
        insert(array[i], myHeap);
    }

    for (int i = 0; i < size; ++i) {
        array[i] = min(myHeap);
        deletemin(myHeap);
    }

    deleteHeap(myHeap);
}

void printHeap(Heap* myHeap) {
    for (int i = 0; i < myHeap->currentSize; ++i) {
        printf("%d ", myHeap->data[i]);
    }
    printf("\n");
}
