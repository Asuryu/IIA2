#include <stdio.h>
#include <stdlib.h>
#include "algoritmo.h"
#include "funcao.h"
#include "utils.h"

void genetic_operators(pchrom parents, info d, pchrom offspring) {
    crossover(parents, d, offspring);
    mutation(offspring, d);
}

void tournament(pchrom pop, info d, pchrom parents) {
    int x1, x2,i;

    for ( i = 0; i < d.pop; i++) { //realiza os torneios
        x1 = random_l_h(0, d.pop - 1);
        do
            x2 = random_l_h(0, d.pop - 1);
        while (x1 == x2);
        if (pop[x1].fitness < pop[x2].fitness)
            parents[i] = pop[x1];
        else
            parents[i] = pop[x2];
    }
}

void crossover(pchrom parents, info d, pchrom offspring) {
    int point,i,j,m,n;
    int aux = 0;
    for ( i = 0; i < d.pop; i += 2) {
        if (rand_01() < d.pr) {
            point = random_l_h(0, d.vertices - 1);
            for ( j = 0; j < point; j++) {
                offspring[i].p[j] = parents[i].p[j];
                offspring[i + 1].p[j] = parents[i + 1].p[j];
            }
            for ( j = point; j < d.vertices; j++) {
                for( m = 0; m < d.vertices; m++) {
                    for( n = 0; n < j; n++) {
                        if(parents[i+1].p[m] == offspring[i].p[n])
                            aux = 1;
                    }
                    if(aux == 0){
                        offspring[i].p[j] = parents[i+1].p[m];
                        break;
                    }
                    aux = 0;
                }
                for( m = 0; m < d.vertices; m++) {
                    for( n = 0; n < j; n++) {
                        if(parents[i].p[m] == offspring[i+1].p[n])
                            aux = 1;
                    }
                    if(aux == 0){
                        offspring[i+1].p[j] = parents[i].p[m];
                        break;
                    }
                    aux = 0;
                }
            }
        } else {
            offspring[i] = parents[i];
            offspring[i + 1] = parents[i + 1];
        }
    }
}

void mutation(pchrom offspring, info d) {
    int p1, p2, aux,i,j;
    for ( i = 0; i < d.pop; i++){
        if (rand_01() < d.pm){
            for ( j = 0; j < d.vertices / 2; j++) {
                p1 = random_l_h(0, d.vertices - 1);
                do{
                    p2 = random_l_h(0, d.vertices - 1);
                } while(p1 == p2);
                aux = offspring[i].p[p1];
                offspring[i].p[p1] = offspring[i].p[p2];
                offspring[i].p[p2] = aux;
            }
        }
    }
}
