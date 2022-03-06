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






void fill_array_rand(int* array, int N, int min, int max)
{
	srand((int)time(0));
	for (int i = 0; i < N; i++)
	{
		array[i] = rand() % (max - min + 1) + min;
	}
}

void fill_array_reverse(int* array, int N)
{
	for (int i = 0; i < N; i++)
	{
		array[i] =N-i;
	}
}




void duplicate_array(int* array, int* array_to_copy, int N)
{

	for (int i = 0; i < N; i++)
	{
		array_to_copy[i] = array[i];
	}


}