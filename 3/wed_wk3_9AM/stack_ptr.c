
#include "stack.h"

struct Node{
    int val;
    struct Node* next;
};
typedef struct Node Node;

struct Stack{
    Node* top;
};
Stack* newStack(){
    Stack* s = malloc(sizeof(Stack));
    s->top = NULL;
    return s;
}
bool isEmpty(Stack* s){
    return s->top == NULL;
}
int top(Stack* s){
    if(isEmpty(s)){return -1;}
    return s->top->val;
}
void push(Stack* s, int val){
    Node* newNode = malloc(sizeof(Node));
    newNode->val = val;
    newNode->next = s->top;
    s->top = newNode;
}
void pop(Stack* s){
    Node* old = s->top;
    s->top = old->next;
    free(old);
}
void deleteStack(Stack* s){
    while(!isEmpty(s)){
        pop(s);
    }
    free(s);
}
void printStack(Stack* s){
    printf("Top of Stack\n");
    Node* current = s->top;
    while(current != NULL){
        printf("%d\n",current->val);
        current = current->next;
    }
    printf("Bottom of Stack\n");
}
