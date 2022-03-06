#include <stdio.h>
#include <stdlib.h>
#include "sort_project.h"

int main()
{
	int min = 0;
	int max = 10;
	int N = 10;
	int* array;
	 array = (int*)calloc(N, sizeof(int));
	 
	
	fill_array_reverse(array, N, min, max);
	print_array(array, N);
	shell_sort (array, N);
	printf("\n");
	print_array(array, N);
	
	printf("\n\n\n");
}