#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "stack.h"


int main(void){
    Stack* s = newStack();
    for(int i=0; i < 200; i++){
        push(s,2*i+1);
    }
    printStack(s);
    while(!isEmpty(s)){
        printf("Current Top %d\n",top(s));
        pop(s);
    }
    deleteStack(s);
    return 0;
}


