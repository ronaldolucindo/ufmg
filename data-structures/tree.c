#include "tree.h"
#include <stdlib.h>
#include <stdio.h>

struct Tree* CreateNode(int id,int key,struct Tree *left, struct Tree *right, int sum){
	struct Tree* node = (Tree *) malloc(sizeof(Tree));
	node->id=id;
	node->key=key;
	node->left=left;
	node->right=right;
	node->sum=sum;
	return node;
}

void buildTree(struct Tree *t, int key, int limitValue){
	
		if(t!=NULL){
			if(t->left==NULL && t->right == NULL){
				int negative= -1*(key);
				if(negative+t->sum >= 0 && negative+t->sum <=limitValue){
					t->left=CreateNode(t->id+1,negative,NULL,NULL,t->sum+negative);
				}
				if(key + t->sum >=0 && key + t->sum <= limitValue){
					t->right=CreateNode(t->id+1,key,NULL,NULL,t->sum+key);
				}
			}
			else{
				buildTree(t->left,key,limitValue);
				buildTree(t->right,key,limitValue);
			}

		}
	
}


int bestValue(struct Tree* t, int limitValue,int *best,int size){
	
	if(t!=NULL){
		if(t->left==NULL && t->right==NULL){
			
			if(t->sum > *best && t->id==size){
				*best=t->sum;
			}
		}
		else{
				bestValue(t->left,limitValue,best,size);
				bestValue(t->right,limitValue,best,size);
		}
	}
	return *best;
}

void FreeTree(struct Tree* t){
	 if(t!=NULL){
			FreeTree(t->left);
			FreeTree(t->right);
			free(t);
	}
}