#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define size 4807
#define INFINITY 99999
#define strlength 100
#define num_edges 6179
#define verticemax 7667
#define verticelength 4807

enum nodes{A, B, C, D, E, F, G};

//these are global due to size issues in the stack
int adjacent_matrix[size][size]; //adjacency matrix
int cost[size][size]; //stores the cost matrix
int visited[size];
int count = 0;      //count gives the number of nodes seen so far
int minimum_distance, nextnode;

typedef struct edges edges;
struct edges {
    int vertex1;
    int vertex2;
    int weight;
};
struct edges edge_array[num_edges];

typedef struct vertices vertices;
struct vertices {
    int StopId;
    char name[strlength];
    float Latitude;
    float Longitude;
    int index;
};
struct vertices vertice_array[num_edges];

void initialise();
void insert_Edge(int src, int dest, int cost);
void printAdjMatrix();
void dijkstra( int start_val, int endnode);

//init matrix to 0
void initialise(){

    int i, j;

    for(i = 0; i < size; i++){
        for(j = 0; j < size; j++){
            adjacent_matrix[i][j] = 0;
        }
    }

    for(i = 0; i < size; i++){
        visited[i] = 0;
    }

}

//Add edge. set arr[src][dest] = 1
void insert_Edge(int src, int dest, int cost){
    adjacent_matrix[src][dest] = cost;
}

void printAdjMatrix(){
    int i, j;

    for(i = 0; i < 153; i++)
    {
        for(j = 0; j < 100; j++)
        {
            printf("%d ", adjacent_matrix[i][j]);
        }
        printf("\n");
    }
}

int next_field ( FILE *csv , char *buffer , int max_length ){
    
    char current_char;
    current_char = fgetc (csv);
    int i = 0;
    bool flag = 0; 

    while( i < max_length){ 

        if(current_char == '\n'){
            buffer[i] = '\0';
            return 0; //leaves function
        }
        if(current_char == '"'){
            flag = !flag;
        }

        if(current_char == ',' && !flag){
            buffer[i] = '\0';
            return 0; //leaves function
        }

        if (current_char == EOF){
            buffer[i] = '\0';
            return 2; 
        }  

        if(current_char != '"'){
            buffer[i++] = current_char; 
        }

        current_char = fgetc (csv);
    }
return 0;
}

void printnode(int value){

    for(int i = 0; i < verticelength; i++){

        if(value == vertice_array[i].index){
            printf("Stop Id: %d \t\tName: %s  ", vertice_array[i].StopId, vertice_array[i].name);
            printf("\t\tLatitude: %f \t\tLongitude: %f ", vertice_array[i].Latitude, vertice_array[i].Longitude);
            printf("\n");
        }
    }

}

void dijkstra(int startnode, int endnode){

    int distance[size];   //counts the distance between nodes
    int predecessor[size];//stores the predecessors of each node

    //Note: the predecessor changes in each iteration of the while loop


    //initialise the cost matrix
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){ 
            if(adjacent_matrix[i][j] == 0){
                cost[i][j] = INFINITY;
            }
            else{
                cost[i][j] = adjacent_matrix[i][j];
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

    //while the count is less than the total number of nodes
    while(count < size ){
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

                //the next node is the current value of i,              A B C D E 
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
                    predecessor[i] = nextnode ; //the next predecessor is the next node

                }
            }
        }

        count++;

    }

    printf("\nDistance to node %d", endnode);
    printf(": %d", distance[endnode]);
    printf("\nPath to: %d\n", endnode);
    printnode(endnode);

    int j = endnode;

    //while j doesnt equal the starting node
    do{

    //get the predecessor of the current node on the way back to source
    j = predecessor[j];
    //print it
    printnode(j);

    }while(j != startnode);

}

