#ifndef PESQUISALOCAL_H
#define PESQUISALOCAL_H

void gerar_vizinho(int *sol, int *vizinho, int vertices);
void gerar_vizinho2(int *sol, int *vizinho, int vertices);
int trepaColinas(int sol[], int *matriz, int vertices, int iter);
int trepaColinasProb(int sol[], int *matriz, int vertices, int iter);

#endif // PESQUISALOCAL_H
