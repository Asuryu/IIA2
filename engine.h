#ifndef ENGINE_H
#define ENGINE_H
#include "evolutivo.h"

int calcula_fit(int a[], int *mat, int vert);
int validar_solucao(int *solucao,int *matriz, int vertices);

float eval_fit(int sol[], info d, int **mat);
void evaluate(pchrom pop, info d, int **mat);

#endif // ENGINE_H
