#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "pesquisaLocal.h"

int main(){

    int vert, ares;
    int *grafo;
    char nomeFicheiro[100];
    srand((unsigned)time(NULL));

    printf("Introduza o nome do ficheiro com os dados: ");
    scanf("%s", nomeFicheiro);

    grafo = init_dados(nomeFicheiro, &vert, &ares);

    for(int k = 0; k < 10; k++){
        
    }

    return 0;
}