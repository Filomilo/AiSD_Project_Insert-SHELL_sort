/**
 * @file gui.c
 * @author Tomasz Bogdan, Maciej Cedzyński, Filip Borowiec
 * @brief funkcje odpowiadające za interfejs graficzny
 * @version 0.1
 * @date 2022-04-05
 *
 * @copyright Copyright (c) 2022
 *
 */



#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_image.h>
#include "sort_project.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

 /**
  * @brief struktura przeznaczone na dane czasu sortowania
  *
  * funkcja ta przechowuje dane odnośnie czasu sortowania tabeli, zawiera element określający ilość elementów które były sortowane
  * czas potrzebny na sortowanie tej tabeli przez wstawienia o praz metoda shella
  *
  */
struct timers_struct
{
	int amount;
	float insert_time;
		float shell_time;
};
typedef struct timers_struct timers;



#define PRINT_INT(x) printf("%s=%d\n", #x, x)
#define PRINT_FL(x) printf("%s=%f\n", #x, x)

#define M_PI 3.14159265359
#define SCREEN_H 720
#define SCREEN_W 1280

#define POINT_RAD 7
#define GRAPH_GAP 75


#define UPPER_COMENT_H 40
#define ARRAT_ELEMENT_WIDTH 1200/3

#define BOLD_LINE 5
#define NARROW_LINE 2

#define UP_MOUSE_GAP 25
#define MOUSE_BOX_W 150
#define MOUSE_BOX_H 60

#define RANGE 25




typedef char text[250];




/**
 * @brief - wartość bezwzględna dla zmiennej float
 *
 * @param x - liczba float która ma zostać zamieniona na wartość z
 * @return float - zwraca wartość bezwzględną danej liczby float
 */

float absf(float x)
{
	if (x >= 0)
		return x;
	return -x;

}

/**
 * @brief wyświetla menu wyboru
 *
 * funkcja wyświetlająca proceduralnie generowane menu wyboru na podstawie podanych danych
 *
 * @param choices - tablica ciągów znaków zawierająca nagłówek/pytanie oraz opcje wyboru
 * @param N - wartość określająca ilość wyborów
 * @return int - funkcja zwraca wartość od 0 do n-1 w zależności od wybranego elementu w menu
 */

int choice_menu(text choices[], int N)
{
	
	ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);
	ALLEGRO_COLOR black = al_map_rgb(0, 0, 0);
	ALLEGRO_COLOR red = al_map_rgb(255, 0, 0);
	ALLEGRO_COLOR blue = al_map_rgb(10, 10, 255);
	ALLEGRO_COLOR choice_color = al_map_rgb(50, 20, 10);
	ALLEGRO_FONT* font = al_load_ttf_font("arial.ttf", 25, NULL);
	ALLEGRO_KEYBOARD_STATE key;
	ALLEGRO_MOUSE_STATE mouse;
	int if_end = 1;
	
	while (if_end) {
		
		al_get_mouse_state(&mouse);
		al_clear_to_color(black);
		al_get_keyboard_state(&key);
		int x = mouse.x - SCREEN_W / 2;
		int y = mouse.y - SCREEN_H / 2;
		float r = sqrt(x *x + y * y);
		
		float rad = atan2(y, x);
		if (rad > 0)
		rad = -1 *( 2*M_PI - rad );

		float seg = -2 * M_PI / N;
		/*
		for (int i = 0; i < N; i++)
		{
			if (rad<seg * i && rad>seg * (i + 1))
			{

			
				for(float j= seg * i;j> seg* (i + 1); j-=0.005)
					al_draw_line(SCREEN_W / 2, SCREEN_H / 2, SCREEN_W/2 * cos(j) * 180, SCREEN_W / 2 * sin(j) * 180, choice_color, 5);
				if (mouse.buttons == 1)
				{
					al_destroy_font(font);
					return i;
				}
					
			}
			}
			
		*/


		


		//hililghting
		al_clear_to_color(black);
		for (int i = 0; i < N; i++)
		{
			
			if (rad<seg * i && rad>seg * (i + 1))
			{
				if (mouse.buttons == 1)
				{
					al_destroy_font(font);
					return i;
				}
				if (N > 2)
				{
					ALLEGRO_VERTEX v[] =
					{
						{SCREEN_W / 2 ,SCREEN_H / 2,0,0,0,blue},
						{SCREEN_W / 2 + cos(seg * i) * SCREEN_W, SCREEN_H / 2 + sin(seg * i) * SCREEN_W,0,0,0,black},
						{SCREEN_W / 2 + cos(seg * (i + 1)) * SCREEN_W, SCREEN_H / 2 + sin(seg * (i + 1)) * SCREEN_W,0,0,0,black}
						//{10,100,0,0,0,black},
						//{800,800,0,0,0,black},
					};

					al_draw_prim(v, NULL, NULL, 0, 3, ALLEGRO_PRIM_TRIANGLE_FAN);
				}
				else
				{
					ALLEGRO_VERTEX v[] =
					{
						{0 ,SCREEN_H / 2,0,0,0,blue},
						{SCREEN_W  ,SCREEN_H / 2 ,0,0,0,blue},
						{0,(mouse.y>SCREEN_H/2)?SCREEN_H:0,0,0,0,black},
						{SCREEN_W, (mouse.y > SCREEN_H / 2) ? SCREEN_H : 0,0,0,0,black}
					};

					al_draw_prim(v, NULL, NULL, 0, 4, ALLEGRO_PRIM_TRIANGLE_STRIP);
				}
			}


		}
		









		al_draw_filled_ellipse(SCREEN_W / 2, SCREEN_H / 2, 200, 100, white);
		float width = al_get_text_width(font, choices[0]);
		float height = al_get_font_line_height(font);
		al_draw_text(font, red, SCREEN_W / 2 - width / 2, SCREEN_H/2-height/2, 0, choices[0]);
		for (int i = 0; i < N; i++)
		{
			int dist =150;
			float rad2 = seg / 2 + seg * i;

			float mult = dist*(absf(absf(rad2+M_PI)-M_PI/2)/(M_PI/2)+2);

			 width = al_get_text_width(font, choices[i+1]);
			al_draw_text(font, red, SCREEN_W/2 + mult *cos(rad2)- width /2, SCREEN_H/2 + mult *sin(rad2), 0, choices[i + 1]);
		}
		/*
		text mouse_test;
		//for (float i= 0; i > rad; i-=0.001)
		//{
		//	al_draw_line(SCREEN_W / 2, SCREEN_H / 2, r * cos(i)*180, r * sin(i)*180, white, 5);
		//}
		//al_draw_arc(SCREEN_W / 2, SCREEN_H / 2, r, 0, rad, white, sqrt(pow(SCREEN_W,2)+pow(SCREEN_H, 2)));

		sprintf_s(mouse_test,100, "%.3f, %.3f",r, absf(absf(rad+M_PI)-M_PI*0.5));
		al_draw_text(font, red,200, 0, 0, mouse_test);
		*/


			al_flip_display();




			if (al_key_down(&key, ALLEGRO_KEY_ESCAPE))
			{
				al_clear_to_color(black);
				if_end = 0;

			}
			
	}
	
	al_destroy_font(font);
