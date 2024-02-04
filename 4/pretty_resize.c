/**
 @mainpage
 @section Overview
 
 Create a resizing Closed Hash Table. Insert random numbers to force it to resize.
 
 */
/**
 @file
 @author Mark Boady <mwb33@drexel.edu>
 @date Jan 2024
 @section Description
 
 This file is to show how a Closed Hash Table can be resized.
 */
#include <stdio.h>
#include <stdlib.h>

struct ClosedHash;
struct Record;
typedef struct ClosedHash ClosedHash;
typedef struct Record Record;
// Using an enum to improve readability
enum recordContents{EMPTY,FULL};
typedef enum recordContents recordContents;

/**
 A resizing Closed Hash Table
 */
struct ClosedHash{
    Record* data;/**< The Records in the Hash Table */
    int used;/**< How many spaces are used */
    int size;/**< The size of the table */
};
/**
 One record in the Hash Table
 */
struct Record{
    int value;/**< The value of the record*/
    recordContents status;/**< Is the space empty or full*/
};

/**
 Create a new Closed Hash Table
 @param size is the starting size
 @return A pointer to the table
 */
ClosedHash* newClosedHash(int size);
/**
 Free the memory used by the hash
 @param c is the hash to free
 */
void deleteHash(ClosedHash* c);
/**
 Insert val into the hash
 @param val is the number to insert
 */
void insert(ClosedHash* c, int val);
/**
 Is val in the hash?
 @param val is the number to search for
 @return 1 for true and 0 for false
 */
char member(ClosedHash* c, int val);
/**
 Increase the hash table size by double
 @param c is the hash table to resize
 */
void resize(ClosedHash* c);
/**
 Print the table to the screen
 @param c is the table to print
 */
void printHash(ClosedHash* c);
/**
 Search for a valid empty location
 @param c is the table to search
 @param val is the value we want to insert
 @return An index of an empty position or -1 if full
 */
int findEmptyPosition(ClosedHash* c, int val);


/**
 Test the hash table
 @return 0 always
 */
int main(void){
    ClosedHash *closed = newClosedHash(5);
    printHash(closed);
    /* Insert Know Values */
    int toInsert[12] = {10, 17, 15, 26, 9, 5, 1, 22, 27, 21, 11, 19};
    /* Test */
    for(int i=0; i < 12; i++){
        insert(closed,toInsert[i]);
        printf("I inserted %d\n",toInsert[i]);
        printHash(closed);
    }
    
    /* Delete Closed Hash */
    deleteHash(closed);
    return 0;
}

ClosedHash* newClosedHash(int size){
    ClosedHash* c = malloc(sizeof(ClosedHash));
    c->size = size;
    c->used = 0;
    c->data = malloc(size*sizeof(Record));
    for(int i=0; i < size; i++){
        c->data[i].value = -1;
        c->data[i].status = EMPTY;
    }
    return c;
}

void deleteHash(ClosedHash* c){
    free(c->data);
    free(c);
}

void printHash(ClosedHash* c){
    printf("Closed Hash Start\n");
    printf("Size: %d\n",c->size);
    printf("Used: %d\n",c->used);
    for(int i=0; i < c->size; i++){
        printf("c->data[%d]=(%d,%d)\n",
               i,
               c->data[i].value,
               c->data[i].status);
    }
    printf("Closed Hash End\n");
}

void insert(ClosedHash* c, int val){
    //No More Space Left in the Array
    if(c->used == c->size){
        resize(c);
    }
    //Put into the array
    int pos = findEmptyPosition(c,val);
    c->data[pos].value = val;
    c->data[pos].status = FULL;
    c->used++;
}

int findEmptyPosition(ClosedHash* c, int val){
    //Offset is used for rehashing
    int offset = 0;
    int pos=-1;
    do{
        pos = (val+offset)%c->size;
        if(c->data[pos].status == EMPTY){
            return pos;
        }
        offset++;//shift for rehash
    //Loop Until Empty Position or did full circle
    }while(c->data[pos].status != EMPTY && offset < c->size);
    return -1;//No Space left
}

void resize(ClosedHash* c){
    ClosedHash* newC = newClosedHash(c->size*2);
    for(int i=0; i < c->size; i++){
        if(c->data[i].status==FULL){
            insert(newC,c->data[i].value);
        }
    }
    //Move data to old struct
    free(c->data);
    c->data = newC->data;
    c->used = newC->used;
    c->size = newC->size;
    free(newC);
    printf("Resized up to %d\n",c->size);
}

char member(ClosedHash* c, int val){
    //Offset is used for rehashing
    int offset = 0;
    int pos=-1;
    do{
        pos = (val+offset)%c->size;
        //Did we Find It?
        if(c->data[pos].status == FULL && c->data[pos].value==val){
            return 1;
        }
        offset++;//shift for rehash
    //Loop Until Empty Position or did full circle
    }while(c->data[pos].status != EMPTY && offset < c->size);
    return 0;//Never Found
}
