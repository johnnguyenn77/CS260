/**
	@file
	@author Mark Boady <mwb33@drexel.edu>
	@date July 20, 2022
	@section DESCRIPTION
 
	This code is used to test the sorts.
 */

/* ----DO NOT CHANGE THIS FILE FOR ANY REASON------ */

#ifndef _SORT_TESTS_H_
#define _SORT_TESTS_H_

#include <stdbool.h>

/**
	Run Many Tests on a Sorting Algorithm
 
	@param func is the function to test
	@param size is the size of arrays to test	
	@param numTests is the number of tests to run
	@return True if all tests pass and False otherwise
 */
bool runMultipleTests(void (*func)(int*, int), int size, int numTests);

/**
	Given a sorting algorithm and a size, run 1 test.
	Prints error messages on failure.
 
	@param func is the function to test with
	@param size is the size of the array to test
	@return True if the test fails and False on success
 */
bool testSort(void (*func)(int*, int), int);

/**
	Print An Array when something goes wrong

	@param array is the array to Print
	@param size is the number of elements
 */
void printArray(int* array, int size);

/**
	Copy an array into a new memory location
 
	@param array is the array to copy
	@param size is the number of elements in the array
	@return Pointer to a new array with a copy of all values
 */
int* copyArray(int* array, int size);

/**
	See If An Array is Sorted
 
	@param old is the unsorted array
	@param sorted is the sorted array
	@param size is the size of the arrays
	@return true if the new is sorted version of original and false otherwise
 */
bool isSorted(int* old,int* sorted,int size);

/**
	Check if all elements of an array are in order
 
	@param array is the array
	@param size is the number of elements in the array
	@return true if the array is in order
 */
bool inOrder(int* array, int size);

/**
	Count how many times a value appears in an array
 
	@param array is the array
	@param size is the number of elements
	@param target is the number to look for
	@return How many times target appears in array
 */
int countAppearances(int* array, int size, int target);

/**
	Check if two arrays have the same elements
 
	@param first is the first array
	@param second is the second array
	@param size is the number of elements
	@return 1 if the arrays have all the same elements and 0 otherwise
 */
bool containsSame(int* first, int* second, int size);

#endif
