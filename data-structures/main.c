#include "tree.h"
#include <stdlib.h>
#include <stdio.h>

int main(){
	int instances,i;
	scanf("%d\n",&instances);
	for(i=0; i<instances; i++){
		int sizeS,initialValue,limitValue,minimumValue;
		scanf("%d %d %d %d",&sizeS, &initialValue, &limitValue, &minimumValue);
		int set[sizeS],j;
		for(j=0; j<sizeS; j++){
			scanf("%d",&set[j]);
		}

		
		Tree *t=CreateNode(0,initialValue,NULL,NULL,initialValue);
		
		for(j=0; j<sizeS; j++){
			buildTree(t,set[j],limitValue);
		}

		int temp=-1;
		int best = bestValue(t,limitValue,&temp,sizeS);
		if(best >= minimumValue){
			printf("S,%d\n",best);
		}
		else{
			printf("N,%d\n",best);
		}
		FreeTree(t);
		
	}
	return 0;
}
