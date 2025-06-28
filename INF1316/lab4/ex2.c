/*
Ex2: concorrência

Considere o vetor de 10.000 posições inicializado com o valor 10. Crie 10 trabalhadores, ambos multiplicam por 2 e somam 2 em todas as posições do vetor. Verifique automaticamente se todas as posições do vetor resultante têm valores iguais e explique o que ocorreu.
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
    // cria memoria compartiljada
    int shm_vetor = shmget(IPC_PRIVATE, sizeof(int) * TAM, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);

    // anexa a memoria compartilhada
    int *v = (int *)shmat(shm_vetor, NULL, 0);

    for (int i = 0; i < TAM; i++)
    {
        v[i] = 10;
    }

    for (int i = 0; i < TRABALHADORES; i++)
    {
        if (fork() == 0)
        {
            for (int j = 0; j < TAM; j++)
            {
                v[j] *= 2;
                v[j] += 2;
            }
            exit(0);
        }
    }

    for (int i = 0; i < TRABALHADORES; i++)
    {
        wait(NULL);
    }

    int verifica = 1;
    for (int i = 1; i < TAM; i++)
    {
        if (v[i] != v[0])
        {
            verifica = 0;
            break;
        }
    }

    if (verifica)
    {
        printf("Todas as posicoes sao iguais. Valor = %d\n", v[0]);
    }

    else
    {
        printf("As posicoes sao diferentes\n");
    }

    int soma = 0;
    for (int i = 0; i < TAM; i++)
    {
        soma += v[i];
    }
    printf("O valor da soma é: %d\n", soma);

    shmdt(v);
    shmctl(shm_vetor, IPC_RMID, NULL);
    return 0;
}