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
    int iter, vert, custo, bestCusto;
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
        custo = trepaColinas(solucao, matriz, vert, iter);

        // printf("\nRepeticao %d: ", i);
        // escrever_solucao(solucao, vert);
        // printf("Custo final: %2d\n", custo);

        mbf += custo;
        if (i == 0 || bestCusto < custo) {
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
    int iter, vert, custo, bestCusto;
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
        //escrever_solucao(solucao, vert);

        custo = trepaColinasProb(solucao, matriz, vert, iter);

        // printf("\nRepeticao %d: ", i);
        // escrever_solucao(solucao, vert);
        // printf("Custo final: %2d\n", custo);

        mbf += custo;
        if (i == 0 || bestCusto < custo) {
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
    char file[100];
    int runs = 10;
    int iter, vert, gen_atual;
    int **mat;
    float mbf = 0;
    info param;
    pchrom pop = NULL, parents = NULL;
    chrom best_run, best_ever;
    int i;

    mostraASCII();
    fflush(stdin);
    printf("Introduza o nome do ficheiro: ");
    fgets(file, 100, stdin);
    file[strlen(file) - 1] = '\0';
    printf("\n");

    mat = init_dados(file, &vert, &iter);
    param = init_data(vert, iter);
    
    for(i = 0; i < runs; i++){
        printf("Repetição %d\n", i);
        pop = init_pop(param);
        evaluate(pop, param, mat);
        best_run = pop[0];
        best_run = get_best(pop, param, best_run);
        parents = malloc(sizeof(chrom) * param.pop);
        if(parents == NULL){
            printf("[ERRO] Ocorreu um problema ao alocar memória.");
            exit(1);
        }
        gen_atual = 1;
        while(gen_atual <= param.numGenerations){
            tournament(pop, param, parents);
            genetic_operators(parents, param, pop);
            evaluate(pop, param, mat);
            best_run = get_best(pop, param, best_run);
            gen_atual++;
        }
        write_best(best_run, param);
        mbf += best_run.fitness;
        if(i == 0 || best_ever.fitness < best_run.fitness){
            best_ever = best_run;
        }
        free(parents);
        for(int j = 0; j < param.pop; j++){
            free(pop[j].p);
            free(parents[j].p);
        }
        free(pop);
        free(parents);
    }
    printf("\n\nMBF: %f\n", mbf / runs);
    printf("\nMelhor solucao encontrada");
    write_best(best_ever, param);
    mbf = 0;
    for(int j = 0; j < iter; j++){
        free(mat[j]);
    }
    free(best_ever.p);
    free(best_run.p);

}