return - 5;
}


/**
 * @brief funkcja oczekuje na wciśnięcie enter
 *
 * funkcja wchodzi w pętle i oczekuje wciśnięcie enter przez użytkownika
 *
 */

void wait_enter()
{
	al_rest(0.2);
	ALLEGRO_KEYBOARD_STATE key;

	while (1)
	{
		{
			al_get_keyboard_state(&key);
			if (al_key_down(&key, ALLEGRO_KEY_ENTER))
				break;
		}
	}
}


/**
 * @brief funkcja przybliza wartosc float w dół
 * 
 * @param data 
 */
void aproximate_up(float* data)
{
	if (*data <= 0)
	{
		*data = 0;
		return;
	}
	int tmp = 1;
	while (*data > tmp*10)
	{
		tmp *= 10;
	//	printf("tmp= %d", tmp);
	}

	*data = ((int)(*data / tmp) + 1) * tmp;
}
/**
 * @brief funkcja przybliza wartosc float w góre
 * 
 * @param data 
 */
void aproximate_down(float* data)
{
	return (float)((int)*data);
}


/**
 * @brief funckja sprawdza czy myszka nachodzi na punkt
 * 
 * funckcja sprawdza czy ppodana pozycja znadjuje sie w odlgelosci RANGE od andego punktu i zwraca wartosc 0 jezeli nie i 1 jezeli tak
 * 
 * @param x1 - kordyanty x myszki
 * @param y1  - kordyanty y myszki
 * @param x2 - kordyanty x punktu
 * @param y2 - kordyanty y punktu
 * @return int - wartosc 0 jezeli nie , wartosc 1 jezeli tak
 */
int if_in_range(float x1, float y1, float x2, float y2)
{
	if (sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)) < RANGE)
		return 1;
	return 0;
}
/**
 * @brief funkcja pomocznica do wycnzaczneia kordynatów x punktówn a wykresie
 * 
 * @param x 
 * @return float 
 */
float point_x(float x)
{
	return x + GRAPH_GAP;
}
/**
 * @brief funkcja pomncnicza do wycznaczenia kordyntów y na pnuktu na wykresie
 * 
 * @param y 
 * @return float 
 */
float point_y(float y)
{
	return SCREEN_H-y - GRAPH_GAP;
}

/**
 * @brief funkcja pomocniza do rysowania punktów na wykresie
 * 
 * @param x 
 * @param y 
 * @param color 
 */
void draw_dot(float x, float y, ALLEGRO_COLOR color)
{
	al_draw_filled_circle(x, y, POINT_RAD, color);
}
/**
 * @brief funcja rysująca wykres czasu od ilosci danych
 * 
 * funckja rusuje wykres na podstawie odanych danych a nastepnie pozwala takze wybrac punkt aby wysswietlic szegółowe  dane
 * 
 * @param data - wskaxnik na talbice zawierajaca dane do wyświetlenia
 * @param N - ilość elemtów w talibcy do wyświetlenia
 * @param display - wskanik na ekran na któym ma być wysietlony wkyres
 */
