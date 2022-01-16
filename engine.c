#include "engine.h"
#include "utils.h"
#include "evolutivo.h"
#include <stdlib.h>
#include <stdio.h>

int calcula_fit(int a[], int *mat, int vert)
{
	int total = 0;
	int i, j;

	for (i = 0; i < vert; i++)
		if (a[i] == 0)
		{
			for (j = 0; j < vert; j++)
				if (a[j] == 1 && *(mat + i * vert + j) == 1)
					total++;
		}
	return total;
}

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

void evaluate(pchrom pop, info d, int **mat)
{
	int i;

	for (i = 0; i < d.pop; i++)
		pop[i].fitness = eval_fit(pop[i].p, d, mat);
}
