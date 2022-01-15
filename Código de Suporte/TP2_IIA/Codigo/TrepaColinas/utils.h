#ifndef UTILS_H
#define UTILS_H

int probEvento(float prob);
int * gera_random_lookup_table(int vert);
int offset(int i, int j, int cols);
int* init_dados(char *nome, int *n, int *iter);
void gera_sol_inicial(int *sol, int v);
void escreve_sol(int *sol, int vert);
void substitui(int a[], int b[], int n);
void init_rand();
int random_l_h(int min, int max);
float rand_01();

#endif	// UTILS_H

