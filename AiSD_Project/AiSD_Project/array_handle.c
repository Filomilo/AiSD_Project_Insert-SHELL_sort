#include "sort_project.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


#define GREEN "\033[0;32m"
#define WHITE "\033[0;37m"
#define YELLOW "\033[0;33m"

void print_array(int* array, int N)
{
	for (int i = 0; i < N; i++)
	{
		printf("%d, ", array[i]);
	}
}

void print_array_a(int* array, int N, int g, int g1, int y, int y2)
{
	for (int i = 0; i < N; i++)
	{
		if (i == g)
		{
			printf(GREEN "%d", array[i]);
			printf(WHITE", ");
		}
		else
			if (i == g1)
			{
				printf(GREEN "%d", array[i]);
				printf(WHITE", ");
			}
			else
			if (i == y)
			{
				printf(YELLOW "%d", array[i]);
				printf(WHITE", ");
			}
			else
				if (i == y2)
				{
					printf(YELLOW "%d", array[i]);
					printf(WHITE", ");
				}
				else
		printf(WHITE "%d, ", array[i]);
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