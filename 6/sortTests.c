/**
	@file
	@author Mark Boady <mwb33@drexel.edu>
	@date July 20, 2022
	@section DESCRIPTION
 
	Tests for student sorting algorithms
 */
/*	----DO NOT CHANGE THIS FILE FOR ANY REASON------ */

#include "sortTests.h"
#include "stdlib.h"
#include "stdio.h"

/* Run many tests */
bool runMultipleTests(void (*func)(int*, int), int size, int numTests){
	int passed=0;
	for(int i=0; i < numTests; i++){
		passed+=testSort(func,size);
	}
	printf("Passed %d out of %d tests.\n",passed,numTests);
	return (passed==numTests);
}

/* Run a single test */
bool testSort(void (*func)(int*, int), int size){
	/* Make a Random Array */
	int* original = malloc(sizeof(int)*size);
	//Put Random Numbers into the Array
	for(int i=0; i < size; i++){
		original[i] = rand()%(size*4);
	}
	/* Make a Copy to Sort */
	int* after = copyArray(original,size);
	/* Run the sort function */
	func(after,size);
	//Check Sort Worked
	if(!isSorted(original,after,size)){
		printf("SORT FAILED!!\n");
		printf("Array Before Sort:\n");
		printArray(original,size);
		printf("Array After Sort:\n");
		printArray(after,size);
		return false;
	}
	/* Release The Memory */
	free(original);
	free(after);
	/* Success */
	return true;
}

/* Print Out An Array */
void printArray(int* array, int size){
	printf("[");
	for(int i=0; i < size; i++){
		printf("%d",array[i]);
		if(i+1<size){
			printf(", ");
		}
	}
	printf("]\n");
}

/* Copy An Array */
int* copyArray(int* array, int size){
	int* newArray = malloc(size*sizeof(int));
	for(int i=0; i < size; i++){
        newArray[i] = array[i];
	}
	return newArray;
}

/*
 sorted is the sorted version of old if
 it is in order and contains all elements
*/
bool isSorted(int* old, int* sorted, int size){
	/* Elements Must Be In Order */
	if(!inOrder(sorted,size)){
		return false;
	}
	/* All Elements Must Appear in Both Arrays */
	if(!containsSame(old, sorted, size)){
		return false;
	}
	/* Nothing Failed */
	return true;
}

/* Check if all elements are in order */
bool inOrder(int* array, int size){
	for(int i=1; i < size; i++){
		/* Not In Order */
		if(array[i-1] > array[i]){
			return false;
		}
	}
	return true;
}


/*
 For each item, check they appear the same number of times
*/
bool containsSame(int* first, int* second, int size){
	for(int i=0; i < size; i++){
		int left = countAppearances(first,size,first[i]);
		int right = countAppearances(second,size,first[i]);
		/* Some Number Doesn't Match */
		if(left!=right){
			return false;
		}
	}
	/* Everything Matches */
	return true;
}

/* Loop over the array and count appearances of target */
int countAppearances(int* array, int size, int target){
	int count = 0;
	for(int i=0; i < size; i++){
		if(array[i]==target){
			count++;
		}
	}
	return count;
}
