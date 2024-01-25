/**
		@file
		@author Mark Boady <mwb33@drexel.edu>
		@date July 20, 2022
		@section DESCRIPTION

		Tests for student sorting algorithms

		----DO NOT CHANGE THIS FILE FOR ANY REASON------
 */

#include "sortTests.h"
#include "stdio.h"
#include "stdlib.h"

/* Run many tests */
char runMultipleTests(void (*func)(int *, int), int size, int numTests) {
  int passed = 0;
  for (int i = 0; i < numTests; i++) {
	passed += testSort(func, size);
  }
  printf("Passed %d out of %d tests.\n", passed, numTests);
  return (passed == numTests);
}

/* Run a single test */
char testSort(void (*func)(int *, int), int size) {
  /* Make a Random Array */
  int *Original = malloc(sizeof(int) * size);
  /* Put Random Numbers into the Array */
  for (int i = 0; i < size; i++) {
	Original[i] = rand() % (size * 4);
  }
  /* Make a Copy to Sort */
  int *After = copyArray(Original, size);
  /* Run the sort function */
  func(After, size);
  /* Check Sort Worked */
  if (!isSorted(Original, After, size)) {
	printf("SORT FAILED!!\n");
	printf("Array Before Sort:\n");
	printArray(Original, size);
	printf("Array After Sort:\n");
	printArray(After, size);
	return 0;
  }
  /* Release The Memory */
  free(Original);
  free(After);
  /* Success */
  return 1;
}

/* Print Out An Array */
void printArray(int *A, int size) {
  printf("[");
  for (int i = 0; i < size; i++) {
	printf("%d", A[i]);
	if (i + 1 < size) {
	  printf(", ");
	}
  }
  printf("]\n");
}

/* Copy An Array */
int *copyArray(int *A, int size) {
  int *T = malloc(size * sizeof(int));
  for (int i = 0; i < size; i++) {
	T[i] = A[i];
  }
  return T;
}

/*
  sorted is the sorted version of old if
  it is in order and contains all elements
*/
char isSorted(int *old, int *sorted, int size) {
  /* Elements Must Be In Order */
  if (!inOrder(sorted, size)) {
	return 0;
  }
  /* All Elements Must Appear in Both Arrays */
  if (!containsSame(old, sorted, size)) {
	return 0;
  }
  /* Nothing Failed */
  return 1;
}

/* Check if all elements are in order */
char inOrder(int *A, int size) {
  for (int i = 1; i < size; i++) {
	/* Not In Order */
	if (A[i - 1] > A[i]) {
	  return 0;
	}
  }
  return 1;
}

/*
  For each item, check they appear the same number
  of times
*/
char containsSame(int *A, int *B, int size) {
  for (int i = 0; i < size; i++) {
	int left = countAppearances(A, size, A[i]);
	int right = countAppearances(B, size, A[i]);
	/* Some Number Doesn't Match */
	if (left != right) {
	  return 0;
	}
  }
  /* Everything Matches */
  return 1;
}

/* Loop over the array and count appearances of target */
int countAppearances(int *A, int size, int target) {
  int count = 0;
  for (int i = 0; i < size; i++) {
	if (A[i] == target) {
	  count++;
	}
  }
  return count;
}