//print the adjMatrix
int main(){

    FILE * csv;
    //opening the file
    csv = fopen ("edges.csv","r");
    printf("edges.csv loaded!\n");

    char buffer[strlength];

    for(int x = 0; x < 3; x++){
        next_field (csv, buffer,  strlength );
            
    }

    for(int i = 0; i < num_edges; i++){

        for(int j = 0; j < strlength; j++){
            buffer[j] = '\0';
        }

        int charId = next_field (csv, buffer,  strlength );
        if(charId == 2){break;} 

        edge_array[i].vertex1 = atoi(buffer);
        charId = next_field (csv, buffer,  strlength );

        edge_array[i].vertex2 = atoi(buffer);
        charId = next_field (csv, buffer,  strlength );

        edge_array[i].weight = atoi(buffer);

    }

    FILE * csv2;
    csv2 = fopen ("vertices.csv","r");
    printf("vertices.csv loaded!\n");

    for(int x = 0; x < 4; x++){
        next_field (csv2, buffer,  strlength );
            
    }

    for(int i = 0; i < verticelength; i++){

        for(int j = 0; j < strlength; j++){
            buffer[j] = '\0';
        }

        int charId = next_field (csv2, buffer,  strlength );
        if(charId == 2){break;} 

        vertice_array[i].StopId = atoi(buffer);
        charId = next_field (csv2, buffer,  strlength );

        strcpy(vertice_array[i].name ,buffer );
        charId = next_field (csv2, buffer,  strlength );

        vertice_array[i].Latitude = atof(buffer);
        charId = next_field (csv2, buffer,  strlength );

        vertice_array[i].Longitude = atof(buffer);

        vertice_array[i].index = i;
        
    }

    int input;
    int inputd;
    int indexsrc;
    int indexdest;
    int searchflag = 0, searchflag2 = 0;
    printf("\nType the station which you would like to start from: \n");
    scanf("%d", &input);

    //inputint = atoi(input);
    for(int i = 0; i < verticelength; i++){
        if(vertice_array[i].StopId == input){
            printf("\nStop Id: %d", vertice_array[i].StopId);
            printf("\nName   : %s", vertice_array[i].name);
            printf("\nLat    : %f", vertice_array[i].Latitude);
            printf("\nLong   : %f", vertice_array[i].Longitude);
            printf("\nIndex  : %d", vertice_array[i].index);
            printf("\n");
            indexsrc = vertice_array[i].index;
            searchflag = 1;
        }
    }
    if(searchflag == 0){
        printf("\nInvalid: Bus station does not exist.\n");
    }

    printf("\nType the station which you would like to go to: \n");
    scanf("%d", &inputd);

    for(int i = 0; i < verticelength; i++){
        if(vertice_array[i].StopId == inputd){
            printf("\nStop Id: %d", vertice_array[i].StopId);
            printf("\nName   : %s", vertice_array[i].name);
            printf("\nLat    : %f", vertice_array[i].Latitude);
            printf("\nLong   : %f", vertice_array[i].Longitude);
            printf("\nIndex  : %d", vertice_array[i].index);
            indexdest = vertice_array[i].index;
            searchflag2 = 1;
        }
    }
    if(searchflag2 == 0){
        printf("\nInvalid: Bus station does not exist.\n");
    }

    initialise();
    
    for(int i = 0; i < num_edges; i++){
    //    insert_Edge(edge_array[i].vertex1, edge_array[i].vertex2, edge_array[i].weight);
        int vert1 = 0, vert2 = 0;
        for(int j = 1; j < verticelength; j++){
            if(edge_array[i].vertex1 == vertice_array[j].StopId){
                vert1 = vertice_array[j].index;
            }
        }

        for(int j = 1; j < verticelength; j++){
            if(edge_array[i].vertex2 == vertice_array[j].StopId){
                vert2 = vertice_array[j].index;
            }
        }

        insert_Edge(vert1, vert2, edge_array[i].weight);
        insert_Edge(vert2, vert1, edge_array[i].weight);

    }
    //printAdjMatrix();

    printf("\n");

    if(searchflag == 1 && searchflag2 == 1){
        dijkstra(indexsrc, indexdest);
    }


    return 0;
}