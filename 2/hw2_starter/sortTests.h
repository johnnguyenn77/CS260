/**
		@file
		@author Mark Boady <mwb33@drexel.edu>
		@date July 20, 2022
		@section DESCRIPTION

		This code is used to test the sorts.

		----DO NOT CHANGE THIS FILE FOR ANY REASON------
 */

#ifndef _SORT_TESTS_H_
#define _SORT_TESTS_H_

/**
		Run Many Tests on a Sorting Algorithm

		@param func is the function to test
		@param size is the size of arrays to test
		@param numTests is the number of tests to run
		@return 1 if all tests pass and 0 otherwise
 */
char runMultipleTests(void (*func)(int *, int), int size, int numTests);

/**
		Given a sorting algorithm and a size, run 1 test.
		Prints error messages on failure.

		@param func is the function to test with
		@param size is the size of the array to test
		@return 0 if the test fails and 1 on success
 */
char testSort(void (*func)(int *, int), int);

/**
		Print An Array when something goes wrong

		@param A is the array to Print
		@param size is the number of elements
 */
void printArray(int *A, int size);

/**
		Copy an array into a new memory location

		@param A is the array to copy
		@param size is the number of elements in the array
		@return Pointer to a new array with a copy of all values
 */
int *copyArray(int *A, int size);

/**
		See If An Array is Sorted

		@param old is the unsorted array
		@param sorted is the sorted array
		@param size is the size of the arrays
		@return 1 if the new is sorted version of original and 0 otherwise
 */
char isSorted(int *old, int *sorted, int size);

/**
		Check if all elements of an array are in order

		@param A is the array
		@param size is the number of elements in the array
		@return 1 if the array is in order
 */
char inOrder(int *A, int size);

/**
		Count how many times a value appears in an array

		@param A is the array
		@param size is the number of elements
		@param target is the number to look for
		@return How many times target appears in A
 */
int countAppearances(int *A, int size, int target);

/**
		Check if two arrays have the same elements

		@param A is the first array
		@param B is the second array
		@param size is the number of elements
		@return 1 if the arrays have all the same elements and 0 otherwise
 */
char containsSame(int *A, int *B, int size);

#endif
