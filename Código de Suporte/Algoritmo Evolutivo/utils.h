#include "algoritmo.h"

int** init_dados(char *nome, int *vertices, int *arestas);
void init_rand();
void gera_sol_inicial(int *sol, int v);
int random_l_h(int min, int max);
float rand_01();
info init_data(int arestas, int vertices);
pchrom init_pop(info d);
chrom get_best(pchrom pop, info d, chrom best);
void write_best(chrom x, info d);
