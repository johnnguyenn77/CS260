#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TREE_HT 100
#define ASCII_SIZE 128

struct MinHeapNode {
    unsigned freq;
    unsigned char item;
    struct MinHeapNode *left, *right;
};

struct MinHeap {
    unsigned size;
    unsigned capacity;
    struct MinHeapNode** array;
};

struct MinHeapNode* newNode(unsigned char item, unsigned freq) {
    struct MinHeapNode* temp = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
    temp->left = temp->right = NULL;
    temp->item = item;
    temp->freq = freq;
    return temp;
}

struct MinHeap* createMinHeap(unsigned capacity) {
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct MinHeapNode**)malloc(minHeap->capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}

void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b) {
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(struct MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
        smallest = right;

    if (smallest != idx) {
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

int checkSizeOne(struct MinHeap* minHeap) {
    return (minHeap->size == 1);
}

struct MinHeapNode* extractMin(struct MinHeap* minHeap) {
    struct MinHeapNode* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    minHeapify(minHeap, 0);
    return temp;
}

void insertMinHeap(struct MinHeap* minHeap, struct MinHeapNode* minHeapNode) {
    ++minHeap->size;
    int i = minHeap->size - 1;
    while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = minHeapNode;
}

void buildMinHeap(struct MinHeap* minHeap) {
    int n = minHeap->size - 1;
    int i;
    for (i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
}

void printArray(int arr[], int n) {
    int i;
    for (i = 0; i < n; ++i)
        printf("%d", arr[i]);
    printf("\n");
}

int isLeaf(struct MinHeapNode* root) {
    return !(root->left) && !(root->right);
}

struct MinHeap* createAndBuildMinHeap(unsigned char item[], unsigned freq[], int size) {
    struct MinHeap* minHeap = createMinHeap(size);
    for (int i = 0; i < size; ++i)
        minHeap->array[i] = newNode(item[i], freq[i]);
    minHeap->size = size;
    buildMinHeap(minHeap);
    return minHeap;
}

struct MinHeapNode* buildHuffmanTree(unsigned char item[], unsigned freq[], int size) {
    struct MinHeapNode *left, *right, *top;
    struct MinHeap* minHeap = createAndBuildMinHeap(item, freq, size);
    while (!checkSizeOne(minHeap)) {
        left = extractMin(minHeap);
        right = extractMin(minHeap);
        top = newNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        insertMinHeap(minHeap, top);
    }
    return extractMin(minHeap);
}

void printCodes(struct MinHeapNode* root, int arr[], int top, char codes[ASCII_SIZE][MAX_TREE_HT]) {
    if (root->left) {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1, codes);
    }
    if (root->right) {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1, codes);
    }
    if (isLeaf(root)) {
        for (int i = 0; i < top; ++i) {
            codes[root->item][i] = arr[i] + '0';
        }
        codes[root->item][top] = '\0';
    }
}

void HuffmanCodes(unsigned char item[], unsigned freq[], int size, char codes[ASCII_SIZE][MAX_TREE_HT]) {
    struct MinHeapNode* root = buildHuffmanTree(item, freq, size);
    int arr[MAX_TREE_HT], top = 0;
    printCodes(root, arr, top, codes);
}

void countFreq(char* filename, int* freq, float* total) {
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Could not open file %s", filename);
        return;
    }
    char c = fgetc(fp);
    while (c != EOF) {
        if (c >= 0 && c < ASCII_SIZE) {
            freq[(int)c]++;
            (*total)++;
        }
        c = fgetc(fp);
    }
    fclose(fp);
}

int main() {
    char filename[100];
    printf("Enter File Name to read:\n");
    scanf("%s", filename);
    int freq[ASCII_SIZE] = {0};
    float total = 0;
    countFreq(filename, freq, &total);
    unsigned char arr[ASCII_SIZE];
    unsigned freqArr[ASCII_SIZE];
    int size = 0;
    for (int i = 0; i < ASCII_SIZE; i++) {
        if (freq[i] > 0) {
            arr[size] = i;
            freqArr[size] = freq[i];
            size++;
        }
    }
    char codes[ASCII_SIZE][MAX_TREE_HT] = {0};
    HuffmanCodes(arr, freqArr, size, codes);
    printf("| %5s | %-7s | %s |\n", "ASCII", "Percent", "Code");
    printf("| %5s | %-7s | %s |\n", "-----", "-------", "----");
    for (int i = 0; i < ASCII_SIZE; ++i) {
        if (freq[i] > 0) {
            printf("| %5d | %-7.5f | %s |\n", i, freq[i] / total, codes[i]);
        }
    }
    return 0;
}