void generate_graph(timers data[],int N, ALLEGRO_DISPLAY* display)
	{
	ALLEGRO_BITMAP* graph_bitmap = al_create_bitmap(SCREEN_W, SCREEN_H);
	ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);
	ALLEGRO_COLOR black = al_map_rgb(0, 0, 0);
	ALLEGRO_COLOR green = al_map_rgb(0, 255, 0);
	ALLEGRO_COLOR grey = al_map_rgb(150, 150, 150);
	ALLEGRO_COLOR red = al_map_rgb(255, 0, 0);
	ALLEGRO_FONT* font = al_load_ttf_font("arial.ttf", 25, NULL);
	int font_h = al_get_font_line_height(font);
	float min_x = data[0].amount;
	float max_x = data[0].amount;

	float min_y = data[0].insert_time < data[0].shell_time ? data[0].insert_time : data[0].shell_time;
	float max_y = data[0].insert_time > data[0].shell_time ? data[0].insert_time : data[0].shell_time;


	al_set_target_bitmap(graph_bitmap);
	al_clear_to_color(black);
	al_draw_line(0 + GRAPH_GAP, GRAPH_GAP-50, 0 + GRAPH_GAP, SCREEN_H - GRAPH_GAP, white, BOLD_LINE);
	al_draw_line(0 + GRAPH_GAP, SCREEN_H - GRAPH_GAP, SCREEN_W- GRAPH_GAP+50, SCREEN_H - GRAPH_GAP, white, BOLD_LINE);
	al_draw_filled_triangle(SCREEN_W - GRAPH_GAP + 50, SCREEN_H - GRAPH_GAP - 10, SCREEN_W - GRAPH_GAP + 50, SCREEN_H - GRAPH_GAP + 10, SCREEN_W - GRAPH_GAP + 50 + 10, SCREEN_H - GRAPH_GAP, white);
	al_draw_filled_triangle(0 + GRAPH_GAP-10, GRAPH_GAP - 50, 0 + GRAPH_GAP + 10, GRAPH_GAP - 50, 0 + 0 + GRAPH_GAP, GRAPH_GAP - 50-10,	white);
	//al_draw_rectangle(0 + GRAPH_GAP, 0 + GRAPH_GAP, SCREEN_W - GRAPH_GAP, SCREEN_H - GRAPH_GAP, white, BOLD_LINE);

	al_draw_filled_rectangle(100, 50, 100 + 25, 50 + 25, red);
	al_draw_filled_rectangle(100+500, 50, 100 +500+ 25, 50 + 25, green);
	al_draw_textf(font, red, 100 + 25 + 10, 50, 0, "insert sort");
	al_draw_textf(font, green, 100 + 500 + 25+10, 50 ,0, "shell sort");

	for (int i = 0; i < N; i++)
	{
		if (data[i].amount < min_x)
		{
			min_x = data[i].amount;
		}
		else
		{
			if (data[i].amount > max_x)
			{
				max_x = data[i].amount;
			}
		}



		if (data[i].insert_time < min_y)
		{
			min_y = data[i].insert_time;
		}
		else
		{
			if (data[i].insert_time > max_y)
			{
				max_y = data[i].insert_time;
			}
		}
		
		if (data[i].shell_time < min_y)
		{
			min_y = data[i].shell_time;
		}
		else
		{
			if (data[i].shell_time > max_y)
			{
				max_y = data[i].shell_time;
			}
		}

	}
	PRINT_FL(max_y);
	aproximate_up(&max_x);
	aproximate_up(&max_y);
	aproximate_down(&min_x);
	aproximate_down(&min_y);
	int x = 5;
	PRINT_INT(x);
	
	//values used to cnvert point data to cordinates
	float x_value = (SCREEN_W - 2 * GRAPH_GAP) / (max_x - min_x);
	float y_value = (SCREEN_H - 2 * GRAPH_GAP) / (max_y - min_y);

	//values used on axises
	int x_gap= max_x / 5;
	if (x_gap == 0)
	{
		x_gap = 1;
	}
	int y_gap = max_y / 5;
	if (y_gap == 0)
	{
		y_gap = 1;
	}
	PRINT_FL(max_y);
	PRINT_FL((max_x-min_x)*x_value+GRAPH_GAP);


	//rysowanie wartosci osi
	for (int i = 0; i<=max_x; i+=x_gap)
	{
		draw_dot(point_x((i - min_x) * x_value), point_y(0),white);
		al_draw_textf(font, white, point_x((i - min_x) * x_value), point_y(0-25), ALLEGRO_ALIGN_CENTER, "%d", i);
	}
	for (int i = 0; i <= max_y; i += y_gap)
	{
		al_draw_line(point_x(0), point_y((i - min_y) * y_value), SCREEN_W - GRAPH_GAP + 50, point_y((i - min_y) * y_value), grey, NARROW_LINE);
		draw_dot(point_x(0), point_y((i-min_y)*y_value), white);
		al_draw_textf(font, white, point_x(0)-50, point_y((i - min_y) * y_value)-font_h, ALLEGRO_ALIGN_CENTER, "%d", i);
		
	}

	//rysowanie lini
	for (int i= 0; i < N; i++)
	{
		draw_dot(point_x((data[i].amount - min_x) * x_value), point_y((data[i].insert_time - min_y) * y_value), red);
		al_draw_line(point_x((data[i].amount - min_x) * x_value), point_y((data[i].insert_time - min_y) * y_value), point_x((data[i + 1 < N ? i + 1 : i].amount - min_x) * x_value), point_y((data[i + 1 < N ? i + 1 : i].insert_time - min_y) * y_value), red, BOLD_LINE);

		draw_dot(point_x((data[i].amount - min_x) * x_value), point_y((data[i].shell_time - min_y) * y_value), green);
		al_draw_line(point_x((data[i].amount - min_x) * x_value), point_y((data[i].shell_time - min_y) * y_value), point_x((data[i + 1 < N ? i + 1 : i].amount - min_x) * x_value), point_y((data[i + 1 < N ? i + 1 : i].shell_time - min_y) * y_value), green, BOLD_LINE);
	}

	al_save_bitmap("results.png", graph_bitmap);
	al_set_target_backbuffer(display);


	
	ALLEGRO_KEYBOARD_EVENT key;
	ALLEGRO_MOUSE_STATE mouse;
	//petla interakcj
	
	float box_x_offset = 0;
	float box_y_offset = 0;
	while (1)
	{

		al_draw_bitmap(graph_bitmap, 0, 0, 0);
		al_get_keyboard_state(&key);
		if (al_key_down(&key, ALLEGRO_KEY_ENTER))
			break;
		al_get_mouse_state(&mouse);

		for (int i = 0; i < N; i++)
		{

			//caclulatiuing box  oofset
			if (mouse.x + MOUSE_BOX_W > SCREEN_W)
				box_x_offset = (SCREEN_W - (mouse.x + MOUSE_BOX_W));
			else
			{
				if (mouse.x - MOUSE_BOX_W < 0)
					box_x_offset = abs((mouse.x - MOUSE_BOX_W));
				else
					box_x_offset = 0;
			}


			if (mouse.y - MOUSE_BOX_H-UP_MOUSE_GAP <0)
				box_y_offset =abs(mouse.y - MOUSE_BOX_H - UP_MOUSE_GAP);
				else
					box_y_offset = 0;





			//redniring box on slector
			if (if_in_range(mouse.x, mouse.y, point_x((data[i].amount - min_x) * x_value), point_y((data[i].insert_time - min_y) * y_value)))
			{
				al_draw_circle(point_x((data[i].amount - min_x)* x_value), point_y((data[i].insert_time - min_y)* y_value), POINT_RAD, white, BOLD_LINE);
				al_draw_filled_rectangle(mouse.x - MOUSE_BOX_W + box_x_offset, mouse.y - (UP_MOUSE_GAP + MOUSE_BOX_H) + box_y_offset, mouse.x + MOUSE_BOX_W + box_x_offset, mouse.y - UP_MOUSE_GAP + box_y_offset, black);
				al_draw_rectangle(mouse.x - MOUSE_BOX_W + box_x_offset, mouse.y - (UP_MOUSE_GAP + MOUSE_BOX_H) + box_y_offset, mouse.x + MOUSE_BOX_W + box_x_offset, mouse.y - UP_MOUSE_GAP + box_y_offset, red, NARROW_LINE);
				al_draw_textf(font, white, mouse.x - MOUSE_BOX_W + box_x_offset, mouse.y - (UP_MOUSE_GAP + MOUSE_BOX_H) + box_y_offset, 0, "amount : %d", data[i].amount);
				al_draw_textf(font, white, mouse.x - MOUSE_BOX_W + box_x_offset, mouse.y - (UP_MOUSE_GAP + MOUSE_BOX_H) + font_h + box_y_offset, 0, "insert sort time : %.3f", data[i].insert_time);
			}

			if (if_in_range(mouse.x, mouse.y, point_x((data[i].amount - min_x) * x_value), point_y((data[i].shell_time - min_y) * y_value)))
			{
				al_draw_circle(point_x((data[i].amount - min_x) * x_value), point_y((data[i].shell_time - min_y) * y_value), POINT_RAD, white, BOLD_LINE);
				al_draw_filled_rectangle(mouse.x - MOUSE_BOX_W + box_x_offset, mouse.y - (UP_MOUSE_GAP + MOUSE_BOX_H)+ box_y_offset, mouse.x + MOUSE_BOX_W+ box_x_offset, mouse.y - UP_MOUSE_GAP+ box_y_offset, black);
				al_draw_rectangle(mouse.x - MOUSE_BOX_W+ box_x_offset, mouse.y - (UP_MOUSE_GAP + MOUSE_BOX_H)+ box_y_offset, mouse.x + MOUSE_BOX_W+ box_x_offset, mouse.y - UP_MOUSE_GAP+ box_y_offset, green, NARROW_LINE);
				al_draw_textf(font, white, mouse.x - MOUSE_BOX_W+ box_x_offset, mouse.y - (UP_MOUSE_GAP + MOUSE_BOX_H)+ box_y_offset, 0, "amount : %d", data[i].amount);
				al_draw_textf(font, white, mouse.x - MOUSE_BOX_W+ box_x_offset, mouse.y - (UP_MOUSE_GAP + MOUSE_BOX_H) + font_h+ box_y_offset, 0, "shell sort time : %.3f", data[i].shell_time);
			}
		}


		al_flip_display();
	}
		
	al_destroy_bitmap(graph_bitmap);
	al_destroy_font(font);
		
		
	}


