#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "pesquisaLocal.h"

int main(){

    int vert, ares, custo, best_custo=0, k;
    int *grafo, *sol, *best;
    char nomeFicheiro[100];
    float mbf = 0.0;
    srand((unsigned)time(NULL));

    printf("Introduza o nome do ficheiro com os dados: ");
    scanf("%s", nomeFicheiro);

    grafo = init_dados(nomeFicheiro, &vert, &ares);
    sol = malloc(sizeof(int)*vert);
    best = malloc(sizeof(int)*vert);
    printf("grafo: %d %d\n", vert, ares);
    gera_sol_inicial(sol, vert);
    for(k=0; k<5; k++)
	{
		// Gerar solucao inicial
		gera_sol_inicial(sol, vert);
		escreve_sol(sol, vert);
		// Trepa colinas
		custo = trepa_colinas(sol, grafo, vert, ares);
		// Escreve resultados da repeticao k
		printf("\nRepeticao %d:", k);
		escreve_sol(sol, vert);
		printf("Custo final: %2d\n", custo);
		mbf += custo;
		if(k==0 || best_custo > custo)
		{
			best_custo = custo;
			substitui(best, sol, vert);
		}
    }
	// Escreve eresultados globais
	printf("\n\nMBF: %f\n", mbf/k);
	printf("\nMelhor solucao encontrada");
	escreve_sol(best, vert);
	printf("Custo final: %2d\n", best_custo);
	free(grafo);
    free(sol);
	free(best);

    return 0;
}