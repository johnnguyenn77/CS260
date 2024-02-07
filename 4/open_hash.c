/**
 * @file open_hash.c
 * @author John Nguyen <jn866@drexel.edu>
 * @brief 
 * @date 2024-02-06
 * 
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

/**
 * A structure to represent a single node
 */
struct Node {
    char* data;
    struct Node* next;
};

/**
 * A structure to represent the array of a hash table
 */
struct LL {
    struct Node* first;
};

/**
 * A structure to represent the Hash Table itself
 */
struct OpenHash {
    struct LL** data;
    int size;
    int totalWords;
    int uniqueWords;
};

typedef struct OpenHash OpenHash;
typedef struct Node Node;
typedef struct LL LL;

/**
 * Create a new Hash table based around an array of size elements
 * @param size is the size of the array the table is built with
 * @return OpenHash* a pointer to the struct
 */
OpenHash* newOpenHash(int size);

/**
 * The hash function for strings
 * @param word is a null terminated character array
 * @param n is the size of the array
 * @return int the hashed index for the string
 */
int hash(char* word, int n);

/**
 * Ask if string is in table
 * @param word is a null terminated character array
 * @param table is the Hash Table to search
 * @return true if found
 * @return false if not
 */
bool member(char* word, OpenHash* table);

/**
 * Insert a string into the table. Ignore duplicates.
 * @param word is a null terminated character array
 * @param table is the Hash Table to search
 */
void insert(char* word, OpenHash* table);

/**
 * Print out the values of the Hash Table
 * @param table is the table to be printed
 */
void printHash(OpenHash* table);

/**
 * Print out the stats for the tests
 * @param table is the table to be printed
 */
void printHashStats(OpenHash* table);

/**
 * Delete the Hash Table from memory
 * @param table is the table to be deleted
 */
void deleteOpenHash(OpenHash* table);

/**
 * Create a new linked list
 * @return LL* is the pointed to the linked list
 */
LL* newLinkedList();

/**
 * Insert a string into the linked list
 * @param l is the linked list to insert the string into
 * @param word is the string to be inserted
 */
void llInsert(LL* l, char* word);

/**
 * Check if a string is in the linked list
 * @param l is the linked list to check
 * @param word is the string to check
 * @return true if the word is in the linked list
 * @return false if not
 */
bool llMember(LL* l, char* word);

/**
 * Print out the linked list 
 * @param l is the linked list to be printed
 */
void printLL(LL* l);

/**
 * Delete the linked list from memory
 * @param l is the linked list to be deleted
 */
void deleteLinkedList(LL* l);

/**
 * Normalize a string by removing special characters and change it to lowercase
 * @param word is the string to normalize
 */
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
        return;
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