/**
 * @brief funkcja wyświetlająca komunikat o wciśnięciu  enter
 *
 */

void press_enter()
{
	ALLEGRO_COLOR black = al_map_rgb(0, 0, 0);
	ALLEGRO_COLOR white = al_map_rgb(255,255,255);
	al_clear_to_color(black);
	ALLEGRO_FONT* font = al_load_ttf_font("arial.ttf", 25, NULL);
	text txt = "Wcisnij enter, aby kontynuowac";
	float width = al_get_text_width(font, txt);
	float height = al_get_font_line_height(font);
	al_draw_text(font, white, SCREEN_W / 2 - width / 2, SCREEN_H / 2 + height, 0, txt);
	al_flip_display();
	wait_enter();
	



	al_destroy_font(font);
}


/**
 * @brief funkcja rysująca tabele w formie graficznych kolumn
 *
 * funkcja rysuje tabele w formie kolumn na ekranie wypełniających cały ekran
 *
 * @param array - wskaźnik na tablice do wyświetlenia
 * @param N - ilość elementów w tablice
 * @param max - wartość maksymalnego elementu w tabeli
 * @param r - wartość koloru czerwonego
 * @param g - wartość koloru zielonego
 * @param b - wartość koloru niebieskiego
 */

void draw_array(int array[], int N, int max, int r,int g,int b)
{
	float size_h =   SCREEN_H/(float)max;
	float size_w = SCREEN_W / (float)N;
	ALLEGRO_COLOR color = al_map_rgb(r, g, b);
	for (int i = 0; i < N; i++)
	{

		al_draw_filled_rectangle(i* size_w, SCREEN_H, i * size_w+ size_w, SCREEN_H-array[i] * size_h, color);

	}
	
	al_flip_display();
}

