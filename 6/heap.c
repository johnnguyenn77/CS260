#include "heap.h"

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
    return -1; // or handle error as you see fit
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

void upheap(Heap* myHeap, int i) {
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
        // handle error or resize array
        return;
    }

    myHeap->currentSize++;
    int i = myHeap->currentSize - 1;
    myHeap->data[i] = x;

    upheap(myHeap, i);
}

void deletemin(Heap* myHeap) {
    if (empty(myHeap)) {
        // handle error
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
