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
	free(new);
	return (double)(stop-start)/CLOCKS_PER_SEC;
}



void generarate_times(int limit, int dif)
{
	//remove("results.txt");
	FILE* file;
	 fopen_s(&file,"results.txt", "w");
	fprintf(file, "ilosc; czas insert; czas shell\n");
	float shell_t, insert_t;
	for (int N = 0; N <= limit; N += dif)
	{
		int* array = (int*)calloc(N, sizeof(int));
		fill_array_reverse(array, N);
		shell_t = calc_time(array, N, shell_sort);
		insert_t = calc_time(array, N, insert_sort);
		free(array);
		printf("czas sortoownaia insert sort dla %d elementow: %.3fs\n", N,insert_t );
		printf("czas sortoownaia shell sort dla %d elementow: %.3fs\n", N,shell_t);
		fprintf(file, "%d;%.3f;%.3f\n",N, insert_t, shell_t);
		
		
		printf("\n");
	}
	fclose(file);


}