#include <stdio.h>
#include <stdlib.h>
#include "algoritmo.h"
#include "funcao.h"
#include "utils.h"

// Gera um vizinho
// Parametros: solucao actual, vizinho, numero de vertices
//swap two vertices
void gera_vizinho(int a[], int b[], int n)
{
    int i, p1, p2, temp;
    int point=0;

    int vizinhanca=0;
    for(i=0; i<n; i++)
        b[i]=a[i];


        p1=random_l_h(0, n-1);
        
        
        p2=random_l_h(0, n-1);
      
        // Troca
        temp = b[p1];
        b[p1] = b[p2];
        b[p2] = temp;
  
}

// Trepa colinas 
// Parametros: solucao, matriz de adjacencias, numero de vertices e numero de iteracoes
// Devolve o custo da melhor solucao encontrada
int trepa_colinas(int sol[], int *mat, int vert, int num_iter)
{
    int *nova_sol, custo, custo_viz, i;


	nova_sol = malloc(sizeof(int)*vert);
    if(nova_sol == NULL)
    {
        printf("Erro na alocacao de memoria");
        exit(1);
    }
	// Avalia solucao inicial
    custo = calcula_fit(sol, mat, vert);
    for(i=0; i<num_iter; i++)
    {
      
		// Gera vizinho
		gera_vizinho(sol, nova_sol, vert);
		// Avalia vizinho
		custo_viz = calcula_fit(nova_sol, mat, vert);
		// Aceita vizinho se o custo diminuir (problema de minimizacao)
        if(custo_viz < custo)
        {
			substitui(sol, nova_sol, vert);
			custo = custo_viz;
            break;
        }
    }
    free(nova_sol);

    return custo;
}


int trepa_colinas_prob(int sol[], int *mat, int vert, int num_iter)
{
    int *nova_sol, custo, custo_viz, i;
    float probs= 0.0005;// {0.05, 0.1,0.3,0.5,0.7,0.9};
    static int p =0;
	nova_sol = malloc(sizeof(int)*vert);
    if(nova_sol == NULL)
    {
        printf("Erro na alocacao de memoria");
        exit(1);
    }
	// Avalia solucao inicial
    custo = calcula_fit(sol, mat, vert);
    for(i=0; i<num_iter; i++)
    {
      
		// Gera vizinho
		gera_vizinho(sol, nova_sol, vert);
		// Avalia vizinho
		custo_viz = calcula_fit(nova_sol, mat, vert);
		// Aceita vizinho se o custo diminuir (problema de minimizacao)
                if(custo_viz < custo)
                {
       
			substitui(sol, nova_sol, vert);
			custo = custo_viz;
                }
                else if(probEvento(probs))
                {
			substitui(sol, nova_sol, vert);
			custo = custo_viz;
                }
    }
    free(nova_sol);

    return custo;
}