
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
long comparisons = 0;

void selectionSort(int *array);
int partition(int *array, int p, int end);
void printArray(int *array);
void setarrays();

void printArray(int *array){
    printf("Original:");
    int n = 10;
    for(int i = 0; i < n; i++){
        printf(" %d", array[i]);
    }
    selectionSort(array);
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
    //random duplicates
    for(int i = 0; i < MAXL; i++){
        int val = 0;
        while(val == 0){
            int r = (rand() % (MAXL));
            if(random_nodup_array[r] == 0){
                random_nodup_array[r] = i;
                val = 1;
            }
            else{
                r = (rand() % (MAXL));
            }

        }
    }
}

// This is the selection sort I've chosen to implement for task 2
void selectionSort(int *array){

    int mIndex, mIndexchange, temp;
    // for each value of the array, i, go through the array looking
    // at other values, j, and see if its smaller
    for(int i = 0; i < MAXL; i++){

        mIndex = i;
        mIndexchange = mIndex;
        for(int j = i+1; j < MAXL; j++){
            //iterate comparisons 
            comparisons++;

            if(array[j] < array[mIndex]){
                //set m_index to the index with the smallest value associated
                mIndex = j;
            }
        }
        if(mIndex != mIndexchange){
            //swap the ith element and the minimum found element
            temp = array[mIndex];
            array[mIndex] = array[i];
            array[i] = temp;

            //iterate swaps counter
            swaps++;
        }
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