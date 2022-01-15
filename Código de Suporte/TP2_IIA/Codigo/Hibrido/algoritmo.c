#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include "algoritmo.h"
#include "utils.h"

// Preenche uma estrutura com os progenitores da pr�xima gera��o, de acordo com o resultados do torneio binario (tamanho de torneio: 2)
// Par�metros de entrada: popula��o actual (pop), estrutura com par�metros (d) e popula��o de pais a encher
void tournament(pchrom pop, struct info d, pchrom parents)
{
	int i, x1, x2;

	// Realiza popsize torneios
	for(i=0; i<d.popsize;i++)
	{
		x1 = random_l_h(0, d.popsize-1);
		do
			x2 = random_l_h(0, d.popsize-1);
		while(x1==x2);
		if(pop[x1].fitness > pop[x2].fitness)		// Problema de maximizacao
			parents[i]=pop[x1];
		else
			parents[i]=pop[x2];
	}
}

// Operadores geneticos a usar na gera��o dos filhos
// Par�metros de entrada: estrutura com os pais (parents), estrutura com par�metros (d), estrutura que guardar� os descendentes (offspring)
void genetic_operators(pchrom parents, struct info d, pchrom offspring)
{
    // Recombina��o com um ponto de corte
	crossover(parents, d, offspring);
	
	mutation(offspring, d);
}



// Preenche o vector descendentes com o resultado das opera��es de recombina��o
// Par�metros de entrada: estrutura com os pais (parents), estrutura com par�metros (d), estrutura que guardar� os descendentes (offspring)
void adjustCrossover(int a[], int vert);
void crossover(pchrom parents, struct info d, pchrom offspring)
{
	int i, j, point, geneCand; //gene candidato
        int swtch = 0 ; //flag de troca
            float crossoverAdjust =1.0;
    
	for (i=0; i<d.popsize; i+=2)
	{
       
	if (rand_01() < d.pr)
		{
			point = random_l_h(0, d.numGenes-1);
                        
                      //  printf("Point:%d ", point);
                      //  printf("\n");
                        
			for (j=0; j<point; j++) //primeira seccao copiada diretamente
			{
				offspring[i].p[j] = parents[i].p[j];
				offspring[i+1].p[j] = parents[i+1].p[j];
			}
			for (j=point; j<d.numGenes; j++) //a segunda copia apenas os numeros que ainda nao form ja colocados, se tiverem sido colocados, pomos o original do espaco
			{
                            // 1st offspring
                            swtch=1;
                            geneCand = parents[i+1].p[j];
                            for(int k =0 ; k < point ; k++)
                            {
                                if(offspring[i].p[k] == geneCand)
                                    swtch=0;
                            }
                            if(swtch) offspring[i].p[j]= geneCand; //se unico troca
                            else offspring[i].p[j]=parents[i].p[j]; //se nao mantem gene do 1o pai
                            
                            //2nd offspring
                            swtch=1;
                            geneCand = parents[i].p[j];
                            for(int k =0 ; k < point ; k++)
                            {
                                if(offspring[i+1].p[k] == geneCand)
                                    swtch=0;
                            }
                            if(swtch) offspring[i+1].p[j] = geneCand;
                            else offspring[i+1].p[j]=parents[i+1].p[j];
			}
		}
		else
		{
			offspring[i] = parents[i];
			offspring[i+1] = parents[i+1];
		}
        
            if(probEvento(crossoverAdjust)){
                adjustCrossover(offspring[i].p,  d.numGenes);
                adjustCrossover(offspring[i+1].p,  d.numGenes);
            }
	}
}

// Muta��o bin�ria com v�rios pontos de muta��o
//No algoritmo de mutaçao das aulas praticas, sendo a sooluçao binaria, a mutaçao era feita na conversao de 0 para 1
//No contexto do trabalho pratico, temos de fazer uma troca entre dos valores da soluçao
// Par�metros de entrada: estrutura com os descendentes (offspring) e estrutura com par�metros (d)
void mutation(pchrom offspring, struct info d)
{
	int i, j, t1, t2, temp;

        for(i=0;i<d.popsize; i++ )
            for (j=0; j<d.numGenes; j++)
                if (rand_01() < d.pm)
                {
                    do{
                         t1= random_l_h(0,d.numGenes-1);
                        t2= random_l_h(0,d.numGenes-1);
                        if(t1!=t2)
                        {
                            temp = offspring[i].p[t1];
                            offspring[i].p[t1]=offspring[i].p[t2];
                            offspring[i].p[t2] = temp;
                        }
                    }while(t1=t2);
                }
}


void adjustCrossover(int a[], int vert){
    int count=0;

    int checkVal[1000];
    
     for(int k=0; k< vert; k++)
            checkVal[a[k]-1] += 1;
   
    

        while(count != vert)
        {
            count =0;
             for(int k =0 ; k<vert ; k++)
             {
                if(checkVal[k] == 1) count++;
                if(checkVal[k] > 1)
                    for(int j=0; j < vert; j++)
                      if(a[j] == k+1){
                          for(int x=0; x<vert; x++)
                              if(checkVal[x]==0)
                              {
                                  a[j]=x+1;
                                   for(int k=0; k< vert; k++)checkVal[k] = 0;
                                  for(int k=0; k< vert; k++) checkVal[a[k]-1] += 1; //atualiza o checkRep array
                                  break;
                              }break;}   
             }
        }
       for(int k=0; k< vert; k++)
           checkVal[k] = 0;
}