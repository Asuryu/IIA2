#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "utils.h"
#include "evolutivo.h"

void mostraASCII(){
    printf("\033[2J\033[1;1H");
    printf("██╗██╗ █████╗\n");
    printf("██║██║██╔══██╗\n");
    printf("██║██║███████║\n");
    printf("██║██║██╔══██║\n");
    printf("██║██║██║  ██║\n");
    printf("╚═╝╚═╝╚═╝  ╚═╝\n\n");
}

int random_int(int minimo, int maximo){
    int n;
    n = minimo + rand() % (maximo-minimo+1);
    return n;
}

float random_float_01(){
    int x;
    x = ((float)rand())/RAND_MAX;
    return x;
}

int *preenche_matriz(char *file, int *v, int *numero_iteracoes){
    FILE *of;
    char buffer[100];
    int v1 = 0 , v2 = 0;
    int *matriz, *matriz2;

    of=fopen(file, "r");
    if(of == NULL){
        printf("[ERRO] Ocorreu um problema ao abrir o ficheiro.");
        exit(1);
    }

    do{
        fscanf(of, " %s ", buffer);
    } while(strcmp(buffer, "edge") != 0);
    fscanf(of, " %d ", v);
    fscanf(of, "%d\n", numero_iteracoes);

    matriz = malloc(sizeof(int)*(*v)*(*v));
    if(matriz == NULL){
        printf("[ERRO] Ocorreu um problema ao alocar memória.");
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

    return matriz;
}

void gerar_solinicial(int *sol, int v){
    int x;

    for(int i = 0; i < v; i++){
        sol[i] = 0;
    }
    for(int i = 0; i < (v/2); i++){
        do{
            x = random_int(0, v-1);
        } while(sol[x] != 0);
        sol[x] = 1;
    }
}

void escrever_solucao(int *sol, int v){
    printf("\nConjunto A: ");
    for(int i = 0; i < v; i++){
        if(sol[i] == 0){
            printf("%2d  ", i);
        }
    }

    printf("\nConjunto B: ");
    for(int i = 0; i < v; i++){
        if(sol[i] == 1){
            printf("%2d  ", i);
        }
    }

    printf("\n");
}

void substitui(int a[], int b[], int n){
    for(int i = 0; i < n; i++){
        a[i] = b[i];
    }
}

int probEvento(float prob){
    return prob > ((float)rand()/RAND_MAX);
}

int offset(int i, int j, int cols){
	return i * cols + j;
}