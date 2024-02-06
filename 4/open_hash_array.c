#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LENGTH 100

struct Node {
    char* data;
    struct Node* next;
};

struct OpenHash {
    struct Node** data;
    int size;
    int totalWords;
    int uniqueWords;
};

typedef struct OpenHash OpenHash;
typedef struct Node Node;

OpenHash* newOpenHash(int size);
int hash(char* word, int n);
bool member(char* word, OpenHash* table);
void insert(char* word, OpenHash* table);
void printHash(OpenHash* table);
void printHashStats(OpenHash* table);
void deleteOpenHash(OpenHash* table);
void deleteNodes(Node* node);
void normalizeWord(char* word);

OpenHash* newOpenHash(int size){
    OpenHash* table = malloc(sizeof(OpenHash));
    if (table == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    table->size = size;
    table->data = malloc(size * sizeof(Node*));
    if (table->data == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i < size; i++){
        table->data[i] = NULL;
    }
    table->totalWords = 0;
    table->uniqueWords = 0;
    return table;
}

int hash(char* word, int n) {
    int total = 0;
    for(int i=0; word[i] != '\0'; i++) {
        char c = word[i];
        total = total + (int) c;
        total = total * 101;
        total = total % n;
    }
    return total;
}

bool member(char* word, OpenHash* table){
    int pos = hash(word, table->size);
    Node* current = table->data[pos];
    while(current != NULL){
        if(strcmp(current->data, word) == 0) {
            return true;
        }
        current = current->next;
    }
    return false;
}

void insert(char* word, OpenHash* table){
    if (strlen(word) == 0) {
        return; // Skip empty strings
    }
    if (!member(word, table)) {
        int pos = hash(word, table->size);
        Node* newNode = malloc(sizeof(Node));
        if (newNode == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            exit(EXIT_FAILURE);
        }
        newNode->data = strdup(word);
        newNode->next = table->data[pos];
        table->data[pos] = newNode;
        table->uniqueWords++;
    }
    table->totalWords++;
}

void printHash(OpenHash* table){
    printf("Start of Hash Table.\n");
    printf("Size: %d\n",table->size);
    for(int i=0; i < table->size; i++){
        printf("h->data[%d]=",i);
        Node* current = table->data[i];
        printf("[");
        while(current != NULL){
            printf("%s",current->data);
            if(current->next!=NULL){printf(", ");}
            current = current->next;
        }
        printf("]");
        printf("\n");
    }
    printf("End Of Hash Table.\n");
}

void deleteNodes(Node* node) {
    if (node != NULL) {
        deleteNodes(node->next);
        free(node->data);
        free(node);
    }
}

void deleteOpenHash(OpenHash* table){
    for(int i=0; i < table->size; i++){
        deleteNodes(table->data[i]);
    }
    free(table->data);
    free(table);
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
    if (file == NULL) {
        fprintf(stderr, "File '%s' not found.\n", filename);
        exit(EXIT_FAILURE);
    }

    char word[MAX_WORD_LENGTH];

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
        Node* current = table->data[i];
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
    char filename[MAX_WORD_LENGTH];

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
