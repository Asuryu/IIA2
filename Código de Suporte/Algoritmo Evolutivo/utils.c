#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utils.h"
#include "algoritmo.h"
#define POPSIZE 10
#define PR 0.5
#define PM 0.5
#define T_SIZE 7
#define NUM_GENERATIONS 30


int** init_dados(char *nome, int *vertices, int *arestas) {

    FILE *f = fopen(nome, "rt");
    int **p = NULL;
    char a[100];
    int i;
    if (!f) {
        fprintf(stderr, "Erro na abertura do ficheiro");
        exit(0);
    }
    fscanf(f, "%99[^\n]", a);
    if (fscanf(f, " %d %d", vertices, arestas) != 2) {
        fprintf(stderr, "Erro na leitura de parametros\n");
        fclose(f);
        exit(1);
    }
    p = malloc(sizeof (int) * (*arestas));
    if (!p) {
        fprintf(stderr, "Erro na alocacao de memoria");
        fclose(f);
        exit(2);
    }
    for ( i = 0; i < *arestas; i++) { //ALOCA ESPA�O PARA A MATRIZ
        p[i] = malloc(sizeof (int) * 2);
        if (!p[i]) {
            fprintf(stderr, "Erro na alocacao de memoria \n");
            fclose(f);
            exit(3);
        }
    }
    for ( i = 0; i < *arestas; i++) {
        if (fscanf(f, " %d %d", &p[i][0], &p[i][1]) != 2) {
            fprintf(stderr, "Erro na leitura de parametros. \n");
            free(p);
            fclose(f);
            exit(4);
        }
    }
    fclose(f);
    return p;
}

info init_data(int arestas, int vertices) {
    info x;
    x.vertices = vertices;
    x.aresta = arestas;
    x.pop = POPSIZE;
    x.pm = PM;
    x.pr = PR;
    x.tsize = T_SIZE;
    x.numGenerations = NUM_GENERATIONS;
    return x;
}

void gera_sol_inicial(int *sol, int v) {
    int aux = v;
    int a[v];
    int x,i;
    for ( i = 0; i < v; i++)
        a[i] = i + 1;
    for ( i = 0; i < v; i++) {
        x = random_l_h(0, aux - 1);
        sol[i] = a[x];
        a[x] = a[aux - 1];
        aux--;
    }
}

void init_rand() {
    srand((unsigned) time(NULL));
}

int random_l_h(int min, int max) {
    return min + rand() % (max - min + 1);
}

float rand_01() {
    return ((float) rand()) / RAND_MAX;
}


pchrom init_pop(info d){
    int i;
    pchrom indiv;

    indiv = malloc(sizeof (chrom) * d.pop);
    if (!indiv) {
        printf("Erro na alocacao de memoria. \n");
        exit(1);
    }
    for (i = 0; i < d.pop; i++) {
        indiv[i].p = malloc(sizeof (int) * d.vertices);
        if (!indiv[i].p) {
            fprintf(stderr, "Erro na alocacao de memoria. \n");
            exit(2);
        }
        gera_sol_inicial(indiv[i].p, d.vertices);
    }
    return indiv;
}

chrom get_best(pchrom pop, info d, chrom best) {
    int i;
    for ( i = 0; i < d.pop; i++) {
        if (best.fitness > pop[i].fitness)
            best = pop[i];
    }
    return best;
}

void write_best(chrom x, info d) {
    int i;
    printf("\nBest individual: %d\n", x.fitness);
    for (i = 0; i < d.vertices; i++)
        printf("%d ", x.p[i]);
    puts("\n");
}
