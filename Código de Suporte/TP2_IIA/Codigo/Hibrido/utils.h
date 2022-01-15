#ifndef UTILS_H
#define UTILS_H



int probEvento(float prob);
int * gera_random_lookup_table(int vert);
int offset(int i, int j, int cols);
void gera_sol_inicial(int *sol, int v);



int * init_data(char *filename, struct info * x);

pchrom init_pop(struct info d, int aplicaTrepaColinas, int * grafo);

void print_pop(pchrom pop, struct info d);

chrom get_best(pchrom pop, struct info d, chrom best);

void write_best(chrom x, struct info d);

void init_rand();

int random_l_h(int min, int max);

float rand_01();

int flip();

#endif	// UTILS_H

