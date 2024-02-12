/**
    @mainpage Binary Search Tree Assignment
    @section Description
 
    This assignment allows the student to implement a traditional binary search tree.
 */
/**
	@file
	@author Mark Boady <mwb33@drexel.edu>
	@date August 2022
	@section DESCRIPTION
 
	Run three different types of tests on the BST
 */

/* MAKE NO CHANGES TO THIS FILE*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bst.h"
#include "heightExp.h"

/**
	Ask user for a list of numbers. Test BST with them.
 */
void inputTest();


/**
	Find Minimum in an Array
	@param A is the array to search
	@param size is the array size
	@return The minimum element in array
 */
int minV(int* A, int size);
/**
	Find Maximum in an Array
	@param A is the array to search
	@param size is the array size
	@return The max element in array
 */
int maxV(int* A, int size);
/**
	Read an integer from stdin. Consumes all characters till newline
	@return Integer read
 */
int readNumber();
/**
	Test file for student BST code
	@param argc not used
	@param argv not used
	@return 0 on success and 1 on bad input
 */
int main(int argc, char** argv){
	/* Set random number generator */
	srand(time(NULL));
	/* Users has two options */
	printf("Select Option:\n");
	printf("1.) Enter Tree Values and print tree.\n");
	printf("2.) Run Height Experiments.\n");
	/* Read the users answer */
	int r=readNumber();
	if(r < 1 || r > 2){
		printf("Bad Input. Try Again.\n");
		return 1;
	}
	if(r==1){
		inputTest();
		return 0;
	}
	if(r==2){
		heightExperiments();
		return 0;
	}
	return 0;
}


/* Get an array of numbers from user. */
/* Insert, Find and Delete All of them. */
void inputTest(){
	/* Ask for Size (assume good input) */
	printf("Enter Number of Values to Test:\n");
	int testSize=readNumber();
	/* read values */
	int* A = malloc(sizeof(int)*testSize);
	for(int i=0; i < testSize;i++){
		printf("Enter A[%d] value:\n",i);
		A[i] = readNumber();
	}
	/* First, make an empty tree */
	BST* B = newBST();
	/* Insert some numbers to make an expected tree */
	for(int i=0; i < testSize; i++){
		insert(B,A[i]);
		printf("Inserted %d into tree\n",A[i]);
		printf("Preorder:\n");
		preorder(B);
		printf("Inorder:\n");
		inorder(B);
		printf("Postorder:\n");
		postorder(B);
	}
	/* Check the height */
	printf("The Tree Height is %d\n",height(B));
	/* Check find */
	int smallest = minV(A,testSize);
	int largest = maxV(A,testSize);
	for(int i=smallest-1; i < largest+1; i++){
		printf("Is %d in the tree?\n",i);
		printf("Answer: %d\n",find(B,i));
	}
	/* Delete the values in order */
	for(int i=0; i < testSize; i++){
		deleteFromTree(B,A[i]);
		printf("Delete %d from tree\n",A[i]);
		printf("Preorder:\n");
		preorder(B);
		printf("Inorder:\n");
		inorder(B);
		printf("Postorder:\n");
		postorder(B);
   }
	/* Clear Memory */
	deleteBST(B);
	return;
}

int minV(int* A, int size){
	int myMin = 9999;
	for(int i=0; i < size; i++){
		if(A[i] < myMin){
			myMin = A[i];
		}
	}
	return myMin;
}

int maxV(int* A, int size){
	int myMax = -9999;
	for(int i=0; i < size; i++){
		if(A[i] > myMax){
			myMax = A[i];
		}
	}
	return myMax;
}

/* Read a number from STDIN */
int readNumber(){
	int number=0;
	char c = getchar();
	while(c!='\n'){
		number = number*10+(c-48);
		c = getchar();
	}
	return number;
}
