#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include "algoritmo.h"
#include "funcao.h"
#include "utils.h"

#define N_RUNS_DEFAULT 10

int main(int argc, char** argv){
    int vertic, aresta, k, i,j,n;
    int **le_mat;
    float mbf = 0;
    char nome_fich[100];
    info param;
    pchrom pop = NULL, parents = NULL;
    chrom best_run, best_ever;
    int gen_atual;
    printf("ALGORITMO EVOLUTIVO!\n");
    printf("Ficheiros Disponiveis: \n");
    printf("bcspwr01.txt\n");
    printf("bcspwr02.txt\n");
    printf("bcspwr03.txt\n");
    printf("inst_teste.txt\n");
    printf("\nIntroduza o nome de um dos ficheiros em cima: ");
    gets(nome_fich);
    int runs = N_RUNS_DEFAULT;
    if (runs <= 0)
        return 0;
    init_rand();
    le_mat = init_dados(nome_fich, &vertic, &aresta);
    param = init_data(aresta, vertic);
    for (k = 0; k < runs; k++) {
                    printf("Repeticao %d\n", k + 1);
                    pop = init_pop(param);
                    evaluate(pop, param, le_mat);
                    best_run = pop[0];
                    best_run = get_best(pop, param, best_run);
                    parents = malloc(sizeof (chrom) * param.pop);
                    if (!parents) {
                        fprintf(stderr, "Erro na alocacao de memoria. \n");
                        exit(1);
                    }
                    gen_atual = 1;
                    while (gen_atual <= param.numGenerations) {
                        tournament(pop, param, parents);
                        genetic_operators(parents, param, pop);
                        evaluate(pop, param, le_mat);
                        best_run = get_best(pop, param, best_run);
                        gen_atual++;
                    }
                    write_best(best_run, param);
                    mbf += best_run.fitness;
                    if (k == 0 || best_run.fitness < best_ever.fitness)
                        best_ever = best_run;
                    free(parents);
                    for( j = 0; j < param.pop; j++){
                        free(pop[j].p);
                        free(parents[j].p);
                    }
                    free(pop);
                    free(parents);
                }
                printf("\n\nMBF: %f\n", mbf / k);
                printf("\nMelhor solucao encontrada");
                write_best(best_ever, param);
                mbf = 0;
                for ( j = 0; j < aresta; j++)
                    free(le_mat[j]);
                free(best_ever.p);
                free(best_run.p);

    return(EXIT_SUCCESS);
}
