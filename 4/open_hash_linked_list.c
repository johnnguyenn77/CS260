#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

struct Node {
    char* data;
    struct Node* next;
};

struct LL {
    struct Node* first;
};

struct OpenHash {
    struct LL** data;
    int size;
    int totalWords;
    int uniqueWords;
};

typedef struct OpenHash OpenHash;
typedef struct Node Node;
typedef struct LL LL;

OpenHash* newOpenHash(int size);
int hash(char* word, int n);
bool member(char* word, OpenHash* table);
void insert(char* word, OpenHash* table);
void printHash(OpenHash* table);
void printHashStats(OpenHash* table);
void deleteOpenHash(OpenHash* table);
LL* newLinkedList();
void llInsert(LL* l, char* word);
bool llMember(LL* l, char* word);
void printLL(LL* l);
void deleteLinkedList(LL* l);
void normalizeWord(char* word);

OpenHash* newOpenHash(int size){
    OpenHash* table = malloc(sizeof(OpenHash));
    table->size = size;
    table->data = malloc(sizeof(LL*)*size);
    table->totalWords = 0;
    table->uniqueWords = 0;
    for(int i = 0; i < size; i++){
        table->data[i] = newLinkedList();
    }
    return table;
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
    if (strlen(word) == 0) {
        return; // Skip empty strings
    }
    if (!member(word, table)) {
        int pos = hash(word, table->size);
        llInsert(table->data[pos], word);
        table->uniqueWords++;
    }
    table->totalWords++;
}

void printHash(OpenHash* table){
    printf("Start of Hash Table.\n");
    printf("Size: %d\n",table->size);
    for(int i=0; i < table->size; i++){
        printf("h->data[%d]=",i);
        printLL(table->data[i]);
        printf("\n");
    }
    printf("End Of Hash Table.\n");
}

void deleteOpenHash(OpenHash* table){
    for(int i=0; i < table->size; i++){
        deleteLinkedList(table->data[i]);
    }
    free(table->data);
    free(table);
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
        if (isalpha(word[i])) {
            word[j++] = tolower(word[i]);
        }
        i++;
    }
    word[j] = '\0';
}

void read_file_insert_words(char* filename, OpenHash* table) {
    FILE* file = fopen(filename, "r");

    char word[100];

    while (fscanf(file, "%s", word) != EOF) {
        normalizeWord(word);
        insert(word, table);
    }
    fclose(file);
}

void printHashStats(OpenHash* table) {
    printf("Total Words: %d\n", table->totalWords);
    printf("Unique Words: %d\n", table->uniqueWords);
    printf("Hash Size: %d\n", table->size);

    int totalBucketValues = 0;
    for (int i = 0; i < table->size; i++) {
        int bucketSize = 0;
        Node* current = table->data[i]->first;
        while (current != NULL) {
            bucketSize++;
            current = current->next;
        }
        totalBucketValues += bucketSize;
        printf("Row %d contains %d values.\n", i, bucketSize);
    }

    float averageLength = (float)totalBucketValues / table->size;
    printf("Average Length: %.2f\n", averageLength);
}

int main() {
    int size;
    char filename[100];

    printf("Enter Size of Hash Table: \n");
    scanf("%d", &size);

    printf("Enter Name of File: \n");
    scanf("%s", filename);

    OpenHash* h = newOpenHash(size);
    read_file_insert_words(filename, h);
    printHashStats(h);
    deleteOpenHash(h);
    return 1;
}