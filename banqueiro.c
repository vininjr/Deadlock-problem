#include <stdio.h>
#include <stdlib.h>

int **necessidade, **alocado, **max_aloc, *disponivel, *alocacao, *executando, seguro = 0;
int count = 0, i, j, exec, recursos, processos, k = 1;

void inicia_arquivo();
void print();
void esta_seguro();

int main()
{
    inicia_arquivo();
    esta_seguro();

    return 0;
}

void esta_seguro()
{
    while (count != 0)
    {
        seguro = 0;
        for (i = 0; i < processos; i++)
        {
            if (executando[i])
            {
                exec = 1;
                for (j = 0; j < recursos; j++)
                {
                    necessidade[i][j] = max_aloc[i][j] - alocado[i][j];

                    if (necessidade[i][j] > disponivel[j])
                    {
                        exec = 0;
                        break;
                    }
                }
                if (exec)
                {

                    printf("\nProcesso %d esta executando\n", i);
                    executando[i] = 0;
                    count--;
                    seguro = 1;

                    for (j = 0; j < recursos; j++)
                    {
                        disponivel[j] += alocado[i][j];
                    }
                    for (i = 0; i < recursos; i++)
                    {
                        printf("%d ", disponivel[i]);
                    }
                    printf("\n");

                    break;
                }
            }
        }
        if (!seguro)
        {
            printf("\nProcessos estao em estado inseguro.\n");
            break;
        }
        else
        {
            printf("\nProcessos em estado seguro");
            printf("\nDisponivel:");

            for (i = 0; i < recursos; i++)
            {
                printf("%d ", disponivel[i]);
            }

            printf("\n");
        }
    }
}

void inicia_arquivo()
{
    int i,j;
    FILE *input;
    input = fopen("input1.txt", "r");

    fscanf(input, "%d", &processos);
    fscanf(input, "%d", &recursos);

    disponivel = (int*)malloc(sizeof(int)*recursos);
    alocacao = (int*)malloc(sizeof(int)*processos);
    executando = (int*)malloc(sizeof(int)*processos);

    for(i=0; i<processos; i++)
    {
        alocacao[i] = 0;
    }

    for (i = 0; i < processos; i++)
    {
        executando[i] = 1;
        count++;
    }

    for(i=0; i<recursos; i++)
        fscanf(input,"%d",&disponivel[i]);

    alocado = (int**)malloc(sizeof(int*)*processos);
    for (i = 0; i < processos; i++)
    {
        alocado[i] = (int*) malloc(recursos * sizeof(int));
        for (j = 0; j < recursos; j++)
        {
            fscanf(input, "%d", &alocado[i][j]);
        }
    }

    max_aloc = (int**)malloc(sizeof(int*)*processos);
    for (i = 0; i < processos; i++)
    {
        max_aloc[i] = (int*) malloc(recursos * sizeof(int));
        for (j = 0; j < recursos; j++)
        {
            fscanf(input, "%d", &max_aloc[i][j]);
        }
    }

    necessidade = (int**)malloc(sizeof(int*)*processos);
    for (i = 0; i < processos; i++)
    {
        necessidade[i] = (int*) malloc(recursos * sizeof(int));
    }

    for (i = 0; i < processos; i++)
    {
        for (j = 0; j < recursos; j++)
        {
            alocacao[j] += alocado[i][j];
        }
    }

    fclose(input);
}
