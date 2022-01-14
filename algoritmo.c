#include <stdio.h>
#include <stdlib.h>

#include "algoritmo.h"
#include "funcao.h"
#include "utils.h"

void gerar_vizinho(int *solucao, int *vizinho, int vertices){
    int p01;

    for(int i=0;i<vertices;i++){ // solução vizinha = solução atual
        vizinho[i]=solucao[i];
    }

    p01 = random(0,vertices-1);

    vizinho[p01] = !vizinho[p01];
}

void gerar_vizinho2(int *solucao, int *vizinho, int vertices){
    int p01,p02;

    for(int i=0;i<vertices;i++){ // solução vizinha = solução atual
        vizinho[i]=solucao[i];
    }

    p01 = random(0,vertices-1);

    vizinho[p01] = !vizinho[p01];

    do{
        p02 = random(0,vertices-1);
    }while(p01 == p02);

    vizinho[p02] = !vizinho[p02];
}

// ====================== TREPA COLINAS ====================================
int trepaColinas(int solucao[], int *matriz, int vertices, int nIteracoes){
    int *novaSolucao, custo, custoVizinho;

    novaSolucao = malloc(sizeof(int)*vertices);
    if(novaSolucao == NULL){
        printf("Erro na alocacao de memoria");
        exit(1);
    }
    // Avaliar solução inicial
    custo = calcular_custo(solucao, matriz, vertices);
    for(int i=0; i<nIteracoes; i++){
        // Gerar vizinho
        gerar_vizinho2(solucao, novaSolucao, vertices);
        // Avaliar vizinho
        custoVizinho = calcular_custo(novaSolucao, matriz, vertices);
        // Aceitar vizinho se o custo aumentar (problema de maximização)
        if(custoVizinho >= custo){
            substitui(solucao, novaSolucao, vertices);
            custo = custoVizinho;
        }
    }

    free(novaSolucao);
    return custo;
}

//Probabilistico
int trepaColinasProb(int solucao[], int *matriz, int vertices, int nIteracoes) {
    int *novaSolucao, custo, custoVizinho;

    novaSolucao = malloc(sizeof(int) * vertices);
    if (novaSolucao == NULL) {
        printf("Erro na alocacao de memoria");
        exit(1);
    }
    // Avaliar solução inicial
    custo = calcular_custo(solucao, matriz, vertices);
    for (int i = 0; i < nIteracoes; i++) {
        // Gerar vizinho
        gerar_vizinho(solucao, novaSolucao, vertices);
        // Avaliar vizinho
        custoVizinho = calcular_custo(novaSolucao, matriz, vertices);

        // Aceitar vizinho se o custo aumentar (problema de maximização)
        if (custoVizinho >= custo) {
            substitui(solucao, novaSolucao, vertices);
            custo = custoVizinho;
        } else {
            if (random_0e1() <= 0.01) {
                substitui(solucao, novaSolucao, vertices);
                custo = custoVizinho;
            }
        }
    }
}
// ================================================================================

