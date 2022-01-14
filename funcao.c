#include "funcao.h"

// Calcular custo de uma solução
int calcular_custo(int s[], int *mat, int v){
    int total=0,contador=0;

    for(int i=0;i<v;i++) {
        if (s[i] == 1) {
            for (int j = 0; j < v; j++) {
                if (s[j] == 1 && *(mat + i * v + j) == 1) {
                    total++;
                }
            }
        }
    }

    if(total == 0){
        for(int j=0;j<v;j++){
            if(s[j] == 1){
                contador++;
            }
        }
        return contador;
    }
    else
        return total;
}