#include <stdio.h>
#include <stdlib.h>

int i,j,k,p,r,temp;
int **matriz_requisicao, **matriz_alocacao, **t_matriz_alocacao;
int *t_res,*alloc_res,*a_res;

void inicia_arquivo();

int main()
{

    inicia_arquivo();

    for(i=0; i<p; i++)
    {
        for(j=0; j<r; j++)
        {
            t_matriz_alocacao[i][j]=matriz_alocacao[j][i];
        }
    }

    for (i = 0; i < r; i++)
    {
        alloc_res[i]=0;
        for(j=0; j<p; j++)
        {
            alloc_res[i]=alloc_res[i]+matriz_alocacao[i][j];
        }
    }

    for(i=0; i<r; i++)
    {
        a_res[i]=(t_res[i]-alloc_res[i]);
    }

    for(k=0; k<p; k++)
    {
        for(i=0; i<p; i++)
        {
            temp=0;
            if(matriz_requisicao[i][0]<0)
                continue;
            for(j=0; j<r; j++)
            {
                if(matriz_requisicao[i][j]<=a_res[j])
                {
                    temp++;
                }
            }

            if(temp==r)
            {
                printf("Processo %d foi completo\n", i+1);
                for(j=0; j<r; j++)
                {
                    a_res[j]+=t_matriz_alocacao[i][j];
                    matriz_requisicao[i][j]=-1;
                }
                break;
            }
        }
    }

    for (i = 0; i < p; i++)
    {
        if (matriz_requisicao[i][0]>=0)
        {
            printf("Processo %d esta em deadlock\n", i+1);
        }
    }
    return 0;
}

void inicia_arquivo()
{

    int i,j;
    FILE *input;
    input = fopen("inputs.txt", "r");
    fscanf(input,"%d",&p);
    fscanf(input,"%d",&r);

    t_res = (int*) malloc(r * sizeof(int));
    alloc_res = (int*) malloc(r * sizeof(int));
    a_res = (int*) malloc(r * sizeof(int));

    for (i = 0; i < r; i++)
    {
        fscanf(input, "%d", &t_res[i]);
    }

    matriz_requisicao = (int**)malloc(sizeof(int*)*p);
    for (i = 0; i < p; i++)
    {
        matriz_requisicao[i] = (int*) malloc(r * sizeof(int));
        for (j = 0; j < r; j++)
        {
            fscanf(input, "%d", &matriz_requisicao[i][j]);
        }
    }

    matriz_alocacao = (int**)malloc(sizeof(int*)*r);
    for (i = 0; i < r; i++)
    {
        matriz_alocacao[i] = (int*) malloc(p * sizeof(int));
        for (j = 0; j < p; j++)
        {
            fscanf(input, "%d", &matriz_alocacao[i][j]);
        }

    }
    t_matriz_alocacao = (int**)malloc(sizeof(int*)*p);
    for (i = 0; i < p; i++)
    {
        t_matriz_alocacao[i] = (int*) malloc(r * sizeof(int));
    }

    fclose(input);

}
