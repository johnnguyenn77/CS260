/**
		@file
		@author Mark Boady <mwb33@drexel.edu>
		@date July 20, 2022
		@section DESCRIPTION

		This file contains 4 sorting algorithms.

		The 4 functions are defined but not implemented.
		Your task is to implement them in the sort.c file.

		You may ADD new functions to this file BUT
		you may not REMOVE anything from this file.
 */

#ifndef _SORT_H_
#define _SORT_H_

/**
 * Swap 2 elements in an array
 * 
 * @param ptr1 is the pointer to the first element
 * @param ptr2 is the pointer to the second element
 */
void swap(int* ptr1, int* ptr2);

/**
		Implement Bubble Sort Based on Lecture

		@param A is the array to sort
		@param size is the number of elements in the array
 */
void bubbleSort(int *A, int size);

/**
		Implement Insertion Sort Based on Lecture

		@param A is the array to sort
		@param size is the number of elements in the array
 */
void insertSort(int *A, int size);

/**
		Implement Merge Sort Based on Lecture

		@param A is the array to sort
		@param size is the number of elements in the array
 */
void mergeSort(int *A, int size);

/**
		Recursive Helper Function for Merge Sort

		@param A is the array to sort
		@param start is the first index to sort
		@param stop is the last index to sort
 */
void msort(int *A, int start, int stop);

/**
		Merge Function for Merge Sort

		@param A is the array to Merge
		@param start is the first index
		@param middle is the middle index
		@param stop is the last index
 */
void merge(int *A, int start, int middle, int stop);

/**
		Implement Quick Sort Based on Lecture

		@param A is the array to sort
		@param size is the number of elements
 */
void quickSort(int *A, int size);

/**
		Recursive Helper Function for Quick Sort

		@param A is the array to sort
		@param start is the first index to sort
		@param stop is the last index to sort
 */
void qusort(int *A, int start, int stop);

/**
		Partition for Quick Sort
		Use Randomized Index Selection Here
		You may assume srand has already been set in main.c

		@param A is the array to Partition
		@param start is the first index to use
		@param stop is the last index to use
		@return The index of the partition element
 */
int partition(int *A, int start, int stop);

#endif
