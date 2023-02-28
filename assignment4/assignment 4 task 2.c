#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define size 7
#define INFINITY 1000

enum nodes{A, B, C, D, E, F, G};

void print_val(int k);
void initialise(int array[][size]);
void insert_Edge(int array[][size],int src, int dest, int cost);
void printAdjMatrix(int array[][size]);
void dijkstra(int array[][size], int start_val);

int visited[size];
int count = 0;      //count gives the number of nodes seen so far
int minimum_distance, nextnode;

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
    else if(k == 6){
        printf("G ");
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

}

//Add edge. set arr[src][dest] = 1
void insert_Edge(int array[][size],int src, int dest, int cost){
    array[src][dest] = cost;
}

void printAdjMatrix(int array[][size]){

    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            printf("%d ", array[i][j]);
        }
        printf("\n");
    }
}


/*
Note: Although *heavily* modified, the basis for this dijkstra
      algorith can be found below:
      Source: https://www.codewithc.com/dijkstras-algorithm-in-c/
*/

void dijkstra(int array[][size], int startnode){

    int cost[size][size]; //stores the cost matrix
    int distance[size];   //counts the distance between nodes
    int predecessor[size];//stores the predecessors of each node

    //Note: the predecessor changes in each iteration of the while loop

    int minimum_distance, nextnode;

    //initialise the cost matrix
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){ 
            if(array[i][j] == 0){
                cost[i][j] = INFINITY;
            }
            else{
                cost[i][j] = array[i][j];
            }
        }
    }

    //initialize predecessor[] and distance[]
    for(int i = 0; i < size; i++){

        distance[i] = cost[startnode][i];
        predecessor[i] = startnode;

    }

    //set the distance for the start to 0, and set the start to visited, 1 item counted
    distance[startnode] = 0;
    visited[startnode] = 1;
    count = 0;

    printf("The order in which they become permanent is: ");
    nextnode = startnode;
    //print_val(startnode);

    //while the count is less than the total number of nodes
    while(count < size ){

        print_val(nextnode);

        //set the minimum to 1000, and go down
        minimum_distance = INFINITY;

        //nextnode gives the node at minimum distance

        //for each node in the matrix
        for(int i = 0; i < size; i++){

            //if the distance is less than the minimum distance, and the node 
            //hasnt been visited yet
            if(distance[i] < minimum_distance && !visited[i]){

                //set the min distance to the value in the array
                minimum_distance = distance[i];

                //the next node is the current value of i,
                //as that has the smallest value
                nextnode = i;

            }
        }

        //set this value of i as visited/permanent.
        visited[nextnode] = 1;

        //check if a better path exists through nextnode
        //for each value of i , find a better path
        for(int i = 0; i < size; i++){

            //the value has not been visited
            if(!visited[i]){

                //check if the min distance and the cost of the next node is less
                //than the current distance
                if(minimum_distance + cost[nextnode][i] < distance[i]){

                    //the distance is the mindist and the cost of the next node (which is smaller)
                    distance[i] = minimum_distance + cost[nextnode][i];
                    predecessor[i] = nextnode; //the next predecessor is the next node

                }
            }
        }

        count++;

    }

    printf("\n");
    //print the path and distance of each node
    for(int i = 0; i < size; i++){

        if(i != startnode){

            printf("\nDistance to node ");
            print_val(i);
            printf(": %d", distance[i]);
            printf("\nPath: ");
            print_val(i);

            int j = i;

            do{
            j = predecessor[j];
            printf("<-");
            print_val(j);

            }while(j != startnode);

        }
    }
}

//print the adjMatrix
int main(){

    int adjacent_Matrix[size][size];

    int starting_letter = A;

    initialise(adjacent_Matrix);
    insert_Edge(adjacent_Matrix, A, B, 1);
    insert_Edge(adjacent_Matrix, A, C, 3);
    insert_Edge(adjacent_Matrix, B, C, 1);
    insert_Edge(adjacent_Matrix, B, G, 2);
    insert_Edge(adjacent_Matrix, B, D, 7);
    insert_Edge(adjacent_Matrix, G, D, 12);
    insert_Edge(adjacent_Matrix, C, D, 9);
    insert_Edge(adjacent_Matrix, C, E, 3);
    insert_Edge(adjacent_Matrix, B, E, 5);
    insert_Edge(adjacent_Matrix, D, E, 2);
    insert_Edge(adjacent_Matrix, D, E, 1);
    insert_Edge(adjacent_Matrix, E, F, 2);
    insert_Edge(adjacent_Matrix, A, F, 10);

    insert_Edge(adjacent_Matrix, B, A, 1);
    insert_Edge(adjacent_Matrix, C, A, 3);
    insert_Edge(adjacent_Matrix, C, B, 1);
    insert_Edge(adjacent_Matrix, G, B, 2);
    insert_Edge(adjacent_Matrix, D, B, 7);
    insert_Edge(adjacent_Matrix, D, G, 12);
    insert_Edge(adjacent_Matrix, D, C, 9);
    insert_Edge(adjacent_Matrix, E, C, 3);
    insert_Edge(adjacent_Matrix, E, B, 5);
    insert_Edge(adjacent_Matrix, E, D, 2);
    insert_Edge(adjacent_Matrix, F, D, 1);
    insert_Edge(adjacent_Matrix, F, E, 2);
    insert_Edge(adjacent_Matrix, F, A, 10);

    printf("\n");

    dijkstra(adjacent_Matrix, starting_letter);

    return 0;
}