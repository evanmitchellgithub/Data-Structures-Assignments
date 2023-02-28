#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include<stdio.h>
#define size 6

void bfs(int array[][size], int v);
void DFS(int array[][size], int i);
void print_val(int k);
void initialise(int array[][size]);
void insert_Edge(int array[][size],int src, int dest);
void printAdjMatrix(int array[][size]);

enum nodes{A, B, C, D, E, F};

int visited[size];
int visited_bfs[size];
int queue[size];
int front = -1;
int rear = -1;
int count = 0;

/*
While modified, the following source was used a template
in order to create the basic Matrix representation.
Source: https://www.log2base2.com/data-structures/graph/adjacency-matrix-representation-of-graph.html
*/

void bfs(int array[][size], int v){

    //this for loop only does one level of the matrix, i.e. the values visible from one node

    //for each value in the array
    for(int i = 0; i < size; i++){ 

        //if the values from v havent been visited, and the value doesnt equal 0
        if(array[v][i] != 0 && visited_bfs[i] == 0){
            //sets the node to the back of the queue
            rear = rear + 1;
            queue[rear] = i;
            //says it has visited the nodes/makes permanent <---
            visited_bfs[i] = 1;
            //prints value
            print_val(i);
        }
    }

    /*
        Note: Instead of using functions, i do the queue recursively
        so instead of passing the queue into a function and changing it, I add a 
        value to the queue, and when i've finished this level of the BFS I 
        increase where the front of the queue is, then pass in that
    */

    //increments which value is at the front
    front = front + 1;
    //if the front value is less than the rear value
    if(front <= rear){
        //redo bfs, with the next value at the front of the queue
        bfs(array, queue[front]);
    }
}

void DFS(int array[][size], int i){  

    //print the current node
    print_val(i);
    //set the current node to visited
    visited[i] = 1; 

    //for each value of the array
    for(int j = 0; j < size; j++){ 
        //if the value hasnt been visited and the array has an edge, then go into it 
        if(!visited[j] && array[i][j] == 1){
            DFS(array, j); 
        }
    }

} 

void print_val(int k){

    if(k == 0){
        printf("A ");
    }
    else if(k == 1){
        printf("B ");
    }
    else if(k == 2){
        printf("C ");
    }
    else if(k == 3){
        printf("D ");
    }
    else if(k == 4){
        printf("E ");
    }
    else if(k == 5){
        printf("F ");
    }
}

//init matrix to 0
void initialise(int array[][size]){

    int i, j;

    for(i = 0; i < size; i++){
        for(j = 0; j < size; j++){
            array[i][j] = 0;
        }
    }

    for(i = 0; i < size; i++){
        visited[i] = 0;
    }

    for(i = 0; i < size; i++){
        visited_bfs[i] = 0;
    }

    for(i = 0; i < size; i++){
        queue[i] = 0;
    }
}

//Add edge. set arr[src][dest] = 1
void insert_Edge(int array[][size],int src, int dest){
    array[src][dest] = 1;
}

void printAdjMatrix(int array[][size]){
    int i, j;

    for(i = 0; i < size; i++)
    {
        for(j = 0; j < size; j++)
        {
            printf("%d ", array[i][j]);
        }
        printf("\n");
    }
}

//print the adjMatrix
int main(){
    int adjacent_Matrix[size][size];

    int starting_letter = A;

    initialise(adjacent_Matrix);
    insert_Edge(adjacent_Matrix, A, B);
    insert_Edge(adjacent_Matrix, A, D);
    insert_Edge(adjacent_Matrix, A, E);
    insert_Edge(adjacent_Matrix, B, D);
    insert_Edge(adjacent_Matrix, B, C);
    insert_Edge(adjacent_Matrix, E, D);
    insert_Edge(adjacent_Matrix, D, F);
    insert_Edge(adjacent_Matrix, C, B);
    insert_Edge(adjacent_Matrix, C, D);
    insert_Edge(adjacent_Matrix, F, C);

    printf("ADjacency_matrix\n");
    printAdjMatrix(adjacent_Matrix);
    printf("\n");

    printf("DFS: ");
    DFS(adjacent_Matrix, starting_letter);
    printf("\n");

    printf("BFS: ");
    print_val(starting_letter);
    bfs(adjacent_Matrix, starting_letter);


    return 0;
}