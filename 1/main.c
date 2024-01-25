#include <stdlib.h>
#include <stdio.h>

/**
 * @mainpage CS 260 - Homework 1
 * @section Description
 * 
 * The program will guess a value from 0 to 100 from inputs from the user
 * 
 */

/**
 * @file
 * @author John Nguyen <jn866@drexel.edu>
 * @date January 20, 2024
 * @section DESCRIPTION
 * 
 * The file contains the main function and a function to generate an array of integers from 0 to 100
*/

/**
 This function generates an array of integers from 0 to 100.
 @return pointer to the array of numbers from 0 to 100
 */
int* arrayFrom0to100();

int main() {
    int start = 0;
    int stop = 100;
    int middle;
    char input;
    int* numbers = arrayFrom0to100();

    printf("Think of a number between 0 and 100.\nResponses:\nh or H means Higher\nl or L means Lower\ny or Y means yes this is the correct number\n");

    while (1) {
        middle = start + (stop-start)/2;
        printf("Is your number %d?\n", numbers[middle]);

        scanf(" %c", &input);

        if(input == 'y' || input == 'Y'){
            printf("Thank you for playing.\n");
            break; 
        }
        if(input == 'l' || input == 'L'){
            stop = middle - 1;
        }
        if(input == 'h' || input == 'H'){
            start = middle + 1;
        }
    }
    return 0;
}

int* arrayFrom0to100(){
    int* A = malloc(sizeof(int)*101);
    for(int i=0; i < 101; i++){
        A[i] = i;
    }
    return A;
}