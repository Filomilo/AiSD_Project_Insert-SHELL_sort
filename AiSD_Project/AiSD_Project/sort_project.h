#ifndef SORT_PROJECT
#define SORT_PROJECT

//algorytmy sortowania


extern void insert_sort(int* array, int N);

extern void shell_sort(int* array, int N);



extern int insert_sort_calc(int* array, int N);

extern int shell_sort_calc(int* array, int N);

extern void shell_sort_step(int* array, int N);
extern void insert_sort_step(int* array, int N);

//zarzadzanie tabela

extern void print_array(int* array, int N);

extern void fill_array_rand(int* array, int N, int min, int max);
extern void fill_array_reverse(int* array, int N);
extern void duplicate_array(int* array, int* array_to_copy, int N);




//zodbywanie danych
extern float calc_time(int* array, int N, void (*sort)(int*, int));
extern void generarate_times(int limit, int dif);

#endif