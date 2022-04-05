/**
 * @file sort_algorithms.c
 * @author Tomasz Bogdan, Maciej Cedzyński, Filip Borowiec
 * @brief plik zawierajce wszystkie funkcje sortujace
 * @version 0.1
 * @date 2022-04-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "sort_project.h"
#include <stdlib.h>
#include <allegro5/allegro.h>





/**
 * @brief funckja sortująca poprzez wstawinie
 * 
 * @param array - wskaźnik na tablice która ma być posortowana
 * @param N - ilośc elemntów tablicy
 */
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
		//printf("\n");
		//print_array(array, N);

	}
}

/**
 * @brief funckja sortująca metoda shella
 * 
 * @param array - wskaźnik na tablice która ma być posortowana
 * @param N - ilośc elemntów tablicy
 */
void shell_sort(int* array, int N)
{
	int active;
	for (int gap = N / 2; gap > 0; gap /= 2)
	{
		//printf("\ngap: %d\n", gap);
		for (int i = gap; i < N; i++)
		{
			active = array[i];
			int j = i - gap;
			while (j >= 0 && array[j] > active)
			{
				array[j + gap] = array[j];
				j-=gap;
			}
			array[j + gap] = active;
			//printf("\n");
			//print_array(array, N);


		}




	}
}


/**
 * @brief funcja liczaća ilosć operacji w sortwoaniu przez wstawianiae 
 * 
 * @param array - wskaźnik na tablice która ma być posortowana
 * @param N - ilośc elemntów tablicy
 * @return int - zwraca ilośc wykoanych operacji
 */
int insert_sort_calc(int* array, int N)
{
	int proces = 0;
	int active;
	for (int i = 1; i < N; i++)
	{
		active = array[i];
		int j = i - 1;
		while (j >= 0 && array[j] > active)
		{
			proces++;
			proces++;
			array[j + 1] = array[j];
			j--;
		}
		array[j + 1] = active;
		//printf("\n");
		//print_array(array, N);
		proces++;
	}

	return proces;
}

/**
 * @brief funcja liczaća ilosć operacji w sortwoaniu przez metoda shella 
 * 
 * @param array - wskaźnik na tablice która ma być posortowana
 * @param N - ilośc elemntów tablicy
 * @return int - zwraca ilośc wykoanych operacji
 */
int shell_sort_calc(int* array, int N)
{
	int proces=0;
	int active;
	for (int gap = N / 2; gap > 0; gap /= 2)
	{
		proces++;
		//printf("\ngap: %d\n", gap);
		for (int i = gap; i < N; i++)
		{
			active = array[i];
			int j = i - gap;
			while (j >= 0 && array[j] > active)
			{
				array[j + gap] = array[j];
				j -= gap;

				proces++;
				proces++;
			}
			array[j + gap] = active;
			//printf("\n");
			//print_array(array, N);

			proces++;
		}



		proces++;
	}
	return proces;
}




/**
 * @brief funcja sortująca przez wstawiania wypisująca i zatrzymujaca się na znaczącym etapie
 * 
 * @param array - wskaźnik na tablice która ma być posortowana
 * @param N - ilośc elemntów tablicy
 */
void insert_sort_step(int* array, int N)
{
	int active;
	for (int i = 1; i < N; i++)
	{
		
		active = array[i];
		int j = i - 1;

		
		while (j >= 0 && array[j] > active)
		{
			array[j + 1] = array[j];
			printf("\n");
			print_array_a(array, N, -1, -1, i, j);
			getchar();
			j--;
		}
		array[j + 1] = active;
		printf("\n");
		print_array_a(array, N, i, j+1, -1, -1);
		getchar();
		system("cls");
	}
}

/**
 * @brief funcja sortująca metoda shella wypsyiująca i zatrzymujaca się na znaczącym etapie
 * 
 * @param array - wskaźnik na tablice która ma być posortowana
 * @param N - ilośc elemntów tablicy
 */
void shell_sort_step(int* array, int N)
{
	int active;
	for (int gap = N / 2; gap > 0; gap /= 2)
	{
		for (int i = gap; i < N; i++)
		{
			
			active = array[i];
			int j = i - gap;
			while (j >= 0 && array[j] > active)
			{
				array[j + gap] = array[j];
				printf("\n");
				print_array_a(array, N, -1, -1, i, i - gap);
				getchar();
				j -= gap;
				
			}
			
			array[j + gap] = active;
			printf("\n");
			print_array_a(array, N, i, i - gap, -1, -1);
			getchar();
			system("cls");


		}




	}
}



