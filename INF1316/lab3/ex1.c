#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define TAM 10000
#define TRABALHADORES 10

int main(void)
{
    int v[TAM];
    int soma[TRABALHADORES];
    pid_t pid;

    for (int i = 0; i < 10000; i++)
    {
        v[i] = 10;
    }

    for (int i = 0; i < TRABALHADORES; i++)
    {
        soma[i] = 0;
    }

    for(int i = 0; i < TRABALHADORES; i++)
    {
        pid = fork();

        if (pid < 0) {
            printf("Erro na criacao do processo.\n");
            exit(1);
        }

        if (pid == 0) { 
            int inicio = i * (TAM / TRABALHADORES);
            int fim = (i + 1) * (TAM / TRABALHADORES);
            int soma_parcial = 0;

            for (int j = inicio; j < fim; j++) {
                v[j] *= 2;
                soma_parcial += v[j];
            }

            soma[i] = soma_parcial;
            
            exit(soma_parcial);
        }
    }

    for (int i = 0; i < TRABALHADORES; i++)
    {
        printf("Soma[%d]: %d\n", i, soma[i]);
    }
    return 0;
}
