#include <stdio.h>
#include <stdlib.h>

int* init_dados(char *nome, int *n, int *m)
{
	FILE *f;
	int *p, *q;
	int i, j;
	char buffer[100];

	f=fopen(nome, "r");
	if(!f)
	{
		printf("Erro no acesso ao ficheiro dos dados\n");
		exit(1);
	}
	
	// Read file until EOF
	while(fgets(buffer, 100, f))
	{
		// Read number of vertices
		printf("%s", buffer);
		if(buffer[0] == 'p'){
			printf("asdasd");
			sscanf(buffer, "p edge %d %d", n, m);
			printf("%d %d\n", *n, *m);
		} else if(buffer[0] == 'e'){
			// Read edges
			p = (int*)malloc((*m)*2*sizeof(int));
			q = p + (*m);
			for(i=0; i<*m; i++)
			{
				fgets(buffer, 100, f);
				sscanf(buffer, "%d %d", p+i, q+i);
			}
		}
	}



	p = malloc(sizeof(int)*(*n)*(*m));
	if(!p)
	{
	    printf("Erro na alocacao de memoria\n");
	    exit(1);
	}
	q=p;
	// Preenchimento da matriz
	for(i=0; i<*n; i++)
        for(j=0; j<*m; j++)
            fscanf(f, " %d", q++);
	fclose(f);
	return p;
}

void substitui(int a[], int b[], int n)
{
    int i;
    for(i=0; i<n; i++)
        a[i]=b[i];
}

int random_l_h(int min, int max)
{
	return min + rand() % (max-min+1);
}

float rand_01()
{
	return ((float)rand())/RAND_MAX;
}