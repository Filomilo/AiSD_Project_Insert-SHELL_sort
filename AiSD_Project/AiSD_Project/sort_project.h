#ifndef SORT_PROJECT
#define SORT_PROJECT

//algorytmy sortowania


extern void insert_sort(int* array, int N);

extern void shell_sort(int* array, int N);



//zarzadzanie tabela

extern void print_array(int* array, int N);

extern void fill_array_rand(int* array, int N, int min, int max);
extern void fill_array_reverse(int* array, int N);


#endif