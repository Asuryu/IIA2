
#ifndef UTILS_H
#define UTILS_H


int *preenche_matriz(char *file, int *v, int *numero_iteracoes);
void gerar_solinicial(int *sol, int v);
void escrever_solucao(int *sol, int v);
void substitui(int a[], int b[], int n);

void init_rand();
int random_int(int minimo, int maximo);
float random_float_01();

#endif // UTILS_H
