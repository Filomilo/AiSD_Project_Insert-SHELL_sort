/**
 * @file data_gather.c
 * @author Tomasz Bogdan, Maciej Cedzyński, Filip Borowiec
 * @brief funckje od zbierania danych odnośnie osrtowania
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
 * @brief funckja licząca czas potrzebny na posortwoanie tabeli
 * 
 * funckja ta przyjmuje wskaźńik na tablice o raz jej wielkośc a także wskaźnik na funckje sortująca której czes ma być obliczony
 * funckja ta najpierw duplikuje table a nastęnie zapiuje stan zsgera procesora, następnie sortuje taablele i zapiusuje 
 * stan zegera po sortowaniu na stępnie dzieli różnice tych wartości prez CLOCKS_PER_SEC 
 * otrzymujac w ten sposoć ilość sekund potrzebnych na posortowanie
 *
 * @param array - wskaźnik na tabele do posortownia
 * @param N - ilość elemntó tabeli
 * @param sort - wskaźnik na funkce sortująca
 * @return float - zwraca wartosć typu float okreslając czas potrzsbyn na sortowanie
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