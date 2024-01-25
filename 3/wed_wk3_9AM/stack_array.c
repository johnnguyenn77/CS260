
#include "stack.h"

#include "stack.h"
struct Stack{
    int* data;
    int size;
    int maxSize;
};
Stack* newStack(){
    Stack* s = malloc(sizeof(Stack));
    s->size = 0;
    s->maxSize = 10;
    s->data = malloc(s->maxSize*sizeof(int));
    return s;
}
void deleteStack(Stack* s){
    free(s->data);
    free(s);
}
void push(Stack* s, int val){
    //We might need to resize
    if(s->size == s->maxSize){
        int newSize = (s->maxSize)*2;
        int* newData = malloc(newSize*sizeof(int));
        printf("I need to resize from %d to %d\n",s->size,newSize);
        for(int i=0; i < s->size; i++){
            newData[i] = s->data[i];
        }
        free(s->data);
        s->data = newData;
        s->maxSize = newSize;
    }
    int pos = s->size;
    s->data[pos] = val;
    s->size++;
}
void pop(Stack* s){
    if(isEmpty(s)){
        return;
    }
    s->size--;
    if(s->size > 10 && s->size < s->maxSize/2){
        int newSize = s->maxSize/2;
        printf("Resize Down %d\n",newSize);
        int* newData = malloc(newSize*sizeof(int));
        for(int i=0; i < s->size; i++){
            newData[i] = s->data[i];
        }
        free(s->data);
        s->data = newData;
        s->maxSize = newSize;
    }
}
//Ask what is on top
int top(Stack* s){
    if(!isEmpty(s)){
        return s->data[s->size-1];
    }
    return -1;
}
//Is it empty
bool isEmpty(Stack* s){
    return s->size==0;
}
void printStack(Stack* s){
    printf("Stack Top\n");
    for(int i=s->size-1; i >= 0; i--){
        printf("%d\n",s->data[i]);
    }
    printf("Stack Bottom\n");
}

