#include "sort_project.h"
#include <stdlib.h>
#include <allegro5/allegro.h>

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