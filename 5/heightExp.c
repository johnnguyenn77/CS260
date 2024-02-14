/**
 * @file heightExp.c
 * @author John Nguyen (jn866@drexel.edu)
 * @date 2024-02-14
 * @section DESCRIPTION
 * 
 * This file contains the implementation of the heightExperiment function for the height experiments.
 */

#include <stdlib.h>
#include <stdio.h>
#include "heightExp.h"
#include "bst.h"

void heightExperiments() {
    printf("Experiments (N=Number Element, Table Shows Height)\n");
    printf("|   N  |   T1  |   T2  |   T3  |   T4  |   T5  |  Average |\n");
    printf("| ---- | ----- | ----- | ----- | ----- | ----- | -------- |\n");

    float sum;

    for (int i = 2; i <= 1024; i = i*2) {
        sum = 0;
        printf("| %5d", i);
        for (int j = 0; j < 5; j++) {
            BST* bst = newBST();
            for (int k = 0; k < i; k++) {
                int target = rand();
                insert(bst, target);
            }
            sum += height(bst);
            printf("| %6d", height(bst));
            deleteBST(bst);
        }
        printf("| %9.2f|\n", sum/5);
    }
}