/**
 * @brief funkcja wyświetlająca menu do wpisywania wartości
 *
 * funkcja wyświetla komunikat podaje jako parametr i umożliwia użytkownikowi wpisanie wartości liczbowej która jest zwracana
 *
 * @param messsege - ciągów znaków wyświetlany jako nagłówek
 */

get_user_value(text messsege)
{

	ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);
	ALLEGRO_COLOR black = al_map_rgb(0, 0, 0);
	ALLEGRO_COLOR red = al_map_rgb(255, 0, 0);
	ALLEGRO_COLOR choice_color = al_map_rgb(50, 20, 10);
	ALLEGRO_FONT* font = al_load_ttf_font("arial.ttf", 25, NULL);
	float width = al_get_text_width(font, messsege);
	float height = al_get_font_line_height(font);
	text input = "";
	int N=-1;
	char c='\0';
	al_clear_to_color(black);
	
	ALLEGRO_EVENT_QUEUE* q = al_create_event_queue();
	al_register_event_source(q, al_get_keyboard_event_source());
	char if_negative = 0;
	while (1)
	{
		ALLEGRO_EVENT ev;
		al_draw_text(font, red, SCREEN_W / 2 - width / 2, 20, 0, messsege);

		


		float width = al_get_text_width(font, input);
		al_draw_text(font, red, SCREEN_W / 2 - width / 2, 80, 0, input);


		al_flip_display();
		
		al_wait_for_event(q, &ev);
		if (ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			if (ev.keyboard.keycode == ALLEGRO_KEY_ENTER)
				break;
			if (ev.keyboard.keycode == ALLEGRO_KEY_BACKSPACE && N >= 0)
			{
				input[N] = '\0';
				N--;
			}
			if ( N <=0 && ev.keyboard.keycode==ALLEGRO_KEY_MINUS)
			{
				c = '-';
				input[++N] = c;
				input[N + 1] = '\0';
			}
			
			
			
			if ((ev.keyboard.keycode) >=27 && (ev.keyboard.keycode) <=46 && N<=7)
			{
				c = (ev.keyboard.keycode-7 ) % 10+48;
				input[++N] = c;
				input[N+1] = '\0';
			}

		}
		al_clear_to_color(black);
	}
	
	int a = atoi(input);

	al_destroy_event_queue(q);
	al_destroy_font(font);
	return a;

}

/**
 * @brief funkcja wyświetlająca graficznie tablice wartości z możliwością oznaczenia 2 elementów kolorem żółtym i 2 elementów zielonym
 *
 * funkcja wyświetla tablica graficznie w formie kolumn z tą różnica że że wybrane 2 zielone elementy wyświetlają się na zielono a 2
 * wybrane elementy wyświetlają się na żółto
 *
 * @param array - wskaźnik na tablice do wyświetlenia
 * @param N - ilość elementów tablicy
 * @param max - wartość maksymalnego elementu tablicy
 * @param g - indeks elementu do narysowania na zielono
 * @param g1 - indeks drugiego elementu do narysowania na zielono
 * @param y - indeks elementu do narysowania na żółto
 * @param y2 - indeks drugiego elementu do narysowania na żółto
 */

