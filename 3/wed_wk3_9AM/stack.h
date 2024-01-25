#ifndef _STACK_H_

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
//Abstract Data Type
//How it is *used*
struct Stack;
typedef struct Stack Stack;
Stack* newStack();
//Add to the top
void push(Stack* s, int val);
//Delete the top
void pop(Stack* s);
//Ask what is on top
int top(Stack* s);
//Is it empty
bool isEmpty(Stack* s);
//How do you delete
void deleteStack(Stack* s);
//Print me!
void printStack(Stack* s);

#endif
