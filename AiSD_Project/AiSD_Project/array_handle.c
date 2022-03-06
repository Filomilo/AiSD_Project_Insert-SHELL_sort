#include "sort_project.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void print_array(int* array, int N)
{
	for (int i = 0; i < N; i++)
	{
		printf("%d, ", array[i]);
	}
}






void fill_array(int* array, int N, int min, int max)
{
	srand((int)time(0));
	for (int i = 0; i < N; i++)
	{
		array[i] = rand() % (max - min + 1) + min;
	}
}