#include "time.h"
#include "utils.h"

struct time* new_time(){
	struct time * t = (time *) malloc(sizeof(time));
	t->h=0;
	t->m=0;
	t->s=0;
	t->ms=0;
	return t;
}

void string_to_time(char* s, struct time* t){
	int n, readcount, offset=0;
	char str[3];
	str[0]='\0';
	char str2[MAX_BUFFER];
	str2[0]='\0';
	strcpy(str2,&s[2]);
	while(sscanf(str2+offset,"%d%s%n", &n, str,&readcount) == 2){
		if(strcmp(str,"h") == 0){
			t->h=n;
		}
		else if(strcmp(str,"m") == 0){
			t->m=n;
		}
		else if(strcmp(str,"s") == 0){
			t->s=n;
		}
		else if(strcmp(str,"ms") == 0){
			t->ms=n;
		}
		offset+=readcount;
	}
}

void time_to_string(struct time* t, char* result){
	char temp[10];
	temp[0]='\0';
	if(t->h > 0){
		sprintf(temp,"%dh",t->h);
		strcat(result,temp);
	}
	if(t->m > 0){
		if(t->h ==0){
			sprintf(temp,"%dm", t->m);
		}
		else{
			sprintf(temp," %dm", t->m);
		}
		strcat(result,temp);
	}
	if(t->s > 0){
		if(t->m > 0 || t->h >0){
			sprintf(temp," %ds", t->s);
		}
		else{
			sprintf(temp, "%ds", t->s);
		}
		strcat(result,temp);
	}
	if(t->ms >0){
		if(t->s > 0 || t->m > 0 || t->h > 0){
			sprintf(temp," %dms", t->ms);
		}
		else{
			sprintf(temp,"%dms", t->ms);
		}
		strcat(result,temp);
	}
}

int compare_time(const void *a, const void *b){
	struct time* t1 = *(struct time**)a;
	struct time* t2 = *(struct time**)b;

	if(t1->h > t2->h)
		return 1;
	else if(t1->h < t2->h)
		return -1;
	
	else{
		if(t1->m > t2->m)
			return 1;
		else if(t1->m < t2->m)
			return -1;
		else{
			if(t1->s > t2->s)
				return 1;
			else if(t1->s < t2->s)
				return -1;
			else{
				if(t1->ms > t2->ms)
					return 1;
				else if( t1->ms < t2->ms)
					return -1;
			}
		}
		return 0;
	}
	
	

}

void free_data(struct time **t, int n){
	int i;
	for(i=0; i < n; i++){
		free(t[i]);
	}

}