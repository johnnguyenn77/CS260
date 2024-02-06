#include <stdio.h>
#include <stdlib.h>

struct OpenHash typedef OpenHash;
struct LinkedList typedef LinkedList;
struct Node typedef Node;

struct OpenHash{
    LinkedList** data;
    int size;
};
struct LinkedList{
    Node* first;
};
struct Node{
    int val;
    Node* next;
};

OpenHash* newOpenHash(int size);
void printHash(OpenHash* h);
int hash(int val, int size);
void insert(OpenHash* h, int val);
char member(OpenHash* h, int val);
void deleteOpenHash(OpenHash* h);

LinkedList* newLinkedList();
void printLL(LinkedList* l);
void insertLL(LinkedList* l, int val);
char memberLL(LinkedList* l, int val);
void deleteLL(LinkedList* l);

int main(void){
    
    OpenHash* h = newOpenHash(5);
    printHash(h);
    insert(h,86);
    insert(h,83);
    insert(h,59);
    insert(h,19);
    insert(h,8);
    insert(h,81);
    printHash(h);
    for(int i=0; i < 100; i++){
        if(member(h,i)){printf("Found %d\n",i);}
    }
    deleteOpenHash(h);
    return 0;
}

OpenHash* newOpenHash(int size){
    OpenHash* h = malloc(sizeof(OpenHash));
    h->size = size;
    h->data = malloc(sizeof(LinkedList*)*size);
    for(int i=0; i < size; i++){
        h->data[i] = newLinkedList();
    }
    return h;
}
LinkedList* newLinkedList(){
    LinkedList* l = malloc(sizeof(LinkedList));
    l->first = NULL;
    return l;
}
Node* newNode(int val, Node* next){
    Node* n = malloc(sizeof(Node));
    n->val = val;
    n->next = next;
    return n;
}


void printHash(OpenHash* h){
    printf("Start of Hash\n");
    printf("Size: %d\n",h->size);
    for(int i=0; i < h->size; i++){
        printf("h->data[%d]=",i);
        printLL(h->data[i]);
        printf("\n");
    }
    printf("End of Hash\n");
}
void printLL(LinkedList* l){
    printf("[");
    Node* current = l->first;
    while(current != NULL){
        printf("%d",current->val);
        if(current->next!=NULL){printf(", ");}
        current = current->next;
    }
    printf("]");
}

int hash(int val, int size){
    return val%size;
}
void insert(OpenHash* h, int val){
    int pos = hash(val,h->size);
    insertLL(h->data[pos],val);
}
void insertLL(LinkedList* l, int val){
    Node* n = newNode(val,l->first);
    l->first = n;
}

char member(OpenHash* h, int val){
    int pos = hash(val,h->size);
    return memberLL(h->data[pos],val);
}
char memberLL(LinkedList* l, int val){
    Node* current = l->first;
    while(current!=NULL){
        if(current->val==val){return 1;}
        current = current->next;
    }
    return 0;
}

void deleteOpenHash(OpenHash* h){
    for(int i=0; i < h->size; i++){
        deleteLL(h->data[i]);
    }
    free(h->data);
    free(h);
}
void deleteLL(LinkedList* l){
    Node* current = l->first;
    while(current != NULL){
        Node* next = current->next;
        free(current);
        current = next;
    }
    free(l);
}
