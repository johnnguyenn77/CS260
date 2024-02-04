#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct OpenHash;
typedef struct OpenHash OpenHash;

OpenHash* newOpenHash(int size);

int hash(char* word, int n);

bool member(char* word, OpenHash* table);

void insert(char* word, OpenHash *table);

int hash(char* word, int n);

struct OpenHash {
    
};

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