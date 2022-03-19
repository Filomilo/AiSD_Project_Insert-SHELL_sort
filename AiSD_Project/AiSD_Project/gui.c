#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include "sort_project.h"
#include <string.h>
#include <stdio.h>
#include <math.h>

#define M_PI 3.14159265359
#define SCREEN_H 720
#define SCREEN_W 1280


typedef char text[250];





float absf(float x)
{
	if (x >= 0)
		return x;
	return -x;

}


int choice_menu(text choices[], int N)
{
	
	ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);
	ALLEGRO_COLOR black = al_map_rgb(0, 0, 0);
	ALLEGRO_COLOR red = al_map_rgb(255, 0, 0);
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
		for (int i=0; i < N; i++)
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
		al_draw_filled_ellipse(SCREEN_W / 2, SCREEN_H / 2, 200, 100, white);
		float width = al_get_text_width(font, choices[0]);
		float height = al_get_font_line_height(font);
		al_draw_text(font, red, SCREEN_W / 2 - width / 2, SCREEN_H/2-height/2, 0, choices[0]);
		for (int i = 0; i < N; i++)
		{
			int dist = 500;
			float rad2 = seg / 2 + seg * i;
			float mult = (absf(absf(rad2 + M_PI) - M_PI * 0.5 + 0.5)) * dist;
			 width = al_get_text_width(font, choices[i+1]);
			al_draw_text(font, red, SCREEN_W/2+ mult *cos(rad2)-width/2, SCREEN_H/2 + mult *sin(rad2), 0, choices[i + 1]);

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

			if (ev.keyboard.keycode + 11 >= '0' && ev.keyboard.keycode + 11 <= '9' && N<=6)
			{
				c = ev.keyboard.keycode + 11;

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



void observation_ui()
{

	text messege = "na ilu lemntach chia³byœ przetesotwac sortowanie";
	int N = get_user_value(messege);
	int* array = calloc(N, sizeof(int));
	text choices[] = { "wolisz przetesoowac na lsowej tabeli czy odworcej","losowej","odworoenj" };
	int max = 0;
	int ch = choice_menu(choices, 2);
	if (ch == 0)
	{
		int min = 0;
		 max = get_user_value("podaj maksymlany  zakres lsowania");
		fill_array_rand(array, N, min, max);
	}
	else
	{
		fill_array_reverse(array, N);
	 max = N;
	}

	al_rest(0.01);

	print_array(array, N);
	text choices2[] = {"wolisz prztestowac na krok po kroku czy czy cala operacje", "krok po korku", "cale"};
	ch= choice_menu(choices2, 2);
	al_rest(0.1);
	text choices3[] = { "wolisz algorytm shell sort czy isnert ", "shell", "insesrt" };
	int ch1 = choice_menu(choices3, 2);
	if (ch == 0)
	{
		 
		 if (ch1 == 0)
		{

		}
		else
		{

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


void decision_ui()
{


		text choice[] = { "co chialbys zrobic", "porwonac prekosc dzialania algorytmow", "zaobserowac dzialanie algorytmow" };
		
		int ch = choice_menu(choice, 2);
		if (ch == 1)
		observation_ui();


	

}




void start_ui()
{
	while (1)
	{
		
		text choice[] = { "witaj w porwnaniu osrtowania shell i insert", "kontunuj", "zakoncz" };
		int ch = choice_menu(choice, 2);
		if (ch == 1)
			return 0;
		else
			decision_ui();




	}

}







void start_gui()
{
	ALLEGRO_DISPLAY* display;
	al_init();
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_keyboard();
	al_install_mouse();
	display = al_create_display(SCREEN_W, SCREEN_H);

	 start_ui();
	//observation_ui();






	/*
	int N = 500;
	int min = 0;
	int max = N;
	int* array = calloc(N, sizeof(int));
	fill_array_reverse(array, N);
	//fill_array_rand(array,N, min, max);
	print_array(array, N);
	draw_array(array, N, max, 255, 255, 255);
	getchar();
	//shell_sort_draw(array, N, max);
	
	insert_sort_draw(array, N, max);
	*/

	al_destroy_display(display);
}