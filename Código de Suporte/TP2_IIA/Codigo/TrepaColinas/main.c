#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "algoritmo.h"
#include "utils.h"


#define DEFAULT_RUNS 30
int trepaC();
int prob();
int main(){
     int what;
    printf("Escolhe o metodo 1-Trepa Colinas normal\t2-Trepa Colinas Probabilistico\n>");
    scanf("%d", &what);
   
    if(what==1)trepaC();
    if(what ==2) prob();
    
    return 0;
}

//main first choice
int trepaC()
{
    char    nome_fich[] = "will199.txt";
    int     vert, num_iter, k, runs, custo,best_custo;
    int     *grafo, *sol,*best;
	float   mbf = 0.0;
        int it[3]={100, 1000, 5000};
        
        for(int j =0; j< 3;j++){
        
	runs = DEFAULT_RUNS;

            mbf=0.0;
	if(runs <= 0)
		return 0;
	init_rand();
    // Preenche matriz de adjacencias
        grafo = init_dados(nome_fich, &vert, &num_iter);
	sol = malloc(sizeof(int)*vert);   
       
	best = malloc(sizeof(int)*vert);
     
        num_iter=it[j];
        
	if(sol == NULL || best == NULL)
	{
		printf("Erro na alocacao de memoria");
		exit(1);
	}
	for(k=0; k<runs; k++)
	{
		// Gerar solucao inicial
		gera_sol_inicial(sol, vert);
             
		//escreve_sol(sol, vert);
		// Trepa colinas
		custo = trepa_colinas(sol, grafo, vert, num_iter);
                
		// Escreve resultados da repeticao k
		//printf("\nRepeticao FC %d:", k);
		//escreve_sol(sol, vert);
                
              
                
		//printf("Custo final FC: %2d\n", custo);
               
		mbf += custo;
               
		if(k==0 || best_custo > custo)
		{
			best_custo = custo;
			substitui(best, sol, vert);
		}
                
    }
	// Escreve eresultados globais
	printf("\n\nMBF FC: %f\n", mbf/k);
	printf("\nMelhor solucao encontrada");
	escreve_sol(best, vert);
	printf("\n%d iter.  Custo final FC: %2d\n",it[j], best_custo);
       
	
        free(grafo);
        free(sol);
	free(best);
        }
    return 0;
}

//main probabilistico
int prob(){
     char  *  nome_fich="will199.txt";
    int     vert, num_iter, k, runs, custoProb, best_custoProb;
    int     *grafo, *sol_prob, *best_prob;
	float    mbf_prob =0.0;

	runs = DEFAULT_RUNS;
	
        int it[2]={100, 5000};
        for(int j =0; j< 2;j++){
           
            mbf_prob=0.0;
	if(runs <= 0)
		return 0;
	init_rand();
    // Preenche matriz de adjacencias
        grafo = init_dados(nome_fich, &vert, &num_iter);
	  
        sol_prob = malloc(sizeof(int)*vert);
	
        best_prob = malloc(sizeof(int)*vert);
        
	if(sol_prob == NULL || best_prob == NULL)
	{
		printf("Erro na alocacao de memoria");
		exit(1);
	}
              num_iter=it[j];
	for(k=0; k<runs; k++)
	{
		// Gerar solucao inicial
		
                gera_sol_inicial(sol_prob, vert);
		//escreve_sol(sol, vert);
		// Trepa colinas
	
                custoProb = trepa_colinas_prob(sol_prob, grafo, vert, num_iter);
		// Escreve resultados da repeticao k
                
              //  printf("\nRepeticao Prob %d:", k);
		//escreve_sol(sol_prob, vert);
                
                
		//printf("Custo final Prob: %2d\n", custoProb);
		
                mbf_prob += custoProb;
		
                if(k==0 || best_custoProb > custoProb)
		{
			best_custoProb = custoProb;
			substitui(best_prob, sol_prob, vert);
		}
    }
	// Escreve eresultados globais

        
        printf("\n\nMBF Prob: %f\n", mbf_prob/k);
	//printf("\nMelhor solucao encontrada");
	//escreve_sol(best_prob, vert);
	printf("Custo final Prob: %2d\n", best_custoProb);
	
        free(grafo);
        free(sol_prob);
	free(best_prob); Sleep(1000);
        
        }

//	Sleep(10000);
    return 0;
}