#include <stdio.h>
#include <stdlib.h>

#include "pesquisaLocal.h"
#include "engine.h"
#include "utils.h"

void gerar_vizinho(int *sol, int *vizinho, int vertices){
    int p01;

    for(int i = 0; i < vertices;i ++){
        vizinho[i] = sol[i];
    }

    p01 = random_int(0, vertices-1);

    vizinho[p01] = !vizinho[p01];
}

void gerar_vizinho2(int *sol, int *vizinho, int vertices){
    int p01, p02;

    for(int i = 0; i < vertices; i++){
        vizinho[i] = sol[i];
    }

    p01 = random_int(0, vertices-1);

    vizinho[p01] = !vizinho[p01];

    do{
        p02 = random_int(0, vertices-1);
    } while(p01 == p02);

    vizinho[p02] = !vizinho[p02];
}

int trepaColinas(int sol[], int *matriz, int vertices, int iter){
    int *novaSolucao, custo, custoVizinho;

    novaSolucao = malloc(sizeof(int)*vertices);
    if(novaSolucao == NULL){
        printf("Erro na alocacao de memoria");
        exit(1);
    }

    custo = calcular_custo(sol, matriz, vertices);
    for(int i=0; i<iter; i++){

        gerar_vizinho2(sol, novaSolucao, vertices);
        
        custoVizinho = calcular_custo(novaSolucao, matriz, vertices);

        if(custoVizinho >= custo){
            substitui(sol, novaSolucao, vertices);
            custo = custoVizinho;
        }
    }

    free(novaSolucao);
    return custo;
}

int trepaColinas2(int sol[], int *matriz, int vertices, int iter){
    int *novaSolucao, custo, custoVizinho;

    novaSolucao = malloc(sizeof(int)*vertices);
    if(novaSolucao == NULL){
        printf("Erro na alocacao de memoria");
        exit(1);
    }

    custo = calcular_custo(sol, matriz, vertices);
    for(int i=0; i<iter; i++){

        gerar_vizinho(sol, novaSolucao, vertices);
        
        custoVizinho = calcular_custo(novaSolucao, matriz, vertices);

        if(custoVizinho >= custo){
            substitui(sol, novaSolucao, vertices);
            custo = custoVizinho;
        }
    }

    free(novaSolucao);
    return custo;
}

int trepaColinasProb(int sol[], int *matriz, int vertices, int iter) {
    int *novaSolucao, custo, custoVizinho;

    novaSolucao = malloc(sizeof(int) * vertices);
    if (novaSolucao == NULL) {
        printf("[ERRO] Ocorreu um problema ao alocar memória.");
        exit(1);
    }
    // Avaliar solução inicial
    custo = calcular_custo(sol, matriz, vertices);
    for (int i = 0; i < iter; i++) {
        // Gerar vizinho
        gerar_vizinho(sol, novaSolucao, vertices);
        // Avaliar vizinho
        custoVizinho = calcular_custo(novaSolucao, matriz, vertices);

        // Aceitar vizinho se o custo aumentar (problema de maximização)
        if (custoVizinho >= custo) {
            substitui(sol, novaSolucao, vertices);
            custo = custoVizinho;
        } else {
            if (random_float_01() <= 0.01) {
                substitui(sol, novaSolucao, vertices);
                custo = custoVizinho;
            }
        }
    }
    free(novaSolucao);
    return custo;
}