/**
 * @file sort_algorithms.c
 * @author Tomasz Bogdan, Maciej Cedzyński, Filip Borowiec
 * @brief plik zawierający wszystkie funkcje sortujące
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
  * @brief funkcja sortująca poprzez wstawienie
  *
  * @param array - wskaźnik na tablice która ma być posortowana
  * @param N - ilość elementów tablicy
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
 * @param N - ilość elementów tablicy
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
 * @brief funkcja licząca ilość operacji w sortowaniu przez wstawianie
 *
 * @param array - wskaźnik na tablice która ma być posortowana
 * @param N - ilość elementów tablicy
 * @return int - zwraca ilość wykonanych operacji
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
 * @brief funkcja licząca ilość operacji w sortowaniu przez metoda shella
 *
 * @param array - wskaźnik na tablice która ma być posortowana
 * @param N - ilość elementów tablicy
 * @return int - zwraca ilość wykonanych operacji
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
 * @brief funkcja sortująca przez wstawiania wypisująca i zatrzymująca się na znaczącym etapie
 *
 * @param array - wskaźnik na tablice która ma być posortowana
 * @param N - ilość elementów tablicy
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

/**funkcja
 * @brief funkcja sortująca metoda shella wypisująca zatrzymująca się na znaczącym etapie
 *
 * @param array - wskaźnik na tablice która ma być posortowana
 * @param N - ilość elementów tablicy
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
 * @brief funkcja sortująca metoda shella i wyświetlająca graficzne tabele po każdym znaczącym etapie
 *
 * @param array - wskaźnik na tablice która ma być posortowana
 * @param N - ilość elementów tablicy
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
 * @brief funkcja sortująca przez wstawianie i wyświetlająca graficznie tabele po każdym znaczącym etapie
 *
 * @param array - wskaźnik na tablice która ma być posortowana
 * @param N - ilośc elementów tablicy
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
 * @brief funkcja sortująca przez wstawianie i wyświetlająca graficzne tabele po każdym znaczącym etapie zatrzymując się przy tym
 *
 * @param array - wskaźnik na tablice która ma być posortowana
 * @param N - ilość elementów tablicy
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
 * @brief funkcja sortująca metodą shella i wyświetlająca graficzne tabele po każdym znaczącym etapie
 *
 * @param array - wskaźnik na tablice która ma być posortowana
 * @param N - ilość elementów tablicy
 * @param max - maksymalna wartość w tablicy
 */
/
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