#include <stdio.h>
#include <stdlib.h>

#include "pesquisaLocal.h"
#include "engine.h"
#include "utils.h"

void gerar_vizinho(int a[], int b[], int n)
{
    int i, p1, p2, temp;

    for (i = 0; i < n; i++)
        b[i] = a[i];

    p1 = random_int(0, n - 1);

    p2 = random_int(0, n - 1);

    // Troca
    temp = b[p1];
    b[p1] = b[p2];
    b[p2] = temp;
}

int trepaColinas(int sol[], int *mat, int vert, int num_iter)
{
    int *nova_sol, custo, custo_viz, i;

    nova_sol = malloc(sizeof(int) * vert);
    if (nova_sol == NULL)
    {
        printf("Erro na alocacao de memoria");
        exit(1);
    }
    // Avalia solucao inicial
    custo = calcula_fit(sol, mat, vert);
    for (i = 0; i < num_iter; i++)
    {

        // Gera vizinho
        gerar_vizinho(sol, nova_sol, vert);
        // Avalia vizinho
        custo_viz = calcula_fit(nova_sol, mat, vert);

        if (custo_viz > custo)
        {
            substitui(sol, nova_sol, vert);
            custo = custo_viz;
            break;
        }
    }
    free(nova_sol);

    return custo;
}
int trepaColinasProb(int sol[], int *mat, int vert, int num_iter)
{
    int *nova_sol, custo, custo_viz, i;
    float probs = 0.05;
    nova_sol = malloc(sizeof(int) * vert);
    if (nova_sol == NULL)
    {
        printf("Erro na alocacao de memoria");
        exit(1);
    }
    // Avalia solucao inicial
    custo = calcula_fit(sol, mat, vert);
    for (i = 0; i < num_iter; i++)
    {

        // Gera vizinho
        gerar_vizinho(sol, nova_sol, vert);
        // Avalia vizinho
        custo_viz = calcula_fit(nova_sol, mat, vert);
        if (custo_viz > custo)
        {
            substitui(sol, nova_sol, vert);
            custo = custo_viz;
        }
        else if (probEvento(probs))
        {
            substitui(sol, nova_sol, vert);
            custo = custo_viz;
        }
    }
    free(nova_sol);

    return custo;
}