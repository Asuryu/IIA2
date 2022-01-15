/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "algoritmoTC.h"
#include "utilsTC.h"
void TrepaColinasAutomatico(int vert, int num_iter, int *grafo, int *sol)
{
    int      k, runs, custo,best_custo;
    int     *best;
	//float   mbf = 0.0;

	runs = 1;
	
           // mbf=0.0;
	if(runs <= 0)
		return ;
	best = malloc(sizeof(int)*vert);
        
	if(sol == NULL || best == NULL)
	{
		printf("Erro na alocacao de memoria");
		exit(1);
	}
	
        custo = trepa_colinas(sol, grafo, vert, num_iter);

        if(k==0 || best_custo > custo)
        {
                best_custo = custo;
                substituiTC(best, sol, vert);
        }
        
	free(best);
        return;
}
