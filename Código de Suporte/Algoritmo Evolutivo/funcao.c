#include <stdio.h>
#include <stdlib.h>
#include "funcao.h"
#include "algoritmo.h"

int eval_fit(int sol[], int **mat, int arestas) {
    int total = 0, aux,i;
    for ( i = 0; i < arestas; i++) {
        aux = abs(sol[mat[i][0] - 1] - sol[mat[i][1] - 1]);
        if (aux > total)//se o custo calculado anteriormente for maior que o total, iguala-se a esse
            total = aux;
    }
    return total;
}


void evaluate(pchrom pop, info d, int **mat) {
int i;
    for ( i = 0; i < d.pop; i++)
        pop[i].fitness = eval_fit(pop[i].p, mat, d.aresta); //Calcula o custo de cada solucao da populacao
}
