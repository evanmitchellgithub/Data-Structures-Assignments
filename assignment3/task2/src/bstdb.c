#include "bstdb.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// Write your submission in this file
//
// A main function and some profiling tools have already been set up to test
// your code in the task2.c file. All you need to do is fill out this file
// with an appropriate Binary Search Tree implementation.
//
// The input data will be books. A book is comprised of a title and a word
// count. You should store both these values in the tree along with a unique
// integer ID which you will generate.
//
// We are aiming for speed here. A BST based database should be orders of
// magnitude faster than a linked list implementation if the BST is written
// correctly.
//
// We have provided an example implementation of what a linked list based
// solution to this problem might look like in the db/listdb.c file. If you
// are struggling to understand the problem or what one of the functions
// below ought to do, consider looking at that file to see if it helps your
// understanding.
//
// There are 6 functions you need to look at. Each is provided with a comment
// which explains how it should behave. The functions are:
//
//  + bstdb_init
//  + bstdb_add
//  + bstdb_get_word_count
//  + bstdb_get_name
//  + bstdb_stat
//  + bstdb_quit
//
// Do not rename these functions or change their arguments/return types.
// Otherwise the profiler will not be able to find them. If you think you
// need more functionality than what is provided by these 6 functions, you
// may write additional functions in this file.

//struct for each node in the BST
typedef struct Tree_Node Tree_Node;
struct Tree_Node {
    int ID;
	int word_count;
	int height;
	char name[100];
    Tree_Node *left, *right;
};

//global variables
int iter;
int debug;
Tree_Node *root;
Tree_Node *nodepointer;
int insertcount;


//extra function declarations
Tree_Node* tree_search ( Tree_Node* root, int datain );
Tree_Node* insert( Tree_Node* root, char *name, int word_count);
Tree_Node *leftrotate(Tree_Node *r);
Tree_Node *rightrotate(Tree_Node *r);
int getBalance(Tree_Node *r);
int height(Tree_Node *r);
int maxf(int a, int b);
void tree_delete (Tree_Node* root);
//for stat
int count(Tree_Node* r);
int total_height(Tree_Node* r);

int
bstdb_init ( void ) {
	// This function will run once (and only once) when the database first
	// starts. Use it to allocate any memory you want to use or initialize 
	// some globals if you need to. Function should return 1 if initialization
	// was successful and 0 if something went wrong.
	root = NULL;
	nodepointer = NULL;
	iter = 0;
	debug = 0;

	insertcount = 0;
	

	if(root != NULL || nodepointer != NULL || iter != 0 || debug != 0 || insertcount != 0 ){
		return 0;
	}
	else return 1;
}

