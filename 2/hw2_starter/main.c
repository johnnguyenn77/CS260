/**
		@mainpage Sorting Races
		@section DESCRIPTION

		Race four classic sorting algorithms to see which is fastest.
 */
/**
		@file
		@author Mark Boady <mwb33@drexel.edu>
		@date July 20, 2022
		@section DESCRIPTION

		This program tests sorting algorithms for a homework assignment.

		----DO NOT CHANGE THIS FILE FOR ANY REASON----
 */

#include "stdio.h"
#include "stdlib.h"
#include "time.h"

/* Local Libraries */
#include "sort.h"
#include "sortTests.h"

/*
  This Enum Type is used to easily select
  from the menu
*/
enum TestType { timings = 0, bubble = 1, insert = 2, merges = 3, quick = 4 };
/*  Give the type a short name to use later */
typedef enum TestType TestType;

/**
		Decide what experiment to run

		@return Enum of TestType with what to do
 */
TestType decideType();

/**
		Ask the user about how to test a single sort

		@param func is the function to test
		@return 1 if passed and 0 for failed
 */
char testASort(void (*func)(int *, int));

/**
		Make a Table of Sorts and their timings
 */
void timeAllSorts();

/**
		Time a single sort

		@param func is the function to time
		@param size is the size of the array to time
		@return time taken by the test in seconds
 */
double timeASingleSort(void (*func)(int *, int), int size);

/**
		Main Asks the User What to Test using STDIN

		@param argc is not used
		@param argv is not used
		@return is always 0
 */
int main(int argc, char **argv) {
  /* Prepare the Random Number Generator */
  srand(time(NULL));
  /* Ask What Test to Run */
  TestType option = decideType();
  /* Run the Correct Test */
  switch (option) {
  case timings:
	printf("Running Timings.\n");
	timeAllSorts();
	break;
  case bubble:
	printf("Testing Bubble Sort\n");
	testASort(bubbleSort);
	break;
  case insert:
	printf("Testing Insertion Sort\n");
	testASort(insertSort);
	break;
  case merges:
	printf("Testing Merge Sort\n");
	testASort(mergeSort);
	break;
  case quick:
	printf("Testing Quick Sort\n");
	testASort(quickSort);
	break;
  default:
	printf("Unknown Command Given\n");
	break;
  }
  return 0;
}

/* Ask the user what type of test to run */
TestType decideType() {
  printf("Select Which Test to Run:\n");
  printf("0.) Time All Algorithms\n");
  printf("1.) Test Bubble Sort\n");
  printf("2.) Test Insertion Sort\n");
  printf("3.) Test Merge Sort\n");
  printf("4.) Test Quick Sort\n");
  int result;
  int success = scanf("%d", &result);
  /* Ask Again On Bad Inputs */
  if (!success || result < 0 || result > 5) {
	printf("Invalid Option Given.\n");
	return decideType();
  }
  return result;
}

/* Ask user for size and number of tests */
char testASort(void (*func)(int *, int)) {
  printf("Enter Size of Arrays to Test:\n");
  int size;
  int worked = scanf("%d", &size);
  /* Read Failed */
  if (!worked) {
	printf("Could Not Read Input\n");
	return 0;
  }
  /* Get Num Tests */
  printf("Enter Number of Tests to Run:\n");
  int tests;
  worked = scanf("%d", &tests);
  /* Read Failed */
  if (!worked) {
	printf("Could Not Read Input\n");
	return 0;
  }
  /* Run the tests! */
  return runMultipleTests(func, size, tests);
}

/*
  Generate Table of Sorts
  Goal:
  | Size | Gnome | Bubble | Insert | Merge | Quick |
  ....
*/
void timeAllSorts() {
  /* Title Column */
  printf("All Times in milliseconds.\n");
  printf("| %7s | %10s | %10s | %10s | %10s |\n", "Size", "Bubble", "Insert",
		 "Merge", "Quick");
  /* Run Tests */
  int size = 8;
  while (size <= 131072) {
	/* Generate 1 Row */
	double b = timeASingleSort(bubbleSort, size);
	double i = timeASingleSort(insertSort, size);
	double m = timeASingleSort(mergeSort, size);
	double q = timeASingleSort(quickSort, size);
	/* Print Results */
	printf("| %7d | %10.4f | %10.4f | %10.4f | %10.4f |\n", size, b, i, m, q);
	/* Get Read for next row */
	size = size * 2;
  }
}

/* Collect Timings for a single sort */
double timeASingleSort(void (*func)(int *, int), int size) {
  /* Make a Random Array */
  int *T = malloc(size * sizeof(int));
  /* Put in Numbers */
  for (int i = 0; i < size; i++) {
	T[i] = rand() % (size * 4);
  }
  double before = (double)clock();
  func(T, size);
  double after = (double)clock();
  /* Release Memory */
  free(T);
  return (after - before) / (CLOCKS_PER_SEC / 1000);
}
