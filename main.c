#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "utils.h"
#include "engine.h"
#include "pesquisaLocal.h"
#include "evolutivo.h"


void tColinas();
void tColinasProb();
void torneioBinario();

int main() {
    int escolha;
    srand((unsigned)time(NULL));
    mostraASCII();
    printf("\n1 - Trepa Colinas (com vizinhança 1)");
    printf("\n2 - Trepa Colinas (probabilístico)");
    printf("\n3 - Torneio Binário");
    printf("\n0 - Sair\n\nEscolha: ");
    scanf("%d", &escolha);
    
    if(escolha == 1) tColinas();
    else if(escolha == 2) tColinasProb();
    else if(escolha == 3) torneioBinario();

    return 0;
}


void tColinas(){
    char file[100];
    int runs = 10;
    int iter, vert, custo, bestCusto, escolha;
    int *matriz, *solucao, *best;
    float mbf = 0.0;
    int i;

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
    gerar_solinicial(solucao, vert);
    escrever_solucao(solucao, vert);
    for (i = 0; i < runs; i++) {

        custo = trepaColinas(solucao, matriz, vert, iter);

        printf("\nRepeticao %d: ", i);
        escrever_solucao(solucao, vert);
        printf("Custo final: %2d\n", custo);
        mbf += custo;
        if (i == 0 || bestCusto <= custo) {
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
}

void tColinasProb(){
    char file[100];
    int runs = 10;
    int iter, vert, custo, bestCusto, escolha;
    int *matriz, *solucao, *best;
    float mbf = 0.0;
    int i;

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
        if (i == 0 || bestCusto <= custo) {
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
}

void torneioBinario(){
    
}