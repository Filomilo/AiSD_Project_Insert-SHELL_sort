/**
 * @file data_gather.c
 * @author Tomasz Bogdan, Maciej Cedzyński, Filip Borowiec
 * @brief funkcje od zbierania danych odnośnie sortowania
 * @version 0.1
 * @date 2022-04-05
 *
 * @copyright Copyright (c) 2022
 *
 */


#include "sort_project.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


 /**
  * @brief funkcja licząca czas potrzebny na sortowanie tabeli
  *
  * funkcja ta przyjmuje wskaźnik na tablice oraz jej wielkośc a także wskaźnik na funkcję sortująca której część ma być obliczony
  * funkcja ta najpierw duplikuje table a następnie zapisuje stan zegara procesora, następnie sortuje tabele i zapisuje
  * stan zegera po sortowaniu na wstępnie dzieli różnice tych wartości prez CLOCKS_PER_SEC
  * otrzymując w ten sposób ilość sekund potrzebnych na sortowanie
  *
  * @param array - wskaźnik na tabele do posortowania
  * @param N - ilość elementów tabeli
  * @param sort - wskaźnik na funkcję sortująca
  * @return float - zwraca wartość typu float określając czas potrzebny na sortowanie
  */

float calc_time(int* array, int N, void (*sort)(int*, int))
{
	
	int* new = calloc(N, sizeof(int));
	duplicate_array(array, new, N);
	time_t start= clock(NULL);
	sort(new, N);
	time_t stop = clock(NULL);

	free(new);




	return (double)(stop-start)/CLOCKS_PER_SEC;
}




/*
float calc_proces(int* array, int N, int (*sort)(int*, int))
{
	int a=0;
	int* new = calloc(N, sizeof(int));
	duplicate_array(array, new, N);
	a=sort(new, N);

	free(new);




	return a;
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
*/