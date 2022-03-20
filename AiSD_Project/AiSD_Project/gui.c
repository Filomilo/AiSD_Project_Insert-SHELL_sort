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


void wait_enter()
{
	al_rest(0.2);
	ALLEGRO_KEYBOARD_STATE key;

	while (1)
	{
		al_get_keyboard_state(&key);
		if (al_key_down(&key, ALLEGRO_KEY_ENTER))
			break;
	}
}


void press_enter()
{
	ALLEGRO_COLOR black = al_map_rgb(0, 0, 0);
	ALLEGRO_COLOR white = al_map_rgb(255,255,255);
	al_clear_to_color(black);
	ALLEGRO_FONT* font = al_load_ttf_font("arial.ttf", 25, NULL);
	text txt = "wcisninj enter aby kontynuwac";
	float width = al_get_text_width(font, txt);
	float height = al_get_font_line_height(font);
	al_draw_text(font, white, SCREEN_W / 2 - width / 2, SCREEN_H / 2 + height, 0, txt);
	al_flip_display();
	wait_enter();
	



	al_destroy_font(font);
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

			if (ev.keyboard.keycode + 11 >= '0' && ev.keyboard.keycode + 11 <= '9' && N<=7)
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
	text choices[] = { "na jakiej tabeli chesz osberowac","losowej","odworoenj","pomiesznej"};
	int max = N;
	int ch = choice_menu(choices, 3);
	int min = 0;
	if (ch == 0)
	{
		
		 max = get_user_value("podaj maksymlany  zakres lsowania");
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
	text choices2[] = {"wolisz prztestowac na krok po kroku czy czy cala operacje", "krok po korku", "cale"};
	ch= choice_menu(choices2, 2);
	al_rest(0.1);
	text choices3[] = { "wolisz algorytm shell sort czy isnert ", "shell", "insesrt" };
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



void cmp_ui()
{
	ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);
	ALLEGRO_COLOR black = al_map_rgb(0, 0, 0);
	ALLEGRO_FONT* font = al_load_ttf_font("arial.ttf", 25, NULL);
	int def = get_user_value("podaj co ile mentow cheszcz zbierac dane");
	int max_el = get_user_value("jakka jest maksymlana ilosc elemtow");
	while (max_el < def){
		max_el = get_user_value("jakka jest maksymlana ilosc elemtow");
}


	text choices[] = { "na jakiej tabeli chesz osberowac","losowej","odworoenj","pomiesznej" };
	int ch_array = choice_menu(choices, 3);
	int min = 0;
	int max = 0;
	al_rest(0.1);
	if (ch_array == 0)
	{

		max = get_user_value("podaj maksymlany  zakres lsowania");
	}
	text choices2[] = { "sortowac wzgledem czasu wykonia czy ilosci operacji","czas","opracje" };
	int ch_data = choice_menu(choices2, 2);


	al_clear_to_color(black);
	text txt = "prosze czekac genrueje dane";
	float width = al_get_text_width(font, txt);
	float height = al_get_font_line_height(font);
	al_draw_text(font, white, SCREEN_W / 2 - width / 2,  height+20, 0, txt);
	
	
	strcpy_s(txt,150, "elemnety w tabeli");
	 width = al_get_text_width(font, txt);
	 height = al_get_font_line_height(font);
	al_draw_text(font, white, SCREEN_W / 2 - width / 2, height + 20+height*2, 0, txt);
	float width_cube=(SCREEN_W)/((int)(max_el / def));
	for (float i = 0; i < SCREEN_W; i += width_cube)
	{
		al_draw_rectangle(i, height + 20 + height * 3, i + width_cube, height + 20 + height * 4,white,2);

	}


	strcpy_s(txt, 150, "shell sort");
	width = al_get_text_width(font, txt);
	height = al_get_font_line_height(font);
	al_draw_text(font, white, SCREEN_W / 2 - width / 2, height + 20 + height * 9, 0, txt);
	for (float i = 0; i < SCREEN_W; i += width_cube)
	{
		al_draw_rectangle(i, height + 20 + height * 10, i + width_cube, height + 20 + height * 11, white, 2);

	}

	strcpy_s(txt, 150, "insert sort");
	width = al_get_text_width(font, txt);
	height = al_get_font_line_height(font);
	al_draw_text(font, white, SCREEN_W / 2 - width / 2, height + 20 + height * 5, 0, txt);
	for (float i = 0; i < SCREEN_W; i += width_cube)
	{
		al_draw_rectangle(i, height + 20 + height * 6, i + width_cube, height + 20 + height * 7, white, 2);

	}
	FILE* file;
	fopen_s(&file, "results.txt", "w");
	fprintf(file, "ilosc; czas insert; czas shell\n");
	int counter = 0;
	float time_insert = 0;
	float time_shell= 0;
	int dif = max_el / def;
	int j = 0;
	if(ch_data==0)
	for (int i = def; i <= max_el; i += def)
	{
		int* array = (int*)calloc(i, sizeof(int));
		


		if (ch_array == 0)
		{
			fill_array_rand(array, i, min, max);
		}
		else
		{
			fill_array_reverse(array, i);
			if (ch_array == 2)
			{
				shuffle_arry(array, i);
			}
		}


		sprintf_s(txt, 150, "%d", i);
		width = al_get_text_width(font, txt);
		height = al_get_font_line_height(font);
		al_draw_text(font, white, width_cube / 2 + (j * width_cube) - width / 2, height + 20 + height * 3, 0, txt);



		time_shell = calc_time(array, i, shell_sort);
		sprintf_s(txt, 150, "%.2f", time_shell);
		width = al_get_text_width(font, txt);
		height = al_get_font_line_height(font);
		al_draw_text(font, white, width_cube / 2 + (j * width_cube) - width / 2, height + 20 + height * 10, 0, txt);
		al_flip_display();





		time_insert = calc_time(array, i, insert_sort);
		sprintf_s(txt, 150, "%.2f", time_insert);
		width = al_get_text_width(font, txt);
		height = al_get_font_line_height(font);
		al_draw_text(font, white, width_cube / 2 + (j * width_cube) - width / 2, height + 20 + height * 6, 0, txt);
		al_flip_display();




		fprintf(file, "%d;%.3f;%.3f\n", i, time_insert, time_shell);

	

		j++;
		free(array);
	}
	else
	{
		for (int i = def; i <= max_el; i += def)
		{
			int* array = (int*)calloc(i, sizeof(int));



			if (ch_array == 0)
			{
				fill_array_rand(array, i, min, max);
			}
			else
			{
				fill_array_reverse(array, i);
				if (ch_array == 2)
				{
					shuffle_arry(array, i);
				}
			}


			sprintf_s(txt, 150, "%d", i);
			width = al_get_text_width(font, txt);
			height = al_get_font_line_height(font);
			al_draw_text(font, white, width_cube / 2 + (j * width_cube) - width / 2, height + 20 + height * 3, 0, txt);



			time_shell = calc_proces(array, i, shell_sort_calc);
			sprintf_s(txt, 150, "%.0f", time_shell);
			width = al_get_text_width(font, txt);
			height = al_get_font_line_height(font);
			al_draw_text(font, white, width_cube / 2 + (j * width_cube) - width / 2, height + 20 + height * 10, 0, txt);
			al_flip_display();





			time_insert = calc_proces(array, i, insert_sort_calc);
			sprintf_s(txt, 150, "%.0f", time_insert);
			width = al_get_text_width(font, txt);
			height = al_get_font_line_height(font);
			al_draw_text(font, white, width_cube / 2 + (j * width_cube) - width / 2, height + 20 + height * 6, 0, txt);
			al_flip_display();




			fprintf(file, "%d;%.0f;%.0f\n", i, time_insert, time_shell);



			j++;
			free(array);
		}

	}




	strcpy_s(txt, 150, "wniki zpaisane w pliku results.txt");
	width = al_get_text_width(font, txt);
	height = al_get_font_line_height(font);
	al_draw_text(font, white, SCREEN_W / 2 - width / 2, height + 20 + height * 22, 0, txt);
	
	
	









	fclose(file);
	
	
	
	
	
	
	
	
	
	al_flip_display();


	





	wait_enter();
	al_destroy_font(font);

}

void decision_ui()
{


		text choice[] = { "co chialbys zrobic", "porwonac prekosc dzialania algorytmow", "zaobserowac dzialanie algorytmow" };
		al_rest(0.2);
		int ch = choice_menu(choice, 2);
		if (ch == 1)
			observation_ui();
		else
			cmp_ui();


	

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
	//text a[] = { "123","aaaaaaaaa","bbbbbbbbbb","cccccccccccc","ddddddddddd","eeeeeeeeeeeeeeeeeee","eeeeeeeeeeeeeeeeeee" ,"eeeeeeeeeeeeeeeeeee" ,"eeeeeeeeeeeeeeeeeee" ,"eeeeeeeeeeeeeeeeeee" ,"eeeeeeeeeeeeeeeeeee" ,"eeeeeeeeeeeeeeeeeee" ,"eeeeeeeeeeeeeeeeeee" ,"eeeeeeeeeeeeeeeeeee" ,"eeeeeeeeeeeeeeeeeee" ,"eeeeeeeeeeeeeeeeeee" ,"eeeeeeeeeeeeeeeeeee" ,"eeeeeeeeeeeeeeeeeee" ,"eeeeeeeeeeeeeeeeeee" ,"eeeeeeeeeeeeeeeeeee" ,"eeeeeeeeeeeeeeeeeee" };
	//choice_menu(a, 2);




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