#ifndef UTILS_H
#define UTILS_H

int probEventoTC(float prob);
int * gera_random_lookup_tableTC(int vert);
int offsetTC(int i, int j, int cols);
void gera_sol_inicialTC(int *sol, int v);
void escreve_solTC(int *sol, int vert);
void substituiTC(int a[], int b[], int n);
void init_randTC();
int random_l_hTC(int min, int max);
float rand_01TC();

#endif	// UTILS_H

