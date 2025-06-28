#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#define TAM 10000
#define TRABALHADORES 10

int main(void)
{
    int v[TAM];

    for(int i = 0; i < TAM; i++)
    {
        v[i] = 10;
    }

    for (int i = 0; i < TRABALHADORES; i++)
    {
        if (fork() == 0)
        {
            for(int j = 0; j < TAM; j++)
            {
                v[j] *= 2;
                v[j] += 2;
            }
            exit(0);
        }

    }
    
    int verifica = 1;
    for (int i = 1; i < TAM; i++) {
    if (v[i] != v[0]) {
        verifica = 0;
        break;
    }
}

if (verifica) {
printf("Todas as posicoes sao iguais. Valor = %d\n", v[0]);
}

else {
printf("As posicoes sao diferentes\n");
}

return 0;
    return 0;
}