void draw_array_a(int array[], int N, int max, int g, int g1, int y, int y2)
{
	float size_h = SCREEN_H / (float)max;
	float size_w = SCREEN_W / (float)N;
	ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);
	ALLEGRO_COLOR green = al_map_rgb(0, 255, 0);
	ALLEGRO_COLOR yellow = al_map_rgb(255, 255, 0);
	for (int i = 0; i < N; i++)
	{

		if (i == g)
		{
			al_draw_filled_rectangle(i * size_w, SCREEN_H, i * size_w + size_w, SCREEN_H - array[i] * size_h, green);
		}
		else
			if (i == g1)
			{
				al_draw_filled_rectangle(i * size_w, SCREEN_H, i * size_w + size_w, SCREEN_H - array[i] * size_h, green);;
			}
			else
				if (i == y)
				{
					al_draw_filled_rectangle(i * size_w, SCREEN_H, i * size_w + size_w, SCREEN_H - array[i] * size_h, yellow);
				}
				else
					if (i == y2)
					{
						al_draw_filled_rectangle(i * size_w, SCREEN_H, i * size_w + size_w, SCREEN_H - array[i] * size_h, yellow);
					}
					else
		al_draw_filled_rectangle(i * size_w, SCREEN_H, i * size_w + size_w, SCREEN_H - array[i] * size_h, white);

	}

	al_flip_display();
}


/**
 * @brief menu odpowiedzialne za zaobserwowanie algorytmu sortowania
 *
 * funkcja ta pozwala na wybór na jak wypełnionej tablicy użytkownik chce obserwować tablice,
 * ,czy chce zaobserwować od razu całe sortowanie czy może krok po kroku,
 * czy chce zaobserwować sortowanie shella czy przez wstawianie ,
 *
 */

void observation_ui()
{

	text messege = "Na ilu elementach chcialbys przetestowac sortowanie";
	int N = get_user_value(messege);
	int* array = calloc(N, sizeof(int));
	text choices[] = { "Na jakiej tabeli chcesz obserwowac","losowej","odwrotnej","pomieszanej"};
	int max = N;
	int ch = choice_menu(choices, 3);
	int min = 0;
	if (ch == 0)
	{
		
		 max = get_user_value("Podaj maksymalny  zakres losowania");
		fill_array_rand(array, N, min, max);
	}
	else
	{
		fill_array_reverse(array, N);
		if (ch == 2)
		{
			shuffle_arry(array, N);
		}
	}

	al_rest(0.1);

	//print_array(array, N);
	text choices2[] = {"Wolisz przetestować na krok po kroku czy cala operacje", "krok po kroku", "cala"};
	ch= choice_menu(choices2, 2);
	al_rest(0.1);
	text choices3[] = { "wolisz algorytm shell sort czy insert ", "shell", "insert" };
	int ch1 = choice_menu(choices3, 2);
	if (ch == 0)
	{
		 
		 if (ch1 == 0)
		{
			 press_enter();
			 shell_sort_draw_step(array, N, max);
		}
		else
		{
			 press_enter();
			 insert_sort_draw_step(array, N, max);
		}
	}
	else
	{ 
		
		if (ch1 == 0)
		{
			shell_sort_draw(array, N, max);
		}
		else
		{
			insert_sort_draw(array, N, max);
		}
	}
	ALLEGRO_KEYBOARD_STATE key;
	while (1)
	{
		al_get_keyboard_state(&key);
		if(al_key_down(&key,ALLEGRO_KEY_ENTER))
			break;
	}
}



/**
 * @brief funkcja generuje tabele czasu sortowania w zależności od elementów
 *
 * funkcja generuje bitmapę tabeli z danymi odnośnie czasu sortownia
 *
 * @param amount_of_elements - ilość elementów tablicy do wyświetlenia
 * @param data - wskaźnik tablice zawierające dane do wyświetlenia
 * @return ALLEGRO_BITMAP* - zwraca wygenerowana tablice w formie bitmapy
 */

ALLEGRO_BITMAP* generate_bitmap(int amount_of_elements, timers data[] )
{
	ALLEGRO_BITMAP* bitmap = al_create_bitmap(ARRAT_ELEMENT_WIDTH * 3, amount_of_elements * UPPER_COMENT_H);
	al_set_target_bitmap(bitmap);
	al_clear_to_color(al_map_rgb(255, 255, 255));
	//al_draw_filled_rectangle(0, 0, 500, 500, al_map_rgb(255, 0, 0));
	ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);
	ALLEGRO_COLOR black = al_map_rgb(0, 0, 0);
	ALLEGRO_FONT* font = al_load_ttf_font("arial.ttf", 25, NULL);
	text txt = "";
	int txtH = al_get_font_line_height(font);
	int txtW = 0;
	for (int i = 0; i < amount_of_elements; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			al_draw_filled_rectangle(ARRAT_ELEMENT_WIDTH * j + 1, UPPER_COMENT_H * i, ARRAT_ELEMENT_WIDTH + ARRAT_ELEMENT_WIDTH * j, UPPER_COMENT_H + UPPER_COMENT_H * i, al_map_rgb(50, 128 * i + 50, 128 * i));

			switch (j)
			{

			case 0: sprintf_s(txt, 200, "%d", data[i].amount); break;
			case 1: sprintf_s(txt, 200, "%.3f", data[i].insert_time); if (data[i].insert_time < 0) strncpy_s(txt,200, "", 200); break;
			case 2: sprintf_s(txt, 200, "%.3f", data[i].shell_time);  if (data[i].shell_time < 0) strncpy_s(txt, 200, "", 200); break;
			}
			txtW = al_get_text_width(font, txt);
			al_draw_text(font, white, ARRAT_ELEMENT_WIDTH/2 - txtW / 2 + ARRAT_ELEMENT_WIDTH * j, UPPER_COMENT_H * i + txtH / 4, 0, txt);



		}
	}


		return bitmap;
	}



