#include "engine.h"
#include "utils.h"
#include "evolutivo.h"
#include <stdlib.h>
#include <stdio.h>

int calcula_fit(int a[], int *mat, int vert)
{
	int total=0;
	int i, j;

	for(i=0; i<vert; i++)
		if(a[i]==0)
		{
			for(j=0; j<vert;j++)
				if(a[j]==1 && *(mat+i*vert+j)==1)
				    total++;
		}
	return total;
}




// int eval_fit(int sol[], int **mat, int arestas) {
//     int total = 0, aux,i;
// 	printf("^^^^%d^^^^^", arestas);
//     for ( i = 0; i < arestas; i++) {
//         aux = abs(sol[mat[i][0] - 1] - sol[mat[i][1] - 1]);
// 		printf("abs");
// 		fflush(stdout);
//         if (aux > total)//se o custo calculado anteriormente for maior que o total, iguala-se a esse
//             total = aux;
//     }
//     return total;
// }


// void evaluate(pchrom pop, info d, int **mat) {
// 	int i;
// 	printf("||%d||", d.pop);
// 	fflush(stdout);
//     for ( i = 0; i < d.pop; i++){
//         pop[i].fitness = eval_fit(pop[i].p, mat, d.aresta); //Calcula o custo de cada solucao da populacao
// 		printf("fixe!!!!!");
// 		fflush(stdout);
// 	}
// }

// Calcula a qualidade de uma solu��o
// Par�metros de entrada: solu��o (sol), capacidade da mochila (d), matriz com dados do problema (mat) e numero de objectos (v)
// Par�metros de sa�da: qualidade da solu��o (se a capacidade for excedida devolve 0)
float eval_fit(int sol[], info d, int **mat)
{
	int i;
	float sum_weight, sum_profit;
	do
	{
		sum_weight = sum_profit = 0;
		// Percorre todos os objectos
		for (i = 0; i < d.tsize; i++)
		{
			// Verifica se o objecto i esta na mochila
			if (sol[i] == 1)
			{
				// Actualiza o peso total
				sum_weight += mat[i][0];
				// Actualiza o lucro total
				sum_profit += mat[i][1];
			}
		}
		if (sum_weight > d.tsize)
		{
			// Solucao inv�lida
			do
			{
				i = random_int(0, d.numGenerations - 1);
			} while (sol[i] == 0);
			sol[i] = 0;
		}
	} while (sum_weight > d.tsize);

	//*v = 1;
	return sum_profit;
}

// Avaliacao da popula��o
// Par�metros de entrada: populacao (pop), estrutura com parametros (d) e matriz com dados do problema (mat)
// Par�metros de sa�da: Preenche pop com os valores de fitness e de validade para cada solu��o
void evaluate(pchrom pop, info d, int **mat)
{
	int i;

	for (i = 0; i < d.pop; i++)
		pop[i].fitness = eval_fit(pop[i].p, d, mat);
}



