/**
 * @file array_handle.c
 * @author Tomasz Bogdan, Maciej Cedzyński, Filip Borowiec
 * @brief plik ten zawiera funkcje do obsługi tabeli
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
#include <string.h>
 /**
  * @brief oznaczenie koloru zielonego do wykorzystania w printf
  *
  */

#define GREEN "\033[0;32m"

  /**
   * @brief oznaczenie koloru białego do wykorzystania w printf
   *
   */

#define WHITE "\033[0;37m"
   /**
	* @brief oznaczenie koloru żółtego do wykorzystania w printf
	*
	*/

#define YELLOW "\033[0;33m"
	/**
	 * @brief funkcja ta wypisuje zawartość wszystkich elementów w tablicy
	 *
	 * @param array - wskaźnik na tablice zawierająca elementy do wyświetlenia
	 * @param N - zmienna informująca o wielkości tablicy do wyświetlenia
	 */

void print_array(int* array, int N)
{
	for (int i = 0; i < N; i++)
	{
		printf("%d, ", array[i]);
	}
}


/**
 * @brief funkcja wypisująca zawartość ale z możliwością wyboru 2 elementów które mają się wyświetlić na zielono oraz dwóch
 * elementów które mają się wyświetlić na żółto
 *
 * @param array - wskaźnik na tablice zawierająca elementy do wyświetlenia
 * @param N - zmienna informująca o wielkości tablicy do wyświetlenia
 * @param g - index elementu który ma się wyświetlić na zielono
 * @param g1 - index drugiego elementu który ma się wyświetlić na zielono
 * @param y - index elementu który ma się wyświetlić na żółto
 * @param y2 - index drugiego elementu który ma się wyświetlić na żółto
 */

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



/**
 * @brief funkcja wypełnia table losowymi wartościami z podanego zakresu
 *
 * @param array - wskaźnik na tablice zawierająca elementy do wypełnienia
 * @param N - zmienna informująca o wielkości tablicy do wypełnienia
 * @param min - minimalny zakres losowania
 * @param max - maksymalny zakres losowania
 */

void fill_array_rand(int* array, int N, int min, int max)
{
	srand((int)time(0));
	for (int i = 0; i < N; i++)
	{
		array[i] = rand() % (max - min + 1) + min;
	}
}

/**
 * @brief funkcja wypełniająca tablice wartościami od 1 do wielkości tablicy ale w kolejności odwrotnej
 *
 * @param array - wskaźnik na tablice zawierająca elementy do wypełnienia
 * @param N - zmienna informująca o wielkości tablicy do wypełnienia
 */

void fill_array_reverse(int* array, int N)
{
	for (int i = 0; i < N; i++)
	{
		array[i] =N-i;
	}
}



/**
 * @brief funckja duplikująca zawartosć tablicy do drugiej tablicy
 *
 * @param array - wskaźnik na tablice zawierająca elementy do skopiowania
 * @param array_to_copy - wskaźnik na tablice do której ma zostać skopiowana tablica
 * @param N - zmienna informująca o wielkości tablicy do wypełnienia
 */

void duplicate_array(int* array, int* array_to_copy, int N)
{

	for (int i = 0; i < N; i++)
	{
		array_to_copy[i] = array[i];
	}


}

/**
 * @brief
 *
 * @param name - nazwa pliku do którego ma zostać zapisana
 * @param array - wskaźnik na tablice zawierająća elemnrty do zapisania
 * @param N - zmienna informująca o wielkości tablicy do wypełnienia
 */

void save_array(char name[50], int array[], int N)
{
	FILE* file;
	

	
	char file_name[54];

	strncpy_s(file_name,54, name, 50);
	strncat_s(file_name, 50, ".txt", 4);


	fopen_s(&file, file_name, "w");
	for (int i = 0; i < N; i++)
	{
		fprintf(file,"%d \n",array[i]);


	}
	fclose(file);


}
/**
 * @brief funkcja zamieniająca między sobą wartości dwóch zmiennych
 *
 * @param a - wskaźnik na pierwszą zmienna do zamieniania
 * @param b - wskaźnik na druga zmienna do zamieniania
 */

void swap(int* a, int* b)
{
	int tmp =* a;
	*a = *b;
	*b = tmp;
}

/**
 * @brief funkcja przesuwająca wszystkie elementy tablicy
 *
 * @param array - wskaźnik na tablice zawierająća elemnrty do zapisania
 * @param N - zmienna informująca o wielkości tablicy do wypełnienia
 */

void shuffle_arry(int* array, int N)
{
	srand(time(0));
	for (int i = 0; i < N; i++)
	{
		swap(&array[i], &array[rand() % (N - i) + i]);


	}

}