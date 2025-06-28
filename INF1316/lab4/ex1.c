/*

Repetir o lab 3 agora usando memória compartilhada para armazenamento dos vetores.

*/

/*
Ex1: Paralelismo

Criar um vetor a de 10.000 posições inicializado com valor 10. 
Criar 10 processos trabalhadores que utilizam áreas diferentes do vetor para multiplicar cada elemento da sua parcela do vetor por 2
armazenando esse resultado no vetor e para somar as posições do vetor retornando o resultado para um processo coordenador que irá apresentar 
a soma de todas as parcelas recebidas dos trabalhadores.

*/


#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define TAM 10000
#define TRABALHADORES 10

int main(void)
{
    int pid, shm_vetor, shm_soma;

    // criar a memoria compartilhada com o vetor principal
    shm_vetor = shmget(IPC_PRIVATE, sizeof(int) * TAM, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
    shm_soma = shmget(IPC_PRIVATE, sizeof(int) * TRABALHADORES, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
    if ( (shm_vetor < 0) || (shm_soma < 0) )
    {
        printf("Erro ao criar memoria compartilhada.\n");
        exit(1);
    }

    // anexaar
    int* v = (int*)shmat(shm_vetor, NULL, 0);
    int* soma = (int*)shmat(shm_soma, NULL, 0);

    for(int i = 0; i < TAM; i++)
    {
        v[i] = 10;
    }

    for(int i = 0; i < TRABALHADORES; i++)
    {
        soma[i] = 0;
    }

    for(int i = 0; i < TRABALHADORES; i++)
    {
        pid = fork();

        if (pid < 0)
        {
            printf("Erro na criacao do preocesso\n");
            exit(1);
        }
        else if (pid == 0)
        {
            int inicio = i* (TAM/TRABALHADORES);
            int fim = (i + 1)* (TAM/TRABALHADORES);
            int somatorio = 0;

            for(int j = inicio; j < fim; j++)
            {
                v[j] *= 2;
                somatorio += v[j];
            }
            soma[i] = somatorio;

            shmdt(v);
            shmdt(soma);

            exit(0);
        }
    }

    for(int i = 0; i < TRABALHADORES; i++)
    {
        wait(NULL);
    }

    for (int i = 0; i < TRABALHADORES; i++)
    {
        printf("Soma[%d]: %d\n", i, soma[i]);
    }
    
    shmdt(v);
    shmdt(soma);
    shmctl(shm_vetor, IPC_RMID, NULL);
    shmctl(shm_soma, IPC_RMID, NULL);

    return 0;
}