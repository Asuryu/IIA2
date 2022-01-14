#ifndef TPV2_ALGORITMO_H
#define TPV2_ALGORITMO_H

void gerar_vizinho(int *solucao, int *vizinho, int n);
int trepaColinas(int solucao[], int *matriz, int vertices, int nIteracoes);
int trepaColinasProb(int solucao[], int *matriz, int vertices, int nIteracoes);

#endif //TPV2_ALGORITMO_H
