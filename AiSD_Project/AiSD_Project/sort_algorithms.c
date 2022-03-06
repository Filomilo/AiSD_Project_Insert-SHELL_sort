#include "sort_project.h"
#include <stdlib.h>


void insert_sort(int* array, int N)
{
	int active;
	for (int i = 1; i < N; i++)
	{
		active = array[i];
		int j = i - 1;
		while(j>=0 && array[j]>active)
		{
			array[j + 1] = array[j];
			j--;
		}
		array[j + 1] = active;
		printf("\n");
		print_array(array, N);

	}





}


void shell_sort(int array[], int N)
{






}