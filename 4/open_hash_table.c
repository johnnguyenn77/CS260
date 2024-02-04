#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

// Define Node struct
struct Node {
    char* data;
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
void printHash(OpenHash* h);
void deleteOpenHash(OpenHash* h);
LL* newLinkedList();
void llInsert(LL* l, char* word);
bool llMember(LL* l, char* word);
void printLL(LL* l);
void deleteLinkedList(LL* l);
void normalizeWord(char* word);

OpenHash* newOpenHash(int size){
    OpenHash* h = malloc(sizeof(OpenHash));
    h->size = size;
    h->data = malloc(sizeof(LL*)*size);
    for(int i = 0; i < size; i++){
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

LL* newLinkedList(){
    LL* l = malloc(sizeof(LL));
    l->first = NULL;
    return l;
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

void normalizeWord(char* word) {
    int i = 0, j = 0;
    while (word[i]) {
        if (isalpha(word[i])) { // Check if character is alphabetic
            word[j++] = tolower(word[i]);
        }
        i++;
    }
    word[j] = '\0'; // Null-terminate the word
}

void read_file_insert_words(char* filename, OpenHash* table) {
    FILE* file = fopen(filename, "r");

    char word[100];

    while (fscanf(file, "%s", word) != EOF) {
        normalizeWord(word); 
        if (!member(word, table)) {
            insert(word, table);
        }
    }
    fclose(file);
}

int main() {
    int size;
    char filename[100];

    // Get user inputs
    printf("Enter Size of Hash Table: \n");
    scanf("%d", &size);

    printf("Enter Name of File: \n");
    scanf("%s", filename);
    OpenHash* h = newOpenHash(size);
    read_file_insert_words(filename, h);
    printHash(h);
    deleteOpenHash(h);
    return 1;
}