#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utils.h"

#define N_ITER 100

// Leitura do ficheiro de input
// Recebe: nome do ficheiro, numero de vertices (ptr), numero de iteracoes (ptr)
// Devolve a matriz de adjacencias
int* init_dados(char *nome, int *n, int *iter)
{
	FILE *f;
	int lixo;
	int *p, *q, *k;
	int i, j;
	char z[] = "0"; //lel
	char x[] = "1"; //lel

	*iter = N_ITER;
	f=fopen(nome, "r");
	if(!f)
	{
		printf("Erro no acesso ao ficheiro dos dados\n");
		exit(1);
	}
	
	fscanf(f, " %d", n);
	
	fscanf(f, " %d", &lixo);
        
	// Alocacao dinamica da matriz
	p = malloc(sizeof(int)*(*n)*(*n));
	if(!p)
	{
	    printf("Erro na alocacao de memoria\n");
	    exit(1);
	}
	q=p;

	// Preenchimento da matriz com zeros
	for (i = 0; i < *n; i++)
		for (j = 0; j < *n; j++)
			sscanf(z, "%d", q++);
	k = p;
        
	//preenchendo de acordo com o ficheiro
	while (fscanf(f, "%d %d", &i, &j) == 2){
            //printf("%d %d\n", i,j);
            sscanf(x, "%d", k + offset(i-1, j-1, *n));   
	}
        
	fclose(f);

	return p;
}

/*offset da matriz de adjacencia*/
int offset(int i, int j, int cols) {
	return i * cols + j;
}

// Gera a solucao inicial
// Parametros: solucao, numero de vertices
//na soluçao inicial temos de atribuir numeros de 0 a n_vert, nao repetidos
void gera_sol_inicial(int *sol, int v)
{
	int i;
        int *randLookUpTable = gera_random_lookup_table(v);
	
        //atribui os rotulos aleatorios à soluçao
        for(i=0; i<v; i++)
            sol[i]=randLookUpTable[i];

      free(randLookUpTable);
}

// Escreve solucao
// Parametros: solucao e numero de vertices
void escreve_sol(int *sol, int vert)
{
	int i;

	printf("\nSolucao: ");
	for(i=0; i<vert; i++)
        {
            printf("%d ", (sol[i]) );
        }
}

// copia vector b para a (tamanho n)
void substitui(int a[], int b[], int n)
{
    int i;
    for(i=0; i<n; i++)
        a[i]=b[i];
}

// Inicializa o gerador de numeros aleatorios
void init_rand()
{
	srand((unsigned)time(NULL));
}

// Devolve valor inteiro aleatorio entre min e max
int random_l_h(int min, int max)
{
	return min + rand() % (max-min+1);
}

// Devolve um valor real aleatorio do intervalo [0, 1]
float rand_01()
{
	return ((float)rand())/RAND_MAX;
}

//gera uma lookup table de numeros aleatorio de 0 ate vert
//recebe o numero de vertices e devolve um array de numeros aleatorios
int * gera_random_lookup_table(int vert){
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
        aux1= random_l_h(0,vert-1);
        aux2= random_l_h(0,vert-1);
        
        if(aux1 != aux2)
        {
            temp = arrayAleatorio[aux1];
            arrayAleatorio[aux1]=arrayAleatorio[aux2];
            arrayAleatorio[aux2] = temp;
        }
    }
   
    return arrayAleatorio;
}

int probEvento(float prob){
    return prob > ((float)rand()/RAND_MAX);
}