/**
 * @brief segment menu odpowiadający za generowanie czasów sortowania
 *
 * funkcja generuje wstępne menu a następnie sortuje tabele w o ilości elementów w zależności od podanych argumentów, co każdą ilość
 * elementów wyświetlana tabela jest aktualizowana
 *
 * @param display - wskaźnika na ekran na którym ma być wyświetlane dane
 * @param def - wartość startowa oraz różnica pomiędzy kolejnymi ilościami danych do sortownia
 * @param max_el - maksymalna ilość elementów do dla których mogą być zbierane dane
 * @param ch_array - argument określający sposób wypełnienia tablicy
 * @param max - maksymalna wartość elementów do wypełnienia w przypadku wyboru wypełnienia losowego
 */

void generate_results(ALLEGRO_DISPLAY* display,int def, int max_el, int ch_array, int max)
{
	
	ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);
	ALLEGRO_COLOR black = al_map_rgb(0, 0, 0);
	ALLEGRO_COLOR green = al_map_rgb(10, 240, 10);
	ALLEGRO_FONT* font = al_load_ttf_font("arial.ttf", 25, NULL);

	al_draw_rectangle(0, 0, SCREEN_W, UPPER_COMENT_H, white, 2);
	al_clear_to_color(black);
	text messege = "prosze czekać generuje wyniki";
	int txt_h = al_get_font_line_height(font);
	int txt_w = al_get_text_width(font, messege);
	al_draw_text(font, white, SCREEN_W / 2- txt_w/2, UPPER_COMENT_H / 2- txt_h/2, 0, messege);
	


	for (int i = 0; i < 3; i++)
	{
		switch (i)
		{
		case 0: strncpy_s(messege, 250, "liczba elementów", 250); txt_w = al_get_text_width(font, messege); break;
		case 1: strncpy_s(messege, 250, "Insert_Sort", 250); txt_w = al_get_text_width(font, messege); break;
		case 2: strncpy_s(messege, 250, "Shell_Sort", 250); txt_w = al_get_text_width(font, messege); break;
		}
		al_draw_text(font, white, SCREEN_W / 2 - ((3 * ARRAT_ELEMENT_WIDTH) / 2) + ARRAT_ELEMENT_WIDTH * i+ ARRAT_ELEMENT_WIDTH/2- txt_w /2, UPPER_COMENT_H, 0, messege);
		al_draw_rectangle(SCREEN_W / 2 - ((3 * ARRAT_ELEMENT_WIDTH)/2) + ARRAT_ELEMENT_WIDTH * i, UPPER_COMENT_H, SCREEN_W / 2 - ((3 * ARRAT_ELEMENT_WIDTH) / 2) + ARRAT_ELEMENT_WIDTH * (i+1), UPPER_COMENT_H * 2, al_map_rgb(100*i+100,100+200*i,100+300*i), 2);
	}



	int amount_of_elements = max_el / def;

	
	timers* data = calloc(amount_of_elements, sizeof(timers));
	for (int i = 0; i < amount_of_elements; i++)
	{
		data[i].amount = def * (i + 1);
		data[i].insert_time = -1;
		data[i].shell_time = -1;
	}






	ALLEGRO_BITMAP* bitmap = generate_bitmap(amount_of_elements,data,display);
	al_set_target_backbuffer(display);



	ALLEGRO_MOUSE_STATE mouse;
	float scroll = 0;
	int min = 0;

	FILE* file;
	fopen_s(&file, "results.txt", "w");
	
	for (int i = 0; i < amount_of_elements; i++)
	{
		al_destroy_bitmap(bitmap);
		int* array = (int*)calloc((i + 1) * def, sizeof(int));



		if (ch_array == 0)
		{
			fill_array_rand(array, (i + 1) * def, min, max);
		}
		else
		{
			fill_array_reverse(array, (i + 1) * def);
			if (ch_array == 2)
			{
				shuffle_arry(array, (i + 1) * def);
			}
		}







		data[i].shell_time = calc_time(array, (i + 1) * def, shell_sort);
		data[i].insert_time = calc_time(array, (i + 1) * def, insert_sort);
		bitmap = generate_bitmap(amount_of_elements, data);
		al_set_target_backbuffer(display);
		al_draw_bitmap_region(bitmap, 0, i > 16 ? UPPER_COMENT_H * (i - 16) : 0, al_get_bitmap_width(bitmap), al_get_bitmap_height(bitmap), SCREEN_W / 2 - ((3 * ARRAT_ELEMENT_WIDTH) / 2) + ARRAT_ELEMENT_WIDTH * 0, UPPER_COMENT_H * 2, 0, 0);

		al_flip_display();
	




		fprintf(file, "%d;%.3f;%.3f\n", (i + 1) * def, data[i].insert_time, data[i].shell_time);


	
		free(array);
	}

	fclose(file);


	





	al_draw_filled_rectangle(0, 0, SCREEN_W, UPPER_COMENT_H, green );
	strcpy_s( messege,200, "Wyniki zapisane w pliku resuluts.txt, wcisnij enter, aby kontynuowac",200);
	txt_w = al_get_text_width(font, messege);
	al_draw_text(font, white, SCREEN_W / 2 - txt_w / 2, UPPER_COMENT_H / 2 - txt_h / 2, 0, messege);





		ALLEGRO_KEYBOARD_STATE key;


		al_set_target_backbuffer(display);
		int is_done = 1;

		do
	{
			al_get_mouse_state(& mouse);
		al_get_keyboard_state(&key);
		if (al_key_down(&key, ALLEGRO_KEY_ENTER))
			is_done=0;
		
		
		

		if (mouse.z > 0)
		{
			al_set_mouse_z(0);
		}
		if (-mouse.z > (al_get_bitmap_height(bitmap) - (SCREEN_H - 2 * UPPER_COMENT_H))/10)
		{
			al_set_mouse_z(-((al_get_bitmap_height(bitmap) - (SCREEN_H - 2 * UPPER_COMENT_H)) / 10));
		}

		scroll = -1* mouse.z/ ((float)al_get_bitmap_height(bitmap)- (SCREEN_H - 2 * UPPER_COMENT_H));
		
		if (al_get_bitmap_height(bitmap) < SCREEN_H - 2 * UPPER_COMENT_H)
			scroll = 0;
		
		scroll *= 10;
			
		
		al_draw_bitmap_region(bitmap, 0, ((float)al_get_bitmap_height(bitmap) - (SCREEN_H - 2 * UPPER_COMENT_H)) * scroll, al_get_bitmap_width(bitmap), al_get_bitmap_height(bitmap), SCREEN_W / 2 - ((3 * ARRAT_ELEMENT_WIDTH) / 2) + ARRAT_ELEMENT_WIDTH * 0, UPPER_COMENT_H * 2, 0, 0);

		
	
	
	
	
	
	
	
		al_flip_display();
	
	} while (is_done);
	al_destroy_bitmap(bitmap);



	al_destroy_font(font);
	al_rest(0.3);
	generate_graph(data, amount_of_elements, display);
}

