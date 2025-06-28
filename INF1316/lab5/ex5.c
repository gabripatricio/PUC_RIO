#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define TEMPO_MAX 15

void trata_erro(void);

int main(void)
{
    char *args[] = {"./loop", NULL};
    pid_t f1 = fork();

    if (f1 < 0)
    {
        trata_erro();
    }
    else if (f1 == 0) // filho
    {
        execvp("./loop", args);
        exit(1);
    }
    
    // so o pai chega ate aqui...
    pid_t f2 = fork();
    if (f2 < 0)
        trata_erro();

    else if (f2 == 0) // filho
    {
        execvp("./loop", args);
        exit(1);
    }

    printf("Coordenando:\n");

    int tempo = 0;

    while(tempo < TEMPO_MAX)
    {
        if (tempo % 2 == 0)
        {
            kill(f1, SIGCONT); // manda o filho 1 continuar
            kill(f2, SIGSTOP); // manda o filho 2 parar
            printf("Executando f1\n");
        }
        else
        {
            kill(f1, SIGSTOP); // manda o filho 1 parar
            kill(f2, SIGCONT); // manda o filho 2 continuar
            printf("Executando f2\n");
        }
        sleep(1); // so para ter certeza de que se passou 1 seg
        tempo++;
    }

    kill(f1, SIGKILL);
    kill(f2, SIGKILL);

    waitpid(f1, NULL, 0);
    waitpid(f2, NULL, 0);

    printf("Filhos mortos!\n");

    return 0;
}

void trata_erro(void)
{
    printf("Erro na criacao do processo.\n");
    exit(1);
}