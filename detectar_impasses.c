#include <stdio.h>
#include <stdlib.h>

int num_process,num_resources;

int **allocation,**request,*available;

int i, j, k, atendido, deadlock = 0, numero_atendimento = 0;
int *atendidos, *foi_atendido;

void atenderProcessos(int num_processo);
void inicia_arquivo();
void print();

int main ()
{
    inicia_arquivo();
    print();
    for(i = 0 ; i < num_process; i++)
        foi_atendido[i] = 1;

    for(i = 0; i < num_process; i++)
    {
        atendido = 0;

        for(j = 0; j < num_resources; j++)
        {
            if(request[i][j] <= available[j])
            {
                atendido++;
            }
        }

        if(atendido == num_resources)
        {
            for(k = 0; k < num_resources; k++)
            {
                available[k] = available[k] + allocation[i][k];
                allocation[i][k] = 0;
            }

            foi_atendido[i] = 1;
            atendidos[numero_atendimento] = i;
            numero_atendimento++;

            for(k = 0; k < num_process; k++)
            {
                if(foi_atendido[k] == 0)
                    atenderProcessos(k);
            }

        }
        else
        {
            foi_atendido[i] = 0;
        }

    }

    for(i = 0; i < num_process; i++)
        if(foi_atendido[i] == 0)
            deadlock = 1;
    print();

    if(deadlock == 1)
    {
        printf("Houve deadlock com os seguintes processos:\n");
        for(i = 0; i < num_process; i++)
            if(foi_atendido[i] == 0)
                printf("p%d ", i);
    }
    else
    {
        printf("Nao houve deadlock. Os processos podem ser atendidos na seguinte ordem:\n");
        for(i = 0; i < num_process; i++)
            printf("p%d ", atendidos[i]);
    }
    printf("\n\n");
    return 0;
}

void atenderProcessos(int num_processo)
{
    atendido = 0;
    for(j = 0; j < num_resources; j++)
    {
        if(request[num_processo][j] <= available[j])
        {
            atendido++;
        }
    }

    if(atendido == num_resources)
    {
        int z;
        for(z = 0; z < num_resources; z++)
        {
            available[z] = available[z] + allocation[num_processo][z];
            allocation[num_processo][z] = 0;
        }

        foi_atendido[num_processo] = 1;
        atendidos[numero_atendimento] = num_processo;
        numero_atendimento++;

        if (numero_atendimento == num_resources)
            return;

        for(k = 0; k < num_process; k++)
        {
            if(foi_atendido[k] == 0)
                atenderProcessos(k);
        }
    }
}

void inicia_arquivo()
{
    int i,j;
    FILE *input;
    input = fopen("input.txt", "r");

    fscanf(input, "%d", &num_process);
    fscanf(input, "%d", &num_resources);

    atendidos = (int*)malloc(sizeof(int)*num_process);
    foi_atendido = (int*)malloc(sizeof(int)*num_process);

    available = (int*)malloc(sizeof(int)*num_resources);
    for(i=0; i<num_resources; i++)
    {
        fscanf(input, "%d", &available[i]);
    }

    allocation = (int**)malloc(sizeof(int*)*num_process);
    for (i = 0; i < num_process; i++)
    {
        allocation[i] = (int*) malloc(num_resources * sizeof(int));
        for (j = 0; j < num_resources; j++)
        {
            fscanf(input, "%d", &allocation[i][j]);
        }
    }

    request = (int**)malloc(sizeof(int*)*num_process);
    for (i = 0; i < num_process; i++)
    {
        request[i] = (int*) malloc(num_resources * sizeof(int));
        for (j = 0; j < num_resources; j++)
        {
            fscanf(input, "%d", &request[i][j]);
        }
    }

    fclose(input);
}

void print()
{
    int i,j;
    printf("\nAvailable\n");
    for(i=0; i<num_resources; i++)
    {
        printf("%d ",available[i]);
    }

    printf("\nAllocation\n");
    for(i=0; i<num_process; i++)
    {
        for(j=0; j<num_resources; j++)
        {
            printf("%d ",allocation[i][j]);
        }
        printf("\n");
    }

    printf("Request\n");
    for(i=0; i<num_process; i++)
    {
        for(j=0; j<num_resources; j++)
        {
            printf("%d ",request[i][j]);
        }
        printf("\n");
    }

}
