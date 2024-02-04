/**
 @mainpage
 @section Overview
 
 This is an example of a closed hash table being used for memoization
 */
/**
 @file
 @author Mark Boady <mwb33@drexel.edu>
 @date Jan 2024
 @section Summary
 
 We compute the fibonanci series with a without a cache for memoization.
 This shows an example of closed hash table that overwrites on collisions.
 */
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

struct record;
struct cache;
typedef struct record record;
typedef struct cache cache;
/** 
 A record is 1 position in the cache
*/
struct record{
    int input;/**< What function input causes this output */
    int output;/**< What is the output of this function input */
    char blank;/**< Is the space empty?*/
};
/**
 A closed and fixed size Hash Table stored in an array.
 */
struct cache{
    record* data;/**< The array of records.*/
    int size;/**< How many records we can store at any time*/
};

/**
 Make a new empty Close Hash Table
 @param size is the max size of the table
 @return a pointer to the table we created
 */
cache* newCache(int size);
/**
 Delete the Cache and free memory
 @param c is the Closed Hash Table to Free
 */
void deleteCache(cache* c);
/**
 Insert a new value into the cache. Overwrite on collisions
 @param c is the cache to edit
 @param i is the function input
 @param o is the function output
 */
void insert(cache* c, int i, int o);
/**
 Is the value i in the cache?
 @param c is the cache to search
 @param i is the input to search for
 @return 1 for true and 0 for false
 */
char member(cache* c, int i);
/**
 Get a value. Assumes you already did membership check
 @param c is the cache
 @param i is the input to look for
 @return The output that matches f(i)
 */
int getVal(cache* c, int i);

/**
 Your classic textbook fibonacci series
 @param x is the input integer
 @return the xth fibonacci number
 */
int fibClassic(int x);
/**
 Front End for Fibonacci with a cache
 @param x is the input integer
 @return the xth fibonacci number
 */
int fibImproved(int x);
/**
 Helper function to pass cache recursively
 @param x is the input integer
 @return the xth fibonacci number
 */
int fibHelper(int x, cache* c);

/**
 Compare the runtime of the two fibonacci functions
 @return always 0
 */
int main(){
    printf("| %7s | %7s | %7s | %10s | %10s |\n","x","fibC(x)","FibI(x)"
        ,"FibC Clock","FibI Clock");
    for(int i=0; i < 30; i++){
        clock_t before = clock();
        int a = fibClassic(i);
        clock_t after = clock();
        int t1 = after-before;
        
        before = clock();
        int b = fibImproved(i);
        after = clock();
        int t2 = after - before;
        
        printf("| %7d | %7d | %7d | %10d | %10d |\n",i,a,b,t1,t2);
    }
    return 0;
}

/* Both versions of the Fibonacci Function*/

/* Version 1 straight out of your math textbook. */
int fibClassic(int x){
    if(x <= 1){
        int temp =  x;
        //printf("fibClassic(%d)=%d\n",x,temp);
        return temp;
    }else{
        int temp = fibClassic(x-1)+fibClassic(x-2);
        //printf("fibClassic(%d)=%d\n",x,temp);
        return temp;
    }
}

/* Version 2 has this front end call to manage the cache create and delete. */
int fibImproved(int x){
    cache* c = newCache(5);
    int temp = fibHelper(x,c);
    deleteCache(c);
    return temp;
    
}
/* Version 2 has the read work done here */
int fibHelper(int x, cache* c){
    if(member(c,x)){
        //printf("Shortcut %d\n",x);
        return getVal(c,x);
    }
    if(x <= 1){
        int temp =  x;
        //printf("fibHelper(%d)=%d\n",x,temp);
        insert(c,x,temp);
        return temp;
    }else{
        int temp = fibHelper(x-1,c )+fibHelper(x-2,c);
        //printf("fibHelper(%d)=%d\n",x,temp);
        insert(c,x,temp);
        return temp;
    }
}

/* Cache Data Structure Code */

/* Create a New Cache */
cache* newCache(int size){
    cache* c = malloc(sizeof(cache));
    c->size = size;
    c->data = malloc(size*sizeof(record));
    for(int i=0; i < size; i++){
        c->data[i].blank = 1;
    }
    return c;
}
/* Delete the Cache */
void deleteCache(cache* c){
    free(c->data);
    free(c);
}
/* Insert Values into Cache */
void insert(cache* c, int i, int o){
    int pos = i%c->size;
    c->data[pos].input = i;
    c->data[pos].output = o;
    c->data[pos].blank = 0;
}
/* Get Values Out assuming they Exist */
int getVal(cache* c, int i){
    int pos = i%c->size;
    return c->data[pos].output;
}
/* Check if a value exists */
char member(cache* c, int i){
    int pos = i%c->size;
    int blank = c->data[pos].blank;
    int in = c->data[pos].input;
    int out = c->data[pos].output;
    if(blank==0 && in==i){
        return 1;
    }
    return 0;
}

/* The End */
