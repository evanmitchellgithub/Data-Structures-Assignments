#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/* 
This is the code for Assignment 1, part 4
*/

#define max_string_size  70
#define array_size  60172   
#define hash_array_size  62071
#define next_largest_prime  62057

typedef struct names names;
struct names {
    long int key;
    names* next;
    char surname[max_string_size];
    long int person_id;
    char deposition_id[max_string_size];
    char forename[max_string_size];
    long int age;
    char person_type[max_string_size];
    char gender[max_string_size];
    char nationality[max_string_size];
    char religion[max_string_size];
    char occupation[max_string_size];

};

struct names surnames[array_size];
struct names hash_array[hash_array_size];
long int num_terms = 0;
long int collision_count = 0;
int next_field ( FILE *csv , char *buffer , int max_length );
void print_list (names* list);
void add_node(names** list, long int x);
void delete_list(names** list);
int hash2(char* s);
void insert_function( long int key, long int x);

void add_node(names** list, long int x){

    names* newNode = (names*)malloc( sizeof( names ) ); 
    newNode->person_id = surnames[x].person_id;
    newNode->age= surnames[x].age;
    for(int i = 0; i < max_string_size; i++){
        newNode->deposition_id[i] = surnames[x].deposition_id[i] ;
        newNode->surname[i]  = surnames[x].surname[i] ;
        newNode->forename[i]  = surnames[x].forename[i] ;
        newNode->person_type[i]  = surnames[x].person_type[i] ;
        newNode->gender[i]  = surnames[x].gender[i] ;
        newNode->nationality[i]  = surnames[x].nationality[i] ;
        newNode->religion[i]  = surnames[x].religion[i] ;
        newNode->occupation[i]  = surnames[x].occupation[i] ;
    }
    newNode->next = *list;
    *list=newNode; // and not list = &newNode; as you can't change a parameter in C
    
}

void print_list (names* list){
    names* node = list;
    while(node!=NULL){
        printf("%d\t", node->person_id);
        printf("%s\t", node->deposition_id);
        printf("%s   \t\t", node->surname);
        printf("%s   \t\t", node->forename);
        printf("%d\t", node->age);
        printf("%s\t", node->person_type);
        printf("%s\t", node->gender);
        printf("%s\t", node->nationality);
        printf("%s\t", node->religion);
        printf("%s\n", node->occupation);
        node = node ->next;

    }
}

void insert_function( long int key, long int x){

    int tempkey, loopcount = 0;
    tempkey = key;
    

    if(hash_array[tempkey].key == -999){//if current key slot is free, add the data
        hash_array[tempkey].key = key;
        hash_array[tempkey].person_id = surnames[x].person_id;
        hash_array[tempkey].age = surnames[x].age;

        strcpy(hash_array[tempkey].deposition_id , surnames[x].deposition_id );
        strcpy(hash_array[tempkey].surname , surnames[x].surname );
        strcpy(hash_array[tempkey].forename, surnames[x].forename );
        strcpy(hash_array[tempkey].person_type , surnames[x].person_type );
        strcpy(hash_array[tempkey].gender , surnames[x].gender );
        strcpy(hash_array[tempkey].nationality , surnames[x].nationality );
        strcpy(hash_array[tempkey].religion , surnames[x].religion );
        strcpy(hash_array[tempkey].occupation , surnames[x].occupation );
        num_terms++;
        return;
    }

    else{//if not
        while(loopcount < array_size){
            if(tempkey == hash_array_size){
                tempkey = 0;//so it stays within the array
            }
            //if the name and key are the same, and a node to the linked list
            else if(hash_array[tempkey].key == key && strcmp(hash_array[tempkey].surname, surnames[x].surname) == 0){
                add_node(&hash_array[tempkey].next, x);
                return;
            }
            //if the slot isnt free, add a collision
            else if(hash_array[tempkey].key != -999){
                collision_count++;
                tempkey++;
            }
            //if the slot is free, add it
            else if(hash_array[tempkey].key == -999){
                hash_array[tempkey].key = key;
                hash_array[tempkey].person_id = surnames[x].person_id;
                hash_array[tempkey].age = surnames[x].age;

                strcpy(hash_array[tempkey].deposition_id , surnames[x].deposition_id );
                strcpy(hash_array[tempkey].surname , surnames[x].surname );
                strcpy(hash_array[tempkey].forename, surnames[x].forename );
                strcpy(hash_array[tempkey].person_type , surnames[x].person_type );
                strcpy(hash_array[tempkey].gender , surnames[x].gender );
                strcpy(hash_array[tempkey].nationality , surnames[x].nationality );
                strcpy(hash_array[tempkey].religion , surnames[x].religion );
                strcpy(hash_array[tempkey].occupation , surnames[x].occupation );
                
                num_terms++; 
                return;     
            }
        loopcount++;
        }

    }

}

void delete_list(names** list){ // recursive
    //This function is not actually used, however I have left it i to show how I would delete the lists
    //I did not have enough time to debug a segmentation fault while
    //deleteing the lists
    if(list){
        if(*list){
            names* next = (*list)->next;
            printf("About to delete node: ");
            free(*list);
            *list = NULL;
            printf("Done\n");
            delete_list(&next);
        }
    }
    
    
}

int hash2(char* s){//hash function from part 2
    int hash = 0;
    int m = hash_array_size;
    while(*s){
        hash = (61*hash + *s)%m;
        s++;
    }

    return (hash % hash_array_size);
}

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

