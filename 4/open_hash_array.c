#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

typedef struct {
    char** array;
    int* rowCounts;
    int size;
} OpenHash;

OpenHash* newOpenHash(int size) {
    OpenHash* hashTable = (OpenHash*)malloc(sizeof(OpenHash));
    hashTable->array = (char**)malloc(size * sizeof(char*));
    hashTable->rowCounts = (int*)calloc(size, sizeof(int));
    hashTable->size = size;
    for (int i = 0; i < size; ++i) {
        hashTable->array[i] = NULL;
    }
    return hashTable;
}

int hash(char* word, int n) {
    int total = 0;
    for (int i = 0; word[i] != 0; i++) {
        char c = word[i];
        total = total + (int)c;
        total = total * 101;
        total = total % n;
    }
    return total;
}

bool member(char* word, OpenHash* table) {
    int index = hash(word, table->size);
    while (table->array[index] != NULL) {
        if (strcmp(table->array[index], word) == 0) {
            return true;
        }
        index = (index + 1) % table->size;
    }
    return false;
}

// void insert(char* word, OpenHash* table) {
//     int index = hash(word, table->size);
//     table->rowCounts[index]++;
//     while (table->array[index] != NULL) {
//         if (strcmp(table->array[index], word) == 0) {
//             return;
//         }
//         index = (index + 1) % table->size; 
//     }
//     table->array[index] = strdup(word);
// }

void insert(char* word, OpenHash* table) {
    int index = hash(word, table->size);
    table->rowCounts[index]++;
    while (table->array[index] != NULL) {
        if (strcmp(table->array[index], word) == 0) {
            return;
        }
        index = (index + 1) % table->size; 
    }
    // If the slot is already occupied, append the new word with a space
    if (table->array[index] != NULL) {
        // Allocate memory for the combined string
        char* combined = malloc(strlen(table->array[index]) + strlen(word) + 2);
        // Concatenate the existing word and the new word with a space
        sprintf(combined, "%s %s", table->array[index], word);
        // Free the memory of the existing word
        free(table->array[index]);
        // Assign the combined string to the slot
        table->array[index] = combined;
    } else {
        // If the slot is empty, simply assign the word
        table->array[index] = strdup(word);
    }
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

void processFile(char* filename, OpenHash* hashTable, int* totalWords, int* uniqueWords) {
    FILE* file = fopen(filename, "r");

    if (file == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    char word[100];

    while (fscanf(file, "%s", word) != EOF) {
        normalizeWord(word);
        printf("%s\n", word);
        if (strcmp(word, "") != 0) {
            (*totalWords)++;
            if (!member(word, hashTable)) {
                (*uniqueWords)++;
                insert(word, hashTable);
            }
        }
    }
    fclose(file);
}

void printStatistics(OpenHash* hashTable) {
    printf("Hash Size: %d\n", hashTable->size);
    for (int i = 0; i < hashTable->size; i++) {
        printf("Row %d contains %d values.\n", i, hashTable->rowCounts[i]);
    }

    double sum = 0.0;
    for (int i = 0; i < hashTable->size; i++) {
        sum += hashTable->rowCounts[i];
    }
    double averageLength = sum / hashTable->size;
    printf("Average Length: %.2f\n", averageLength);
}

void printHashTable(OpenHash* hashTable) {
    printf("Hash Table:\n");
    for (int i = 0; i < hashTable->size; i++) {
        printf("Row %d: ", i);
        if (hashTable->array[i] == NULL) {
            printf("Empty\n");
        } else {
            int index = i;
            printf("%s", hashTable->array[index]);
            index = (index + 1) % hashTable->size;
            while (index != i) {
                if (hashTable->array[index] != NULL) {
                    printf(", %s", hashTable->array[index]);
                }
                index = (index + 1) % hashTable->size;
            }
            printf("\n");
        }
    }
}

int main() {
    int size;
    printf("Enter Size of Hash Table: \n");
    scanf("%d", &size);
    char filename[100];
    printf("Enter Name of File: \n");
    scanf("%s", filename);

    OpenHash* hashTable = newOpenHash(size);

    int totalWords = 0;
    int uniqueWords = 0;
    processFile(filename, hashTable, &totalWords, &uniqueWords);

    printf("Total Words: %d\n", totalWords);
    printf("Unique Words: %d\n", uniqueWords);
    printStatistics(hashTable);
    printHashTable(hashTable);

    for (int i = 0; i < size; i++) {
        free(hashTable->array[i]);
    }
    free(hashTable->array);
    free(hashTable->rowCounts);
    free(hashTable);

    return 0;
}
