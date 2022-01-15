#ifndef ALGORITMO_H
#define ALGORITMO_H


// EStrutura para armazenar parametros
struct info
{
    // Tamanho da popula��o
    int     popsize;
    // Probabilidade de muta��o
    float   pm;
    // Probabilidade de recombina��o
    float   pr;
    // Tamanho do torneio para sele��o do pai da pr�xima gera��o
	int     tsize;
	// Constante para avalia��o com penaliza��o
	float   ro;
	// N�mero de objetos que se podem colocar na mochila
    int     numGenes;
	// N�mero de gera��es
    int     numGenerations;
};

// Individuo (solu��o)
typedef struct individual chrom, *pchrom;

struct individual
{
   

    // Valor da qualidade da solu��o
    float   fitness;
    
    int valido;
        
    int p[1000];
};

void tournament(pchrom pop, struct info d, pchrom parents);

void genetic_operators(pchrom parents, struct info d, pchrom offspring);

void crossover(pchrom parents, struct info d, pchrom offspring);

void mutation(pchrom offspring,struct info d);

#endif	// ALGORITMO_H

