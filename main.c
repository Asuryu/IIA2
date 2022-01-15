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
    int iter, vert, custo, bestCusto, escolha;
    int *matriz, *solucao, *best;
    float mbf = 0.0;
    srand((unsigned)time(NULL));

    mostraASCII();
    printf("\n1 - Trepa Colinas (com vizinhança 1)");
    printf("\n2 - Trepa Colinas (com vizinhança 2)");
    printf("\n3 - Trepa Colinas (probabilístico)");
    printf("\n4 - Torneio Binário");
    printf("\n0 - Sair\n\nEscolha: ");
    scanf("%d", &escolha);
    int i;
    switch (escolha){
        case 1:
            mostraASCII();
            fflush(stdin);
            printf("Introduza o nome do ficheiro: ");
            fgets(file, 100, stdin);
            file[strlen(file) - 1] = '\0';
            printf("\n");

            matriz = preenche_matriz(file, &vert, &iter);
            solucao = malloc(sizeof(int) * vert);
            best = malloc(sizeof(int) * vert);

            if (solucao == NULL || best == NULL) {
                printf("[ERRO] Ocorreu um problema ao alocar memória.");
                exit(1);
            }

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

            printf("\n\nMBF: %f\n", mbf / i);
            printf("\nMelhor solucao encontrada");
            escrever_solucao(best, vert);
            printf("Custo final: %2d\n", bestCusto);

            free(matriz);
            free(solucao);
            free(best);
            break;
        case 2:
            mostraASCII();
            fflush(stdin);
            printf("Introduza o nome do ficheiro: ");
            fgets(file, 100, stdin);
            file[strlen(file) - 1] = '\0';
            printf("\n");

            matriz = preenche_matriz(file, &vert, &iter);
            solucao = malloc(sizeof(int) * vert);
            best = malloc(sizeof(int) * vert);

            if (solucao == NULL || best == NULL) {
                printf("[ERRO] Ocorreu um problema ao alocar memória.");
                exit(1);
            }

            for (i = 0; i < runs; i++) {
                gerar_solinicial(solucao, vert);
                escrever_solucao(solucao, vert);

                custo = trepaColinas2(solucao, matriz, vert, iter);

                printf("\nRepeticao %d: ", i);
                escrever_solucao(solucao, vert);
                printf("Custo final: %2d\n", custo);
                mbf += custo;
                if (i == 0 || bestCusto > custo) {
                    bestCusto = custo;
                    substitui(best, solucao, vert);
                }
            }

            printf("\n\nMBF: %f\n", mbf / i);
            printf("\nMelhor solucao encontrada");
            escrever_solucao(best, vert);
            printf("Custo final: %2d\n", bestCusto);

            free(matriz);
            free(solucao);
            free(best);
            break;
        case 3:
            // Trepa colinas probabilistico
            mostraASCII();
            fflush(stdin);
            printf("Introduza o nome do ficheiro: ");
            fgets(file, 100, stdin);
            file[strlen(file) - 1] = '\0';
            printf("\n");

            matriz = preenche_matriz(file, &vert, &iter);
            solucao = malloc(sizeof(int) * vert);
            best = malloc(sizeof(int) * vert);

            if (solucao == NULL || best == NULL) {
                printf("[ERRO] Ocorreu um problema ao alocar memória.");
                exit(1);
            }

            for (i = 0; i < runs; i++) {
                gerar_solinicial(solucao, vert);
                escrever_solucao(solucao, vert);

                custo = trepaColinasProb(solucao, matriz, vert, iter);

                printf("\nRepeticao %d: ", i);
                escrever_solucao(solucao, vert);
                printf("Custo final: %2d\n", custo);
                mbf += custo;
                if (i == 0 || bestCusto > custo) {
                    bestCusto = custo;
                    substitui(best, solucao, vert);
                }
            }

            printf("\n\nMBF: %f\n", mbf / i);
            printf("\nMelhor solucao encontrada");
            escrever_solucao(best, vert);
            printf("Custo final: %2d\n", bestCusto);

            free(matriz);
            free(solucao);
            free(best);
            break;
        case 4:
            break;
        case 0:
            printf("\nA sair do programa...\n");
            break;
        default:
            break;
    }

    return 0;
}