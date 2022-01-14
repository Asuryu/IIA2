
#ifndef CODIGO_UTILS_H
#define CODIGO_UTILS_H


int *setMatriz(char *nome_ficheiro, int *v, int *numero_iteracoes);
void gerar_solucaoInicial(int *solucao, int v);
void escrever_solucao(int *solucao, int v);
void substitui(int a[], int b[], int n);

void init_rand();
int random(int minimo, int maximo);
float random_0e1();

#endif //CODIGO_UTILS_H
