/**
 * @mainpage CS 260 - Homework 8
 * @section Description
 * 
 * The program will ask for a file from the user then find the MST using Prim's Algorithm
 * 
 */

/**
 * @file main.c
 * @author John Nguyen <jn866@drexel.edu>
 * @date 2024-03-10
 * @section DESCRIPTION
 * 
 * This file contains an implementation of Prim's Algorithm
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF 9999999

int main() {
    char filename[100];
    int startNode;

    printf("Enter File Containing Graph:\n");
    scanf("%s", filename);  // read the filename

    printf("Enter Starting Node:\n");
    scanf("%d", &startNode);  // read the starting node

    printf("Running Prim's Algorithm\n");
    printf("Input File: %s\n", filename);
    printf("Starting Node: %d\n", startNode);

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Could not open file %s\n", filename);
        return 1;
    }

    int V;
    fscanf(file, "%d", &V);  // read the number of vertices

    // create a 2D array for the graph
    int** G = malloc(V * sizeof(int*));
    for (int i = 0; i < V; i++) {
        G[i] = malloc(V * sizeof(int));
        for (int j = 0; j < V; j++) {
            G[i][j] = INF;  // initialize the graph with INF
        }
    }

    // read the edges
    int from, to, weight;
    while (fscanf(file, "%d %d %d", &from, &to, &weight) == 3) {
        G[from][to] = weight;
        G[to][from] = weight; 
    }

    fclose(file);

    // Prim's Algorithm
    int no_edge = 0;  // number of edge
    int selected[V];  // create a array to track selected vertex
    for (int i = 0; i < V; i++)
        selected[i] = 0;  // set selected false initially
    selected[startNode] = 1;  // choose the starting vertex and make it true

    int x;  //  row number
    int y;  //  col number
    int totalWeight = 0;

    while (no_edge < V - 1) {
        int min = INF;
        x = 0;
        y = 0;

        for (int i = 0; i < V; i++) {
            if (selected[i]) {
                for (int j = 0; j < V; j++) {
                    if (!selected[j] && G[i][j]) {  // not in selected and there is an edge
                        if (min > G[i][j]) {
                            min = G[i][j];
                            x = i;
                            y = j;
                        }
                    }
                }
            }
        }

        printf("Added %d\n", y);
        printf("Using Edge (%d, %d) with weight %d\n", x, y, G[x][y]);
        selected[y] = 1;
        no_edge++;
        totalWeight += G[x][y];
    }

    printf("Total Weight: %d\n", totalWeight);

    return 0;
}
