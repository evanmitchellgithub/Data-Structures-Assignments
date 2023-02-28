

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>


#define array_size 30

char array[array_size] = {'F', 'L', 'O', 'C', 'C', 'I', 'N', 'A', 'U', 'C', 'I', 'N', 'I', 'H', 'I', 'L', 'I', 'P', 'I', 'L', 'I', 'F', 'I', 'C', 'A', 'T', 'T', 'I', 'O', 'N'};

typedef struct Tree_Node Tree_Node;
struct Tree_Node {
    char data;
    Tree_Node *left, *right;

};

void tree_insert(Tree_Node ** root, char data);
Tree_Node* tree_search ( Tree_Node* root, char data );
void tree_print_sorted (Tree_Node* root);
void tree_delete (Tree_Node* root);

//inserts value into the correct place in the tree recursively
void tree_insert(Tree_Node** root, char datain){
    //if node is free, add values
    if((*root) == NULL) {
        Tree_Node *newnode = (Tree_Node *)malloc(sizeof(Tree_Node));
        newnode->left = NULL;
        newnode->right = NULL;
        newnode->data = datain;
        *root = newnode;
        return;
    }
    // if data is less than or equal, go left
    if((*root)->data >= datain) {
        tree_insert(&(*root)->left, datain);
    } 
    // if data is greater, go right
    else if((*root)->data < datain) {
        tree_insert(&(*root)->right, datain);
    }

}


//return a pointer if a value exists in the tree, otherwise return NULL
Tree_Node* tree_search ( Tree_Node* root, char datain ){
    //root is empty, return root
    if(root == NULL){
        return root;
    }
    //if value = data, return root
    else if( root->data == datain){
        return root; 
    }
    //go down left
    else if(root->data > datain){
        return tree_search(root->left, datain);
    }
    //go down right
    else if(root->data < datain){
        return tree_search(root->right, datain);
    }

    else return NULL;

}

//traverse the tree, printing the data held in every node, in smallest-to-greatest sorted order
void tree_print_sorted (Tree_Node* root){
    if(root){

        tree_print_sorted(root->left);
    
        printf("%c ", root->data);

        tree_print_sorted(root->right);
    }
}

void tree_delete (Tree_Node* root){

    //recursively delete the left and right branches
    if(root!= NULL){
        //go down left branch
        tree_delete(root->left);
        //go down right branch
        tree_delete(root->right);
        //delete the current node at the end of the branch
        free(root);

    }
}



int main(){

    //Null pointer for start of tree
    Tree_Node *root = NULL;
    char randomletter;
    Tree_Node* letterpointer;


    //prints the unsorted array first
    printf("Original list: \n");
    for(int i = 0; i < array_size; i++){
        printf("%c ", array[i]);
    }
    printf("\n");

    //adds the array to a binary tree
    for(int i = 0; i< array_size; i++){
        tree_insert(&root, array[i]);
        //insert(&root, array[i]);
    }

    //prints the binary tree
    printf("List in the binary tree:\n");
    tree_print_sorted (root);

    srand(time(NULL));
    for(int i = 0; i < 2; i++){
        //creates a random letter
        randomletter = 'A' + (rand() %26);

        letterpointer = tree_search(root, randomletter );

        printf("\nLetter to be found: %c \n", randomletter);
        if (letterpointer != NULL){
            printf("%c is in the tree.", letterpointer->data);
        }
        else{
            printf("%c is not in the tree.", randomletter);
        }

    }

    //delete the tree.
    tree_delete(root);

    printf("\nTree deleted");

}