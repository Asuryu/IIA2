
#ifndef UTILS_H
#define UTILS_H
#include "evolutivo.h"

void mostraASCII();

int *preenche_matriz(char *file, int *v, int *numero_iteracoes);
void gerar_solinicial(int *sol, int v);
void escrever_solucao(int *sol, int v);
void substitui(int a[], int b[], int n);

int random_int(int minimo, int maximo);
float random_float_01();
int probEvento(float prob);
int calcIndice(int i, int j, int cols);

info init_data(int arestas, int vertices);
pchrom init_pop(info d);
chrom get_best(pchrom pop, info d, chrom best);
void write_best(chrom x, info d);
void gera_sol_inicial(int *sol, int v);
int** init_dados(char *nome, int *vertices, int *arestas);

#endif // UTILS_H
