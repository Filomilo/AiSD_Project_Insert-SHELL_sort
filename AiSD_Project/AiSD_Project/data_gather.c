#include "sort_project.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

float calc_time(int* array, int N, void (*sort)(int*, int))
{
	time_t start= clock(NULL);
	int* new = calloc(N, sizeof(int));
	duplicate_array(array, new, N);
	sort(new, N);
	time_t stop = clock(NULL);
	return (double)(stop-start)/CLOCKS_PER_SEC;
}