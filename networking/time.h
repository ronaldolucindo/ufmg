#ifndef TIME_H_INCLUDED
#define TIME_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct time{
	int h;
	int m;
	int s;
	int ms

	
} time;

// alocates and initializes a new time
struct time* new_time();

// stores data from a string in a struct time t
void string_to_time(char* s, struct time* t);

// stores data from a struct time t in a string result
void time_to_string(struct time* t, char* result);

// auxiliar function used in qsort that defines the criterias to sorting data
int compare_time(const void *a, const void *b);

// free spaces allocated to a array of pointers struct time
void free_data(struct time **t, int n);
#endif