/**
 * @brief menu odpowiadające za wybór parametrów do porównywania sortownia
 *
 * funkcja ta pyta się użytkownika co ile elementów chce wygenerować dane , jaki jest górny limit elementów do obliczenia czasu
 *  jak ma być wypełniona tablica i maksymalna wartość elementów którymi będzie wypełniona w przypadku wypełnienia losowego
 *
 * @param display
 */

void cmp_ui(ALLEGRO_DISPLAY* display)
{
	
	int def = get_user_value("Podaj co ile elementów chcesz zbierać dane");
	int max_el = get_user_value("jaka jest maksymalna ilosc elementow");
	while (max_el < def){
		max_el = get_user_value("jaka jest maksymalna ilosc elementow");
}


	text choices[] = { "Na jakiej tabeli chcesz zaobserwowac","losowej","odwrotnej","pomieszanej" };
	int ch_array = choice_menu(choices, 3);
	int max = 0;
	al_rest(0.1);
	if (ch_array == 0)
	{

		max = get_user_value("Podaj maksymalny  zakres losowania");
	}
	
	
	generate_results(display,def,max_el, ch_array,max);
	
	
	
	

}

/**
 * @brief menu odpowiadające za wybór dalszego działania programu
 *
 * funkcja pozwala wybrać użytkownikowi czy che zaobserwować działanie algorytmu czy wygenerować dane odnośnie czasu sortowania
 *
 * @param display - wskaźnik na ekran na którym ma być rysunki
 */

void decision_ui(ALLEGRO_DISPLAY* display)
{


		text choice[] = { "Co chcialbys zrobic", "Porownac predkosc dzialania algorytmow", "Zaobserwowac dzialanie algorytmow" };
		al_rest(0.2);
		int ch = choice_menu(choice, 2);
		if (ch == 1)
			observation_ui();
		else
			cmp_ui(display);


	

}



/**
 * @brief menu startowe
 *
 * funkcja wyświetla menu startowego pozwalające na kontynuowanie pracy z programem lub jej zakończenie
 *
 * @param display - wskaźnik na ekran na którym ma być rysunki
 */

void start_ui(ALLEGRO_DISPLAY* display)
{
	while (1)
	{
		
		text choice[] = { "Witaj w porownaniu sortowania shell i insert", "kontynuuj", "zakoncz" };
		int ch = choice_menu(choice, 2);
		if (ch == 1)
			return 0;
		else
			decision_ui(display);




	}

}






/**
 * @brief * funkcja rozpoczynająca działanie programu w formie graficznej
 *
 */

void start_gui()
{
	ALLEGRO_DISPLAY* display;
	al_init();
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_keyboard();
	al_install_mouse();
	al_init_image_addon();
	display = al_create_display(SCREEN_W, SCREEN_H);

	start_ui(display);



	/*
	timers tmp[] = { 
		
		{10000,0.107,0.001},
		{20000,0.409,0.001},
		{30000,0.909,0.001},
		{40000,1.744,0.002},
		{50000,2.580,0.003},
		{60000,3.598,0.004}, 
		{70000,5.129,0.005},
		{80000,6.838,0.005},
		{90000,8.565,0.006},
		{100000,9.989,0.007}
	};
	 generate_graph(tmp, sizeof(tmp) / sizeof(tmp[0]), display);
	 */


	al_destroy_display(display);
}