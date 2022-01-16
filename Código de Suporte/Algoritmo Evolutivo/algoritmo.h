#ifndef ALGORITMO_H
#define ALGORITMO_H
#define MAX_OBJ 500

typedef struct{
    int pop;   //populacao
    int vertices;  //numer de vertices
    int aresta;   //numero de ligacoes (arestas)
    float pm;   //probabilidade da mutacao
    float pr; //probabilidade de recombinacao
    int  tsize; //tamanho do torneio para a selecao do pai da proxima geracao
    float ro;  //constante para avaliacao com penalizacao
    int numGenerations; //numero de geracoes
} info;

typedef struct{
    int *p;        //solucao
    int fitness; //valor da qualidade da solucao
} chrom, *pchrom;

void tournament(pchrom pop, info d, pchrom parents);
void genetic_operators(pchrom parents, info d, pchrom offspring);
void crossover(pchrom parents, info d, pchrom offspring);
void mutation(pchrom offspring, info d);
#endif
