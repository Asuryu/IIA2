#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utilsTC.h"


/*offset da matriz de adjacencia*/
int offsetTC(int i, int j, int cols) {
	return i * cols + j;
}

// Gera a solucao inicial
// Parametros: solucao, numero de vertices
//na soluçao inicial temos de atribuir numeros de 0 a n_vert, nao repetidos
void gera_sol_inicialTC(int *sol, int v)
{
	int i;
        int *randLookUpTable = gera_random_lookup_tableTC(v);
	
        //atribui os rotulos aleatorios à soluçao
        for(i=0; i<v; i++)
            sol[i]=randLookUpTable[i];

      free(randLookUpTable);
}

// Escreve solucao
// Parametros: solucao e numero de vertices
void escreve_solTC(int *sol, int vert)
{
	int i;

	printf("\nSolucao: ");
	for(i=0; i<vert; i++)
        {
            printf("%d ", (sol[i]) );
        }
}

// copia vector b para a (tamanho n)
void substituiTC(int a[], int b[], int n)
{
    int i;
    for(i=0; i<n; i++)
        a[i]=b[i];
}

// Inicializa o gerador de numeros aleatorios
void init_randTC()
{
	srand((unsigned)time(NULL));
}

// Devolve valor inteiro aleatorio entre min e max
int random_l_hTC(int min, int max)
{
	return min + rand() % (max-min+1);
}

// Devolve um valor real aleatorio do intervalo [0, 1]
float rand_01TC()
{
	return ((float)rand())/RAND_MAX;
}

//gera uma lookup table de numeros aleatorio de 0 ate vert
//recebe o numero de vertices e devolve um array de numeros aleatorios
int * gera_random_lookup_tableTC(int vert){
    int * arrayAleatorio;
    int numTrocas= 2*vert;
    int aux1=0, aux2=0, temp;
    
    arrayAleatorio = malloc(vert * sizeof(vert));
    
    //coloca os rotulos ordenados para cada vertice
    for(int i = 0; i<vert; i++){
        arrayAleatorio[i] = i+1;
    }
    
    //troca os rotulos
    for(int i =0;i<numTrocas; i++){
        aux1= random_l_hTC(0,vert-1);
        aux2= random_l_hTC(0,vert-1);
        
        if(aux1 != aux2)
        {
            temp = arrayAleatorio[aux1];
            arrayAleatorio[aux1]=arrayAleatorio[aux2];
            arrayAleatorio[aux2] = temp;
        }
    }
   
    return arrayAleatorio;
}

int probEventoTC(float prob){
    return prob > ((float)rand()/RAND_MAX);
}