int
bstdb_add ( char *name, int word_count ) {
	// This function should create a new node in the binary search tree, 
	// populate it with the name and word_count of the arguments and store
	// the result in the tree.
	//
	// This function should also generate and return an identifier that is
	// unique to this document. A user can find the stored data by passing
	// this ID to one of the two search functions below.
	//
	// How you generate this ID is up to you, but it must be an integer. Note
	// that this ID should also form the keys of the nodes in your BST, so
	// try to generate them in a way that will result in a balanced tree.
	//
	// If something goes wrong and the data cannot be stored, this function
	// should return -1. Otherwise it should return the ID of the new node

	// SELF BALANCED TREE
	// Example: AVL tree
	// Example function for an AVL tree were retrieved online and
	// then modified for our purposes
	// Source: https://www.geeksforgeeks.org/avl-tree-set-1-insertion/

	//iteration by 1 for every book ensures they are all identical
	iter++;

	//insert value and find new root
	root = insert(root, name, word_count);
	//set key to the pointer in the insert function which points to the node that has iter as the ID
	int key = nodepointer->ID;

	//if value wasnt added
	if(root == NULL){
		return -1;
	}

	insertcount++;
	//return key
	return key;

	
}
Tree_Node* insert( Tree_Node* r, char *name, int word_count){
	//using r as root as root is a global variable
	if(r == NULL){
		//if current pointer is empty, add a node
		Tree_Node *newnode = (Tree_Node *)malloc(sizeof(Tree_Node));
		newnode->left = NULL;
		newnode->right = NULL;
		newnode->ID = iter;
		newnode->word_count = word_count;
		strcpy(newnode->name, name);
		//sets height to 1
		newnode->height = 1;

		//pointer to the node that was just made
		//the function returns the original root, so this is 
		//necessary
		nodepointer = newnode; 

		//return the pointer to the new node
		return(newnode);
	}
	//if value is less, go to the left 
	if(iter < r->ID){
		r->left = insert(r->left, name, word_count);
	}
	//if value is greater, go to the right
	else if(iter > r->ID){
		r->right = insert(r->right, name, word_count);
	}
	else{	//equal keys not allowed
		return r;
	}
	// On the way down through the list
	// Update height value of this node
	// Reason: The height difference between left and right can never be more than 1
	// This ensures a balances array
	r->height = 1 + maxf(height(r->left),height(r->right));

	//find the current balance
	int balance = getBalance(r);

	// 4 Different cases for rotating

	/*
	Example:

	left-left case: T1, T2, T3 and T4 are subtrees

	     z                                      y 
        / \                                   /   \
       y   T4      Right Rotate (z)          x      z
      / \          - - - - - - - - ->      /  \    /  \ 
     x   T3                               T1  T2  T3  T4
    / \
  T1   T2

	Originally, z would be the root, with an inbalance on the left
	After rotation, y is the root, with x and z being subtrees and the
	tree is now balances

	*/
	//left-left
	if(balance > 1 && iter < r->left->ID){
		return rightrotate(r);
	}

	//right-right
	if(balance < -1 && iter > r->right->ID){
		return leftrotate(r);
	}

	//left-right
	if(balance > 1 && iter > r->left->ID){
		r->left = leftrotate(r->left);
		return rightrotate(r);
	}

	//right-left
	if(balance < -1 && iter < r->right->ID){
		r->right = rightrotate(r->right);
		return leftrotate(r);
	}

	return r;

}

int height(Tree_Node *r){ 
	//simply returns the height of the current pointer

	//reason for a function instead of simply doing root->left->height is because
	//root might be null, so that int value wouldnt exist
    if (r == NULL) 
        return 0; 
    return r->height; 
} 
int getBalance(Tree_Node *r){ 
	//gets the difference in height between the subnodes

	//same reason for the function as above
    if (r == NULL) 
        return 0; 
    return height(r->left) - height(r->right); 
} 
int maxf(int a, int b){ 
    return (a > b)? a : b; 
} 
Tree_Node *leftrotate(Tree_Node *r){
	//gives names to the right subnode and the right-left subnodes
	Tree_Node *y = r->right;
	Tree_Node *t2 = y->left;

	//perform rotation
	y->left = r;
	r->right = t2;

	//update heights
	r->height = maxf(height(r->left),height(r->right))+1;
	y->height = maxf(height(y->left),height(y->right))+1;

	return y;
}
Tree_Node *rightrotate(Tree_Node *r){
	//gives names to the left nodes and left-right nodes
	Tree_Node *y = r->left;
	Tree_Node *t2 = y->right;

	//perform rotation
	y->right = r;
	r->left = t2;

	//update heights
	r->height = maxf(height(r->left),height(r->right))+1;
	y->height = maxf(height(y->left),height(y->right))+1;

	return y;
}

int
bstdb_get_word_count ( int doc_id ) {
	// This is a search function. It should traverse the binary search tree
	// and return the word_count of the node with the corresponding doc_id.
	//
	// If the required node is not found, this function should return -1
	//return -1;

	Tree_Node* pointer;
	pointer = tree_search(root, doc_id);
	int wcount;

	if(pointer == NULL){
		return -1;
	}

	wcount = pointer->word_count;
	return wcount;
}

