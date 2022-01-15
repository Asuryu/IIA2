#include "engine.h"
#include "utils.h"
#include <stdlib.h>

int calcula_fit(int a[], int *mat, int vert)
{
	int custo=0;
        int aux=0;
        int offsetv=0;
        //o custo da solucao equivale a diferenca entre duas ligacoes
	for(int i=0; i<vert; i++)
	{
            for(int j= 0 ; j < vert ; j++)
            {
                offsetv = offset(i,j,vert);
                if(mat[offsetv] == 1)
                {
                    aux = abs(a[i]-a[j]);
                    if(aux > custo)
                        custo=aux;
                }  
            }
        }
     
	return custo;
}