int main(){

    FILE * csv;
    //opening the file
    csv = fopen ("people.csv","r");
    printf("people.csv loaded!\n");

    char buffer[max_string_size], input[max_string_size];
    long int key, find_key;
    int freq_count = 0;
    int i = 0;

    //initialise hash_array
    for(int a = 0; a < hash_array_size; a++){//settings keys to be free
        hash_array[a].key = -999;
    }
    for(int a = 0; a < hash_array_size; a++){//setting the pointers at each position to nothing
        hash_array[a].next = NULL;
    }
    for(int a = 0; a < max_string_size; a++){
        input[a] = ' ';
    }

    //gets rid of the first 10 words
    for(int x = 0; x < 10; x++){
            next_field (csv, buffer,  max_string_size );
            
    }
    //stores names in a struct
    for(int l = 0; l < array_size; l++){

        
        //this for loop resets the buffer so previous values dont interact with the next buffer's values
        for(int j = 0; j < max_string_size; j++){
            buffer[j] = '\0';
        }

        int charId = next_field (csv, buffer,  max_string_size );
        if(charId == 2){break;} 

        surnames[l].person_id = atoi(buffer);

        charId = next_field (csv, buffer,  max_string_size );
        for(int j = 0; j < max_string_size; j++){
            surnames[l].deposition_id[j] = buffer[j];
        }
        //strcpy(surnames[l].deposition_id ,buffer );
    
        charId = next_field (csv, buffer,  max_string_size );
        for(int j = 0; j < max_string_size; j++){
            surnames[l].surname[j] = buffer[j];
        }
        //strcpy(surnames[l].surname ,buffer );       
    
        charId = next_field (csv, buffer,  max_string_size );
        for(int j = 0; j < max_string_size; j++){
            surnames[l].forename[j] = buffer[j];
        }
        //strcpy(surnames[l].forename ,buffer );
    
        charId = next_field (csv, buffer,  max_string_size );
        surnames[l].age = atoi(buffer);
    
        charId = next_field (csv, buffer,  max_string_size );
        for(int j = 0; j < max_string_size; j++){
            surnames[l].person_type[j] = buffer[j];
        }
        //strcpy(surnames[l].person_type ,buffer );            

        charId = next_field (csv, buffer,  max_string_size );
        for(int j = 0; j < max_string_size; j++){
            surnames[l].gender[j] = buffer[j];
        }
        //strcpy(surnames[l].gender ,buffer );
    
        charId = next_field (csv, buffer,  max_string_size );
        for(int j = 0; j < max_string_size; j++){
            surnames[l].nationality[j] = buffer[j];
        }
        //strcpy(surnames[l].nationality ,buffer );

        charId = next_field (csv, buffer,  max_string_size );
        for(int j = 0; j < max_string_size; j++){
            surnames[l].religion[j] = buffer[j];
        }
        //strcpy(surnames[l].religion ,buffer );

        charId = next_field (csv, buffer,  max_string_size );
        for(int j = 0; j < max_string_size; j++){
            surnames[l].occupation[j] = buffer[j];
        }
        //strcpy(surnames[l].occupation ,buffer );

    }//end of storing names in a struct

    //store names in the hash array
    for(int x = 0; x < array_size; x++){
        i = 0;
        key = hash2(surnames[x].surname);
        insert_function( key,  x);
    }

    printf("\nCapacity  : %d\n", hash_array_size);
    printf("num_terms : %d\n", num_terms);
    printf("Collisions: %d\n", collision_count);
    int load = (num_terms*100)/(hash_array_size);
    printf("Load      : %d%%\n", load);
    printf("\nEnter term to get frequency or type quit to quit:\n");
    scanf("%s", input);

    //finding the data
    find_key = hash2(input);
    
    int match = 0;
    int found = 0;
    int w = find_key;

    //keeps running the finder until quit is typed
    while(input[0] != 'q'){

        while(hash_array[w].key != -999){
            if(w == hash_array_size){
                w = 0;
            }
            //if the names are equal, print out the list
            int string_cmp = strcmp(input, hash_array[w].surname);
            if(string_cmp == 0){
                printf("PersId   DepId          Surname                 Forename            Age         PType           Gender   Nation.        Rel.            Occup.\n");
                if(hash_array[w].next != NULL){
                    print_list (hash_array[w].next);
                }
                //prints out the names stored in the array, before the list
                printf("%d\t", hash_array[w].person_id);
                printf("%s\t", hash_array[w].deposition_id);
                printf("%s   \t\t", hash_array[w].surname);
                printf("%s   \t\t", hash_array[w].forename);
                printf("%d\t", hash_array[w].age);
                printf("%s\t", hash_array[w].person_type);
                printf("%s\t", hash_array[w].gender);
                printf("%s\t", hash_array[w].nationality);
                printf("%s\t", hash_array[w].religion);
                printf("%s\n", hash_array[w].occupation);
                found = 1;
                break;
            }
            else{
                w++;
            }
        }
        //If nothing is found
        if(found == 0){
            printf("%s is not in the table.\n", input);
            match = 0;
        }

        //reset variables
        freq_count = 0;
        match = 0;
        found = 0;
        i = 0;

        printf("\nEnter term to get frequency:\n");
        scanf("%s", input);
        find_key = hash2(input);
        w = find_key;
        //restart while loop
    }

    //Then delete linked lists

}