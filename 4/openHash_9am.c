#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct OpenHash;
typedef struct OpenHash OpenHash;
struct Node;
typedef struct Node Node;
struct LL;
typedef struct LL LL;

OpenHash* newOpenHash(int size);
void printHash(OpenHash* h);
int hash(int val, int size);
void insert(OpenHash* h, int val);
bool member(OpenHash* h, int val);
void deleteOpenHash(OpenHash* h);

LL* newLinkedList();
void printLL(LL* l);
void llInsert(LL* l, int val);
bool llMember(LL* l, int val);
void deleteLinkedList(LL* l);

int main(void){
    OpenHash* h = newOpenHash(6);
    insert(h,86);
    insert(h,83);
    insert(h,59);
    insert(h,19);
    insert(h,8);
    insert(h,81);
    printHash(h);
    for(int i=0; i < 100; i++){
        if(member(h,i)){
            printf("Found %d\n",i);
        }
    }
    deleteOpenHash(h);
    return 1;
}

struct OpenHash{
    LL** data;
    int size;
};
struct LL{
    Node* first;
};
struct Node{
    int val;
    Node* next;
};

OpenHash* newOpenHash(int size){
    OpenHash* h = malloc(sizeof(OpenHash));
    h->size = size;
    h->data = malloc(sizeof(LL*)*size);
    for(int i=0; i < size; i++){
        h->data[i] = newLinkedList();
    }
    return h;
}
int hash(int val, int size){
    return val%size;
}
void insert(OpenHash* h, int val){
    if(member(h,val)){return;}
    int pos = hash(val,h->size);
    llInsert(h->data[pos],val);
}
bool member(OpenHash* h, int val){
    int pos = hash(val,h->size);
    return llMember(h->data[pos],val);
}
void printHash(OpenHash* h){
    printf("Start of Hash Table.\n");
    printf("Size: %d\n",h->size);
    for(int i=0; i < h->size; i++){
        printf("h->data[%d]=",i);
        printLL(h->data[i]);
        printf("\n");
    }
    printf("End Of Hash Table.\n");
}
void deleteOpenHash(OpenHash* h){
    for(int i=0; i<h->size; i++){
        deleteLinkedList(h->data[i]);
    }
    free(h->data);
    free(h);
}

LL* newLinkedList(){
    LL* l = malloc(sizeof(LL));
    l->first = NULL;
    return l;
}
void llInsert(LL* l, int val){
    Node* newNode = malloc(sizeof(Node));
    newNode->val = val;
    newNode->next = l->first;
    l->first = newNode;
}
bool llMember(LL* l, int val){
    Node* current = l->first;
    while(current != NULL){
        if(current->val == val){
            return true;
        }
        current = current->next;
    }
    return false;
}
void printLL(LL* l){
    printf("[");
    Node* current = l->first;
    while(current != NULL){
        printf("%d",current->val);
        if(current->next!=NULL){printf(", ");}
        current = current->next;
    }
    printf("]");
}
void deleteLinkedList(LL* l){
    Node* current = l->first;
    while(current!=NULL){
        Node* next = current->next;
        free(current);
        current = next;
    }
    free(l);
}
