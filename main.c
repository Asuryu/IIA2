#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "utils.h"
#include "engine.h"
#include "pesquisaLocal.h"

int main() {
    char file[100];
    int runs = 10;
    int iter, vert, custo, bestCusto;
    int *matriz, *solucao, *best;
    float mbf = 0.0;
    srand((unsigned)time(NULL));

    printf("Introduza o nome do ficheiro: ");
    fgets(file, 100, stdin);
    file[strlen(file) - 1] = '\0';
    printf("\n");

    matriz = preenche_matriz(file, &vert, &iter);
    solucao = malloc(sizeof(int) * vert);
    best = malloc(sizeof(int) * vert);

    if (solucao == NULL || best == NULL) {
        printf("Erro na alocacao de memoria!");
        exit(1);
    }

    int i;
    for (i = 0; i < runs; i++) {
        gerar_solinicial(solucao, vert);
        escrever_solucao(solucao, vert);

        custo = trepaColinas(solucao, matriz, vert, iter);

        printf("\nRepeticao %d: ", i);
        escrever_solucao(solucao, vert);
        printf("Custo final: %2d\n", custo);
        mbf += custo;
        if (i == 0 || bestCusto > custo) {
            bestCusto = custo;
            substitui(best, solucao, vert);
        }
    }

    // Escreve resultados globais
    printf("\n\nMBF: %f\n", mbf / i);
    printf("\nMelhor solucao encontrada");
    escrever_solucao(best, vert);
    printf("Custo final: %2d\n", bestCusto);

    free(matriz);
    free(solucao);
    free(best);

    return 0;
}
