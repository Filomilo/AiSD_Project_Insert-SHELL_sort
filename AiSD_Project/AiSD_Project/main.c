#include <stdio.h>
#include <stdlib.h>
#include "sort_project.h"

int main()
{
	int min = 0;
	int max = 10;
	int N = 100000;
	int* array;
	 array = (int*)calloc(N, sizeof(int));
	 
	
	fill_array_reverse(array, N);
	//print_array(array, N);

	printf("czas sortoownaia insert sort dla %d elementow: %.3fs\n", N, calc_time(array, N, insert_sort));
	printf("czas sortoownaia shell sort dla %d elementow: %.3fs\n", N, calc_time(array, N, shell_sort));
	//shell_sort (array, N);
	//insert_sort(array, N);
	//printf("\n");
	//print_array(array, N);
	
	printf("\n\n\n");
}