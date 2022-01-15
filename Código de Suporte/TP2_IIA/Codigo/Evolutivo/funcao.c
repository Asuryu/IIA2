#define _CRT_SECURE_NO_WARNINGS 1
#include "algoritmo.h"
#include "funcao.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void printSol(int a[], int vert);

// Calcula a qualidade de uma solu��o
// Par�metros de sa�da: qualidade da solu��o
float eval_individual(int a[], int *mat, int vert,int *v)
{
        int custo=0;
        int aux=0;
        int offsetv=0;
	int i=0, j=0;
        int * checkVal;
        //o custo da solucao equivale a diferenca entre duas ligacoes
        static int number =0;
         static int number2 =0;
        checkVal = malloc(sizeof(int) * vert);
        for(int k=0; k< vert; k++){
            checkVal[k] =0;
        }
        
	for(i=0; i<vert; i++)
	{
            for(j= 0 ; j < vert ; j++)
            {
                offsetv = offset(i,j,vert);
                if(*(mat + offsetv )== 1)
                {
                    aux = abs(a[i]-a[j]);
                    if(aux > custo)
                        custo=aux;
                }
                
            }
        }
   
        
        for(int k=0; k< vert; k++){
            checkVal[a[k]-1] += 1;
        }

        //check for repetitions
         aux=1;
        for(int k =0 ; k<vert ; k++){
            if(checkVal[k] != 1)
            {
                *v = 0;
                aux =0;
              
                return 100000;
            }
        }
       *v = 1;
        
	return custo;	
}

// Avaliacao da popula��o
// Par�metros de entrada: populacao (pop), estrutura com parametros (d) e matriz com dados do problema (mat)
// Par�metros de sa�da: Preenche pop com os valores de fitness e de validade para cada solu��o
void evaluate(pchrom pop, struct info d, int *mat)
{
	int i;
        
	for (i=0; i<d.popsize; i++)
		pop[i].fitness = eval_individual(pop[i].p, mat, d.numGenes,&pop[i].valido );

}

void printSol(int a[], int vert)
{
    int total=0;
  for(int i = 0; i < vert ; i++)
  {
      printf("%d ", a[i]);
      total +=a[i];
  }
  printf(" ::: %d ", total);
  
  printf("\n");

}
