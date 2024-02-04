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

int hash(char* word, int n);

bool member(char* word, OpenHash* table);

void insert(char* word, OpenHash *table);

struct OpenHash{
    LL** data;
    int size;
};
struct LL{
    Node* first;
};
struct Node{
    char* data;
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

int hash(char* word, int n) {
    int total = 0;
    for(int i=0; word[i] != 0; i++) {
        char c = word[i];
        total = total + (int) c;
        total = total *101;
        total = total%n;
    }
    return total;
}

bool member(char* word, OpenHash* table){
    int pos = hash(word, table->size);
    return llMember(table->data[pos], word);
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

void llInsert(LL* l, char* word){
    Node* newNode = malloc(sizeof(Node));
    newNode->data = word;
    newNode->next = l->first;
    l->first = newNode;
}

bool llMember(LL* l, char* word){
    Node* current = l->first;
    while(current != NULL){
        if(current->data == word){
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
        printf("%d",current->data);
        if(current->next!=NULL){printf(", ");}
        current = current->next;
    }
    printf("]");
}

void deleteLinkedList(LL* l) {
    Node* current = l->first;
    while(current!=NULL){
        Node* next = current->next;
        free(current);
        current = next;
    }
    free(l);
}