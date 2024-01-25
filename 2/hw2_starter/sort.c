/**
 * @file sort.c
 * @author John Nguyen <jn866@drexel.edu>
 * @date January 19, 2024
 * @section DESCRIPTION
 * 
 * This program has all of the sorting algorithms that are tested for a homework assignment
 * 
 */

#include<stdlib.h>
#include<stdio.h>

/**
 * This function swap 2 elements in an array 
 * 
 * @param A the array where the elements are
 * @param x index of first element
 * @param y index of second element
 */
void swap(int *A, int x, int y);

/**
 * This is an implementation of the bubble sort algorithm
 * 
 * @param A the array to be sorted
 * @param size size of the array
 */
void bubbleSort(int *A, int size);

/**
 * This is an implementation of the insertion sort algorithm
 * 
 * @param A the array to be sorted
 * @param size size of the array
 */
void insertSort(int *A, int size);

/**
 * This function merges 2 arrays together
 * 
 * @param A the array to merge
 * @param start the first index
 * @param middle the middle index
 * @param stop the last index
 */
void merge(int *A, int start, int middle, int stop);

/**
 * This is a helper function for the merge sort function
 * 
 * @param A the array to sort
 * @param start the first index to sort
 * @param stop the last index to sort
 */
void msort(int *A, int start, int stop);

/**
 * This is a implementation of the merge sort algorithm
 * 
 * @param A the array to sort
 * @param size the size of the array
 */
void mergeSort(int *A, int size);

/**
 * This is the partition for quicksort
 * 
 * @param A the array to partition
 * @param start the first index to use
 * @param stop the last index to use
 * @return the index of te partition element
 */
int partition(int *A, int start, int stop);

/**
 * This is a recursive helper function for quicksort
 * 
 * @param A the array to sort
 * @param start the first index to sort
 * @param stop the last index to sort
 */
void qusort(int *A, int start, int stop);

/**
 * This is an implementation of the quick sort algorithm
 * 
 * @param A the array to be sorted
 * @param size the size of the array
 */
void quickSort(int *A, int size);

void swap(int *A, int x, int y)
{
    int temp = A[x];
    A[x] = A[y];
    A[y] = temp;
}

void bubbleSort(int *A, int size) {
    int swapped;
    for (int i = 0; i < size - 1; i++) {
        swapped = 0;
        for(int j = 0; j < size - i - 1; j++) {
            if(A[j] > A[j+1]) {
                swap(A, j, j+1);
                swapped = 1;
            }
        }

        if (swapped == 0) {
            break;
        }
    }
};

void insertSort(int *A, int size) {
    int i = 1;
    while (i < size) {
        while(i > 0 && A[i] < A[i-1]) {
            swap(A, i, i-1);
            i--;
        }
        i++;
    }
}

void merge(int *A, int start, int middle, int stop) {
    int sizePart1 = 1+(middle -start);
    int sizePart2 = 1+(stop - (middle + 1));
    int Part1[sizePart1];
    int Part2[sizePart2];
    for (int i = 0; i < sizePart1; i++) {
        Part1[i] = A[start+i];
    }
    for (int i = 0; i < sizePart2; i++) {
        Part2[i] = A[middle+1+i];
    }

    int i = 0;
    int j = 0;
    for (int k = start; k <= stop; k++) {
        if (i >= sizePart1) {
            A[k] = Part2[j];
            j++;
        } else if (j >= sizePart2) {
            A[k] = Part1[i];
            i++;
        } else if (Part1[i] < Part2[j]) {
            A[k] = Part1[i];
            i++;
        } else {
            A[k] = Part2[j];
            j++;
        }
    }
};

void msort(int *A, int start, int stop) {
    if(start >= stop) {
        return;
    }
    int middle = start + (stop-start)/2;
    msort(A, start, middle);
    msort(A, middle + 1, stop);
    merge(A, start, middle, stop);
};

void mergeSort(int *A, int size) {
    int start = 0;
    int stop = size - 1;
    msort(A, start, stop);
};

int partition(int *A, int start, int stop) {
    int pivot = A[stop];
    int i = start;
    int j = start;
    while (i < stop) {
        if (A[i] < pivot) {
            swap(A, i, j);
            j++;
        }
        i++;
    }
    int temp = A[i];
    A[i] = A[j];
    A[j] = temp;
    return j;
};

void qusort(int *A, int start, int stop) {
    if (start >= stop) {
        return;
    }
    int p = partition(A, start, stop);
    qusort(A, start, p-1);
    qusort(A, p+1, stop);
};

void quickSort(int *A, int size) {
    int start = 0;
    int stop = size - 1;
    qusort(A, start, stop);
};
