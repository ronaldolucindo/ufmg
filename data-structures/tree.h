#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

typedef struct Tree{
	int id; //used to specify node's height
	int key;
	struct Tree* left;
	struct Tree* right;
	int sum;
}Tree;

//Creates a new node with the specified parameters
struct Tree* CreateNode(int id,int key,struct Tree *left, struct Tree *right, int sum);

//Builds the decision tree with the valid solutions 
void buildTree(struct Tree *t, int key, int limitValue);

//Find the greatest possible value
int bestValue(struct Tree* t, int limitValue, int *best, int size);

//Free memory alocated 
void FreeTree(struct Tree* t);


#endif