/*
Quick sort is a highly efficient sorting algorithm and is based on 
partitioning of array of data into smaller arrays. A large array is 
partitioned into two arrays one of which holds values smaller than 
the specified value, say pivot, based on which the partition is made
and another array holds values greater than the pivot value.
*/

#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#define MAX 10
#define MAXL 10000
//int random_nodup_array[MAX] = {4,6,3,2,1,9,7,8,5,0};
//int random_dup_array[MAX] = {4,5,3,2,1,9,7,8,5,9};
//int ascend_array[MAX] = {0,1,2,3,4,5,6,7,8,9};
//int descend_array[MAX] = {9,8,7,6,5,4,3,2,1,0};
//int equal_array[MAX] = {3,3,3,3,3,3,3,3,3,3};
int random_nodup_array[MAXL];
int random_dup_array[MAXL];
int ascend_array[MAXL];
int descend_array[MAXL];
int equal_array[MAXL];
int swaps = 0;
int comparisons = 0;

void printArray(int *array);
void quickSort(int *array, int left, int right);
int partition(int *array, int p, int end);
void setarrays();


void printArray(int *array){
    printf("Original:");
    int n = 100;
    for(int i = 0; i < n; i++){
        printf(" %d", array[i]);
    }
    quickSort(array, 0, MAXL-1);
    printf("\nSorted  :");
    for(int i = 0; i < n; i++){
        printf(" %d", array[i]);
    }
    printf(" ");
    printf("\nSwaps   : %d\n", swaps);
    printf("Comps   : %d\n\n", comparisons);
    swaps = 0;
    comparisons = 0;
}

void setarrays(){

    //ascend array
    for(int i = 0; i < MAXL; i++){
        ascend_array[i] = i;
    }
    //descending array
    for(int i = 0; i < MAXL; i++){
       descend_array[i] = MAXL - i;
    }
    //equal array
    for(int i = 0; i < MAXL; i++){
       equal_array[i] = 3;
    }
    //random duplicates
    srand(time(NULL));
    for(int i = 0; i < MAXL; i++){
        random_dup_array[i] = (rand() % (MAXL));
    }
    
    //random noduplicates
    for(int i = 0; i < MAXL; i++){//values 1 from MAXL

        //only i values are assigned, so we know they are unique

        int val = 0;//simple flag to stop while loop
        while(val == 0){
            int r = (rand() % (MAXL)); // random number between 0 and 10000
            if(random_nodup_array[r] == 0){ //if the index is 0, then change the value to the current i value
                random_nodup_array[r] = i;
                val = 1;
            }
            else{ //if its not 0, then find a new index
                r = (rand() % (MAXL));
            }

        }
    }
}


// Hoare parition scheme
// Created from Psuedocode on wikipedia
int partition(int *array, int p, int end){ 

    int pivot = array[((p+end)/2)]; // sets the pivot to the mid point
    int i = p - 1;
    int j = end + 1;
    int temp;

    while(true){ //run forever

        //I count when values are compared 
        do{                     // i is the first element larger than pivot
            i++;
            comparisons++;
        }while(array[i] < pivot); // until just before value of pivot

        do{                     // j is at the last element smaller than pivot
            j--;
            comparisons++;
        }while(array[j] > pivot); // until just greater value of pivot

        comparisons++;
        if(i >= j){            // if the two values intersect
            return j;          //return j - J is the new dividing point
        }

        // If the values of I and J did not intersect, then the values are not ordered
        // as i and j are brought one closer each time, and since they both dont equal 
        // the pivot, (array[i] > pivot) and (array[j] < pivot) then we can swap them
        swaps++;
        temp = array[i];
        array[i] = array[j];
        array[j] = temp;

        //start loop gain
    }

}

// Taken from Quicksort Pseudo-Code in lecture notes
void quickSort(int *array, int left, int right){

    //if left is less than right 
    if(left < right){//halts recursion when array cant be further subdivided

        //find q which is the partitioning index, then recursively call quickSort
        //on the left and right of the partitioning 
        int q = partition(array, left, right);
        quickSort(array, left, q);
        quickSort(array, q+1, right);
    }

}

int main(){

    setarrays();

//-------------------------------------------------------------------

    printf("Test    : Unique random values\n");
    printArray(random_nodup_array);

//-------------------------------------------------------------------

    printf("Test    : Random values\n");
    printArray(random_dup_array);

//------------------------------------------------------------------

    printf("Test    : Ascending values\n");
    printArray(ascend_array);

//------------------------------------------------------------------
    printf("Test    : Descending values\n");
    printArray(descend_array);

//------------------------------------------------------------------
    printf("Test    : Equal values\n");
    printArray(equal_array);   

    return 0;

}