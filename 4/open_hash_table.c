#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Define Node struct
struct Node {
    char* data; // Change to char pointer to store strings
    struct Node* next;
};

// Define LinkedList struct
struct LL {
    struct Node* first;
};

// Define OpenHash struct
struct OpenHash {
    struct LL** data;
    int size;
};

// Typedef structs for convenience
typedef struct OpenHash OpenHash;
typedef struct Node Node;
typedef struct LL LL;

// Function declarations
OpenHash* newOpenHash(int size);
int hash(char* word, int n);
bool member(char* word, OpenHash* table);
void insert(char* word, OpenHash* table);
LL* newLinkedList();
void printHash(OpenHash* h);
void deleteOpenHash(OpenHash* h);
void llInsert(LL* l, char* word);
bool llMember(LL* l, char* word);
void printLL(LL* l);
void deleteLinkedList(LL* l);

OpenHash* newOpenHash(int size){
    OpenHash* h = malloc(sizeof(OpenHash));
    h->size = size;
    h->data = malloc(sizeof(LL*)*size);
    for(int i = 0; i < size; i++){
        h->data[i] = newLinkedList();
    }
    return h;
}

LL* newLinkedList(){
    LL* l = malloc(sizeof(LL));
    l->first = NULL;
    return l;
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

void insert(char* word, OpenHash* table){
    if(member(word, table)){return; }
    int pos = hash(word, table->size);
    llInsert(table->data[pos], word);
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
    for(int i=0; i < h->size; i++){
        deleteLinkedList(h->data[i]);
    }
    free(h->data);
    free(h);
}

void llInsert(LL* l, char* word){
    Node* newNode = malloc(sizeof(Node));
    newNode->data = strdup(word);
    newNode->next = l->first;
    l->first = newNode;
}

bool llMember(LL* l, char* word){
    Node* current = l->first;
    while(current != NULL){
        if(strcmp(current->data, word) == 0) {
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
        printf("%s",current->data);
        if(current->next!=NULL){printf(", ");}
        current = current->next;
    }
    printf("]");
}

void deleteLinkedList(LL* l) {
    Node* current = l->first;
    while(current != NULL){
        Node* next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
    free(l);
}

int main(void) {
    OpenHash* h = newOpenHash(6);
    insert("ab", h);
    insert("bv", h);
    insert("cv", h);
    insert("qwe", h);
    insert("sdf", h);
    insert("bsq", h);
    printHash(h);
    deleteOpenHash(h);
    return 1;
}