/**
 * @brief funckja sortująca metoda shella i wyświetlająća grafczinnie tabelel po każdym znaczącym etapie
 * 
 * @param array - wskaźnik na tablice która ma być posortowana
 * @param N - ilośc elemntów tablicy
 * @param max - maksymalna wartość w tablicy
 */
void shell_sort_draw(int* array, int N, int max)
{
	int active;
	for (int gap = N / 2; gap > 0; gap /= 2)
	{
		for (int i = gap; i < N; i++)
		{

			active = array[i];
			int j = i - gap;
			while (j >= 0 && array[j] > active)
			{
				array[j + gap] = array[j];
				al_clear_to_color(BLACK);
				draw_array_a(array, N,max, -1, -1, i, i - gap);
				j -= gap;

			}

			array[j + gap] = active;
			al_clear_to_color(BLACK);
			draw_array_a(array, N,max, i, i - gap, -1, -1);

		}




	}
	al_clear_to_color(BLACK);
	draw_array(array, N, max, 0, 255, 0);
}



/**
 * @brief funckja sortująca przez wstawianie i wyświetlająća grafczinnie tabelel po każdym znaczącym etapie
 * 
 * @param array - wskaźnik na tablice która ma być posortowana
 * @param N - ilośc elemntów tablicy
 * @param max - maksymalna wartość w tablicy
 */
void insert_sort_draw(int* array, int N, int max)
{
	int active;
	for (int i = 1; i < N; i++)
	{

		active = array[i];
		int j = i - 1;


		while (j >= 0 && array[j] > active)
		{
			array[j + 1] = array[j];
			al_clear_to_color(BLACK);
			draw_array_a(array, N, max, -1, -1, i, j);
			j--;
		}
		array[j + 1] = active;
		al_clear_to_color(BLACK);
		draw_array_a(array, N, max, i, j + 1, -1, -1);
	}
	al_clear_to_color(BLACK);
	draw_array(array, N, max,0,255,0);
}






/**
 * @brief funckja sortująca przez wstawianie i wyświetlająća grafczinnie tabelel po każdym znaczącym etapie zatrzymując sie przy tym
 * 
 * @param array - wskaźnik na tablice która ma być posortowana
 * @param N - ilośc elemntów tablicy
 * @param max - maksymalna wartość w tablicy
 */
void insert_sort_draw_step(int* array, int N, int max)
{
	int active;
	for (int i = 1; i < N; i++)
	{

		active = array[i];
		int j = i - 1;


		while (j >= 0 && array[j] > active)
		{
			array[j + 1] = array[j];
			al_clear_to_color(BLACK);
			draw_array_a(array, N, max, -1, -1, i, j);
			wait_enter();
			j--;
		}
		array[j + 1] = active;
		al_clear_to_color(BLACK);
		draw_array_a(array, N, max, i, j + 1, -1, -1);
	}
	al_clear_to_color(BLACK);
	draw_array(array, N, max, 0, 255, 0);
	wait_enter();
	wait_enter();
}

/**
 * @brief funckja sortująca metodą shella i wyświetlająća grafczinnie tabelel po każdym znaczącym etapie
 * 
 * @param array - wskaźnik na tablice która ma być posortowana
 * @param N - ilośc elemntów tablicy
 * @param max - maksymalna wartość w tablicy
 */
void shell_sort_draw_step(int* array, int N, int max)
{
	int active;
	for (int gap = N / 2; gap > 0; gap /= 2)
	{
		for (int i = gap; i < N; i++)
		{

			active = array[i];
			int j = i - gap;
			while (j >= 0 && array[j] > active)
			{
				array[j + gap] = array[j];
				al_clear_to_color(BLACK);
				draw_array_a(array, N, max, -1, -1, i, i - gap);
				wait_enter();
				j -= gap;

			}

			array[j + gap] = active;
			al_clear_to_color(BLACK);
			draw_array_a(array, N, max, i, i - gap, -1, -1);
			wait_enter();

		}




	}
	al_clear_to_color(BLACK);
	draw_array(array, N, max, 0, 255, 0);
	wait_enter();
}