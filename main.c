#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include ".\utils.h"
#include ".\funcao.h"
#include ".\algoritmo.h"

#define DEFAULT_RUNS 10

int main() {
    char nome_ficheiro[100];
    int numero_iteracoes = 0, nvertices = 0;
    int *matriz, *solucao, *melhorSolucao, custo, runs = DEFAULT_RUNS, melhorCusto = 0;
    float mbf = 0.0;

    printf("Nome do ficheiro: ");
    gets(nome_ficheiro);
    printf("\n");

//=================== TREPA COLINAS =======================================
    int i;

    matriz = setMatriz(nome_ficheiro, &nvertices, &numero_iteracoes);

    solucao = malloc(sizeof(int) * nvertices);
    melhorSolucao = malloc(sizeof(int) * nvertices);

    if (solucao == NULL || melhorSolucao == NULL) {
        printf("Erro na alocacao de memoria!");
        exit(1);
    }

    for (i = 0; i < runs; i++) {
        gerar_solucaoInicial(solucao, nvertices);
        escrever_solucao(solucao, nvertices);

        custo = trepaColinas(solucao, matriz, nvertices, numero_iteracoes);

        // Escreve resultados desta repetição 'i'
        printf("\nRepeticao %d: ", i);
        escrever_solucao(solucao, nvertices);
        printf("Custo final: %2d\n", custo);
        mbf += custo;
        if (i == 0 || melhorCusto > custo) {
            melhorCusto = custo;
            substitui(melhorSolucao, solucao, nvertices);
        }
    }

    // Escreve resultados globais
    printf("\n\nMBF: %f\n", mbf / i);
    printf("\nMelhor solucao encontrada");
    escrever_solucao(melhorSolucao, nvertices);
    printf("Custo final: %2d\n", melhorCusto);

    free(matriz);
    free(solucao);
    free(melhorSolucao);

    return 1;
}
