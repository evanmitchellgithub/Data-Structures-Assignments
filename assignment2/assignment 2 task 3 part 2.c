

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define MAX 10
#define MAXL 10000
#define max_string_size 100
#define array_size 18625
int swaps = 0;
long comparisons = 0;

typedef struct ign ign;
struct ign {
    ign* next;
    char title[max_string_size];
    char platform[max_string_size];
    int score;
    char release_year[max_string_size];

};

struct ign games[array_size];
//struct ign top10[10];
struct ign top10[array_size];

void selectionSort();
void printArray();
int next_field ( FILE *csv , char *buffer , int max_length );

//basic parser, modified from pokemon
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
        //printf("%s\n", buffer);
        buffer[i++] = current_char; 
        current_char = fgetc (csv);
    }
return 0;
}

void printArray(){
    printf("Original loaded\n");  
    selectionSort();
    printf("\nSorted!\n");
    printf(" ");
    printf("\nSwaps   : %d\n", swaps);
    printf("Comps   : %d\n\n", comparisons);
    swaps = 0;
    comparisons = 0;
}

// This is the selection sort I've chosen to implement for task 2
void selectionSort(){

    int mIndex, mIndexchange, temp;
    char temptitle[max_string_size], tempyear[max_string_size], tempplat[max_string_size];
    int n = array_size;
    // for each value of the array, i, go through the array looking
    // at other values, j, and see if its smaller
    for(int i = 0; i < n; i++){

        mIndex = i;
        mIndexchange = mIndex;
        for(int j = i+1; j < n; j++){
            //iterate comparisons 
            comparisons++;

            if(games[j].score < games[mIndex].score){
                //set m_index to the index with the smallest value associated
                mIndex = j;
            }
        }
        if(mIndex != mIndexchange){
            //swap the first element and the minimum found element
            temp = games[mIndex].score;
            strcpy(temptitle , games[mIndex].title );
            strcpy(tempplat , games[mIndex].platform );
            strcpy(tempyear, games[mIndex].release_year );

            games[mIndex].score = games[i].score;
            strcpy(games[mIndex].title , games[i].title );
            strcpy(games[mIndex].platform , games[i].platform );
            strcpy(games[mIndex].release_year, games[i].release_year );

            games[i].score = temp;
            strcpy(games[i].title , temptitle );
            strcpy(games[i].platform , tempplat );
            strcpy(games[i].release_year, tempyear );

            //iterate swaps counter
            swaps++;
        }
    }
}

int main(){

    FILE * csv;
    //opening the file
    csv = fopen ("ign.csv","r");
    printf("ign.csv loaded!\n");

    char buffer[max_string_size];
    int charId;

    //gets rid of the first 4 words
    for(int x = 0; x < 4; x++){
        next_field (csv, buffer,  max_string_size );     
    }
    //stores names in a struct
    for(int l = 0; l < array_size; l++){
        //this for loop resets the buffer so previous values dont interact with the next buffer's values
        for(int j = 0; j < max_string_size; j++){
            buffer[j] = '\0';
        }

        if(charId == 2){break;} 

        charId = next_field (csv, buffer,  max_string_size );
        for(int j = 0; j < max_string_size; j++){
            games[l].title[j] = buffer[j];
        }
    
        charId = next_field (csv, buffer,  max_string_size );
        for(int j = 0; j < max_string_size; j++){
            games[l].platform[j] = buffer[j];
        }

        charId = next_field (csv, buffer,  max_string_size );
        games[l].score = atoi(buffer);     
    
        charId = next_field (csv, buffer,  max_string_size );
        for(int j = 0; j < max_string_size; j++){
            games[l].release_year[j] = buffer[j];
        }
    }
    //prints 100 values of the original and sorted arrays
    printArray();

    // print the top 10 games
    int flag = 0;
    int count = 0;
    int i = array_size -1;
    printf("Top 10 games!\n");
    while(count <= 10){

        for(int x = 0; x < count-1; x++){
            //printf("getshere\n");
            if(strcmp(games[i].title, top10[x].title) == 0){
                flag = 1;
                count--;
                break;
            }
        }

        if(flag == 0){
            printf("%s, ", games[i].title);
            printf("%s, ", games[i].platform);
            printf("%d, ", games[i].score);
            printf("%s\n", games[i].release_year);
        }

        count++;
        i--;
        flag = 0;
        strcpy(top10[count].title , games[i].title );
    }
    flag = 0;
    i = array_size - 1;
    char input[max_string_size];
    printf("\nDo you want to see all other games with a score of 10?\n");
    scanf("%s", input);
    if(input[0] == 'y'){
        while(games[i].score == 10){

            for(int x = 0; x < count-1; x++){
                //printf("getshere\n");
                if(strcmp(games[i].title, top10[x].title) == 0){
                    flag = 1;
                    break;
                }
            }

            if(flag == 0){
                printf("%s, ", games[i].title);
                printf("%s, ", games[i].platform);
                printf("%d, ", games[i].score);
                printf("%s\n", games[i].release_year);
            }

            count++;
            i--;
            flag = 0;
            strcpy(top10[count].title , games[i].title );
        }
    }
    return 0;

}