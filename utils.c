#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "utils.h"

// Para que o random retorne sempre numeros diferentes
void init_rand(){
    srand((unsigned)time(NULL));
}

// Gerar valor random entre minimo e maximo
int random(int minimo, int maximo){
    int n;
    n = minimo + rand() % (maximo-minimo+1);
    return n;
}

// Gerar valor real entre 0 e 1
float random_0e1(){
    int x;
    x = ((float)rand())/RAND_MAX;
    return x;
}

// Inicializar a matriz
int *setMatriz(char *nome_ficheiro, int *v, int *numero_iteracoes){
    FILE *of;
    char lerString[200];
    int v1=0,v2=0;
    int *matriz, *matriz2;

    of=fopen(nome_ficheiro,"r");
    if(of == NULL){
        printf("Erro na abertura do ficheiro!");
        exit(1);
    }

    do{
        fscanf(of," %s ",lerString);
    }while(strcmp(lerString,"edge")!=0);
    fscanf(of," %d ",v);
    fscanf(of,"%d\n",numero_iteracoes);

    if(*v<=0){
        printf("\nErro! Numero de vertices menor ou igual a 0");
        exit(1);
    }
    else if(*v > 500){
        printf("\nErro! Numero de vertices maior do que 500");
    }

    matriz = malloc(sizeof(int)*(*v)*(*v));
    if(matriz == NULL){
        printf("\nErro ao alocar memoria para a matriz!");
        fclose(of);
        exit(1);
    }

    matriz2 = matriz;

    for(int i=0;i<(*v);i++){
        for(int j=0;j<(*v);j++) {
            fscanf(of, "e %d %d\n", &v1, &v2);
            *(matriz + (i - 1) * (*v) + (j - 1)) = 1;
            *(matriz + (j - 1) * (*v) + (i - 1)) = 1;
            matriz2 = matriz;
        }
    }

    for(int x=0;x<(*v)*(*v);x++){
            printf("[%d]",matriz2[x]);
        }

    return matriz;
}

// Gerar uma solução
void gerar_solucaoInicial(int *solucao, int v){
    int x;

    for(int i=0;i<v;i++){
        solucao[i]=0;
    }
    for(int i=0;i<v/2;i++){
        do{
            x = random(0,v-1);
        }while(solucao[x] != 0);
        solucao[x] = 1;
    }
}

// Escrever uma solução
void escrever_solucao(int *solucao, int v){
    printf("\nConjunto A: ");
    for(int i=0;i<v;i++){
        if(solucao[i]==0){
            printf("%2d  ",i);
        }
    }

    printf("\nConjunto B: ");
    for(int i=0;i<v;i++){
        if(solucao[i]==1){
            printf("%2d  ",i);
        }
    }

    printf("\n");
}

// Copiar vetor b para o vetor a de tamanho n
void substitui(int a[], int b[], int n){
    for(int i=0;i<n;i++){
        a[i]=b[i];
    }
}