char*
bstdb_get_name ( int doc_id ) {
	// This is a search function. It should traverse the binary search tree
	// and return the name of the node with the corresponding doc_id.
	//
	// If the required node is not found, this function should return NULL or 0
	Tree_Node* pointer;
	pointer = tree_search(root, doc_id);

	if(pointer == NULL){
		return NULL;
	}

	return pointer->name;
}

Tree_Node* tree_search ( Tree_Node* r, int datain ){
	//if value equals the ID, then return it
	if( r->ID == datain){
    	return r; 
    }
	//else, put it into the left tree
    else if(r->ID > datain){
        return tree_search(r->left, datain);
    }
	//else, put it into the right tree
    else if(r->ID < datain){
        return tree_search(r->right, datain);
    }
	//nothing was found, return null
    else return NULL;
}

void
bstdb_stat ( void ) {
	// Use this function to show off! It will be called once after the 
	// profiler ends. The profiler checks for execution time and simple errors,
	// but you should use this function to demonstrate your own innovation.
	//
	// Suggestions for things you might want to demonstrate are given below,
	// but in general what you choose to show here is up to you. This function
	// counts for marks so make sure it does something interesting or useful.
	//
	//  + Check if your tree is balanced and print the result
	//
	//  + Does the number of nodes in the tree match the number you expect
	//    based on the number of insertions you performed?
	//
	//  + How many nodes on average did you need to traverse in order to find
	//    a search result? 
	//
	//  + Can you prove that there are no accidental duplicate document IDs
	//    in the tree?

	//check number of nodes in the tree
	int searchtotal;
	int total_height_left, total_height_right, bal;

	searchtotal = count(root);
	printf("NODE COUNT: \n");
	printf("The total number inserted: %d\n", insertcount);
	printf("The total number found   : %d\n", searchtotal);

	if(insertcount == searchtotal){
		printf("The total number of nodes is as expected.\n");
	}
	else{
		printf("The total number of nodes is not as expected.\n");
	}

	//find the balance of the trees

	//height of left branch
	total_height_left = 1 + total_height(root->left);

	//height of right branch
	total_height_right = 1+ total_height(root->right);

	bal = total_height_left - total_height_right;
	printf("\nBalance check: \n");
	printf("Total height of left branch  : %d \n", total_height_left);
	printf("Total height of right branch : %d \n", total_height_right);

	if(bal <= 1 && bal >= -1){
		printf("BST is balanced.\n");
	}
	else{
		printf("BST is not balanced.\n");
	}
}

int count(Tree_Node* r){
	//start count at 1 node
	int c = 1;
	if(r == NULL){
		return 0;
	}
	else{
		//add number of nodes in below nodes
		c = c + count(r->left);
		c = c + count(r->right);
		//return c
		return c;
	}
}

int total_height(Tree_Node* r){
	int val;
	//return -1 if root is empty
	if(r == NULL){
		return -1;
	}
	//else, find the highest height in the below nodes
	else{
		val = 1 + maxf(total_height(r->left), total_height(r->right));
		return val;
	}
}

void
bstdb_quit ( void ) {
	// This function will run once (and only once) when the program ends. Use
	// it to free any memory you allocated in the course of operating the
	// database.

	//delete the tree
	tree_delete(root);
	printf("\nTree deleted.\n");
}

void tree_delete (Tree_Node* r){
	// previous delete function from task1 caused stack overflow
	// i.e. it left early, and never finished.
	// this is an updated delete to avoid large chains of recursions
	// source: https://stackoverflow.com/questions/42799209/fastest-way-to-delete-a-binary-tree-in-c

	// updated code
	// separate the previous delete_tree
	// So, the tree does not go down both the left and right tree at once now, only one
	// as a result, overflow is unlikely to occur
	
	// if the left tree doesnt = NULL
	if(r->left){
		//go into the left subtree
		tree_delete(r->left);
		//delete it
		free(r->left);
	}
	//if the right tree doesnt = NULL
	if(r->right){
		//go into the right subtree
		tree_delete(r->right);
		//delete it
		free(r->right);
	}
}