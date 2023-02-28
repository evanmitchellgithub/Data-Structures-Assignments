#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

/* 
This is the code for Assignment 1, part 2

It takes in the csv data, so a struct and the csv parser is needed.
Then, it passes the names to a hash function.
Then, it passes these into a hash table. 
*/

#define max_string_size  50
#define array_size  51
#define hash_array_size  59
#define next_largest_prime  53
int num_terms = 0;
int collision_count = 0;

struct names {
    int key;
    char surname[50];//compiler wouldnt let me use max_string_size
    int frequency;
};

struct names surnames[array_size];
struct names hash_array[hash_array_size];

int next_field ( FILE *csv , char *buffer , int max_length );
int hash2(char* s);
void insert_function( int key, int x);


void insert_function( int key,  int x){

    int tempkey, loopcount = 0;
    tempkey = key;
    if((strcmp(hash_array[key].surname, surnames[x].surname) == 0)){
        collision_count--;
    }
    if(hash_array[key].key == -999){
        hash_array[key].key = key;
        for(int e = 0; e < max_string_size; e++){
        hash_array[key].surname[e] = surnames[x].surname[e];
        }
        hash_array[key].frequency++;
        num_terms++;  
        return;
    }
    else{
        //collision_count++;
        while(loopcount < array_size){
            if(tempkey == hash_array_size){
                tempkey = 0;
            }
            if(hash_array[tempkey].key == key && strcmp(hash_array[tempkey].surname, surnames[x].surname) == 0){
                hash_array[tempkey].frequency++;
                return;
            }
            if(hash_array[tempkey].key != -999){
                collision_count++;
                tempkey++;
            }
           
                if(hash_array[tempkey].key == -999){
                    hash_array[tempkey].key = key;
                    for(int e = 0; e < max_string_size; e++){
                    hash_array[tempkey].surname[e] = surnames[x].surname[e];
                    }
                    hash_array[tempkey].frequency++;
                    num_terms++; 
                    return;
                    
                }
            
        //tempkey++;
        loopcount++;
        }

    }


}

int hash2(char* s){
    int hash = 0;
    int m = hash_array_size;
    while(*s){
        hash = (29*hash + *s)%m;
        s++;
    }

    return (hash % hash_array_size);
}

int next_field ( FILE *csv , char *buffer , int max_length ){
    
    char current_char;
    current_char = fgetc (csv);
    int i = 0;

    while( i < max_length){ 

        if(current_char == '\n'){
            buffer[i] = '\0';
            return 0; //leaves function
        }

        if(current_char == ','){
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


int main(){

    FILE * csv;
    //opening the file
    csv = fopen ("names.csv","r");
    printf("names.csv loaded!\n");

    char buffer[max_string_size], input[max_string_size];

    int key, find_key;
    int freq_count = 0;
    int equal = 0;
    int str_eq = 0;

    //stores names in a struct
    for(int i = 0; i < array_size; i++){

        //this for loop resets the buffer so previous values dont interact with the next buffer's values
        for(int j = 0; j < max_string_size; j++){
            buffer[j] = '\0';
        }
        int charId = next_field (csv, buffer,  array_size );

        for(int k = 0; k <= array_size; k++){
            surnames[i].surname[k] = tolower(buffer[k]);     
        }

        if(charId == 2){break;}  
        
    }

    //initialise hash_array
    for(int a = 0; a < hash_array_size; a++){
        hash_array[a].key = -999;
    }
    for(int a = 0; a < hash_array_size; a++){
        hash_array[a].frequency = 0;
    }
    //initialise input array
    for(int a = 0; a < max_string_size; a++){
        input[a] = ' ';
    }

    //use the names to find the keys, then add to the array
    for(int x = 0; x < array_size; x++){//=================================================================
        key = hash2(surnames[x].surname);
        insert_function( key,  x);

    }//=================================================================
    printf("Capacity  : %d\n", hash_array_size);
    printf("num_terms : %d\n", num_terms);
    printf("Collisions: %d\n", collision_count);
    int load = (num_terms*100)/(hash_array_size);
    printf("Load      : %d%%\n", load);
    printf("Enter term to get frequency or type quit to quit:\n");
    scanf("%s", input);


    find_key = hash2(input);
    
    int w = find_key;
    int match = 0;
    int loop_count = 0;
    int found = 0;

    //keeps running the finder until quit is typed
    while(input[0] != 'q'){

        //keeps running the loop until a space is found, also until it has done a full search of the array ( in case it was full

        for(int w = 0; w < hash_array_size; w++){
            //check if the strings are equal
            int string_cmp = strcmp(input, hash_array[w].surname);

            if(string_cmp == 0){
                //printf("\ngh:\n"); 
                freq_count = hash_array[w].frequency;
                found = 1;
                match = 0;
            }
        }
        
        
        if(found == 0){
            printf("%s is not in the table.\n", input);
            match = 0;
        }

        if(found == 1){
        printf("%s", input);
        printf(" is found ");
        printf("%d", freq_count);
        printf(" times.\n");
        }

        //reset variables
        loop_count = 0;
        freq_count = 0;
        match = 0;
        found = 0;

        printf("\nEnter term to get frequency:\n");
        scanf("%s", input);
        find_key = hash2(input);

        w = find_key;
    }//End of while loop========================================================================================================

}
