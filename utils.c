#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "utils.h"
#include "evolutivo.h"

#define POPSIZE 10
#define PR 0.5
#define PM 0.5
#define T_SIZE 7
#define NUM_GENERATIONS 30

void mostraASCII()
{
    printf("\033[2J\033[1;1H");
    printf("██╗██╗ █████╗\n");
    printf("██║██║██╔══██╗\n");
    printf("██║██║███████║\n");
    printf("██║██║██╔══██║\n");
    printf("██║██║██║  ██║\n");
    printf("╚═╝╚═╝╚═╝  ╚═╝\n\n");
}

int random_int(int minimo, int maximo)
{
    int n;
    n = minimo + rand() % (maximo - minimo + 1);
    return n;
}

float random_float_01()
{
    int x;
    x = ((float)rand()) / RAND_MAX;
    return x;
}

int *preenche_matriz(char *file, int *v, int *numero_iteracoes)
{
    FILE *of;
    char buffer[100];
    int *matriz, *matriz2, *k;
    int i, j;

    of = fopen(file, "r");
    if (of == NULL)
    {
        printf("[ERRO] Ocorreu um problema ao abrir o ficheiro.");
        exit(1);
    }

    do
    {
        fscanf(of, "%s", buffer); // Lê as linhas de comentário
    } while (strcmp(buffer, "edge") != 0); // Enquanto não encontrar a palavra "edge"

    fscanf(of, " %d ", v); // Lê o número de vértices
    fscanf(of, "%d\n", numero_iteracoes); // Lê o número de arestas

    matriz = malloc(sizeof(int) * (*v) * (*v)); // Aloca memória para o grafo
    if (matriz == NULL)
    {
        printf("[ERRO] Ocorreu um problema ao alocar memória.");
        fclose(of);
        exit(1);
    }

    matriz2 = matriz; // Preservar matriz inicial

    // Inicializar a matriz com zeros
    for(int i = 0; i < *v; i++)
        for(int j = 0; j < *v; j++) // 
            matriz2[i*(*v)+j] = 0;
    k = matriz;

    // Lê as arestas
    while (fscanf(of, "e %d %d\n", &i, &j) == 2)
    {
        sscanf("1", "%d", k + calcIndice(i - 1, j - 1, *v));
    }

    printf("\n");
    // Mostra a matriz
    for (int i = 0; i < (*v); i++)
    {
        for (int j = 0; j < (*v); j++)
        {
            printf("%d ", *(matriz + (i - 1) * (*v) + (j - 1)));
        }
        printf("\n");
    }

    return matriz; // Retorna o grafo
}

void gerar_solinicial(int *sol, int v)
{
    int x;

    for (int i = 0; i < v; i++)
    {
        sol[i] = 0;
    }

    // Preenche a solução inicial
    for (int i = 0; i < (v / 2); i++)
    {
        do
        {
            x = random_int(0, v - 1);
        } while (sol[x] != 0);
        sol[x] = 1;
    }
}

void escrever_solucao(int *sol, int v)
{
    printf("\nConjunto A: ");
    for (int i = 0; i < v; i++)
    {
        if (sol[i] == 0)
        {
            printf("%2d  ", i);
        }
    }

    printf("\nConjunto B: ");
    for (int i = 0; i < v; i++)
    {
        if (sol[i] == 1)
        {
            printf("%2d  ", i);
        }
    }

    printf("\n");
}

void substitui(int a[], int b[], int n)
{
    for (int i = 0; i < n; i++)
    {
        a[i] = b[i];
    }
}

int probEvento(float prob)
{
    return prob > ((float)rand() / RAND_MAX);
}

int calcIndice(int i, int j, int cols)
{
    return i * cols + j;
}

int **init_dados(char *nome, int *vertices, int *arestas)
{

    FILE *of = fopen(nome, "rt");
    int **p = NULL;
    char buffer[100];
    int i;
    if (!of)
    {
        fprintf(stderr, "[ERRO] Ocorreu um erro ao abrir o ficheiro\n");
        exit(0);
    }

    do
    {
        fscanf(of, "%s", buffer);
    } while (strcmp(buffer, "edge") != 0);

    fscanf(of, " %d ", vertices);
    fscanf(of, "%d\n", arestas);

    p = malloc(sizeof(int) * (*arestas));
    if (!p)
    {
        printf("[ERRO] Ocorreu um erro ao alocar memória\n");
        fclose(of);
        exit(0);
    }
    for (i = 0; i < *arestas; i++)
    {
        p[i] = malloc(sizeof(int) * 2);
        if (!p[i])
        {
            printf("Erro na alocacao de memoria \n");
            fclose(of);
            exit(0);
        }
    }
    for (i = 0; i < *arestas; i++)
    {
        if (fscanf(of, "e %d %d\n", &p[i][0], &p[i][1]) != 2)
        {
            free(p);
            fclose(of);
            exit(0);
        }
    }

    fclose(of);
    return p;
}

info init_data(int arestas, int vertices)
{
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

void gera_sol_inicial(int *sol, int v)
{
    int aux = v;
    int a[v];
    int x, i;
    for (i = 0; i < v; i++)
        a[i] = i + 1;
    for (i = 0; i < v; i++)
    {
        x = random_int(0, aux - 1);
        sol[i] = a[x];
        a[x] = a[aux - 1];
        aux--;
    }
}

pchrom init_pop(info d)
{
    int i;
    pchrom indiv;

    indiv = malloc(sizeof(chrom) * d.pop);
    if (!indiv)
    {
        printf("[ERRO] Ocorreu um erro ao alocar memória\n");
        exit(1);
    }
    for (i = 0; i < d.pop; i++)
    {
        indiv[i].p = malloc(sizeof(int) * d.vertices);
        if (!indiv[i].p)
        {
            printf("[ERRO] Ocorreu um erro ao alocar memória\n");
            exit(2);
        }
        gera_sol_inicial(indiv[i].p, d.vertices);
    }
    return indiv;
}

chrom get_best(pchrom pop, info d, chrom best)
{
    int i;
    for (i = 0; i < d.pop; i++)
    {
        if (best.fitness > pop[i].fitness)
            best = pop[i];
    }
    return best;
}

void write_best(chrom x, info d)
{
    int i;
    printf("\nBest individual: %d\n", x.fitness);
    for (i = 0; i < d.vertices; i++)
        printf("%d ", x.p[i]);
    puts("\n");
}
