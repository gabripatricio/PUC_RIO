#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include "processo.h"

/*
    OBSERVACOES DE COMPILACAO:
    gcc -o main main.c
    gcc -o interpretador interpretador.c
    gcc -o escalonador escalonador.c

    gcc -o P1 p1.c
    gcc -o P2 p2.c
    gcc -o P3 p3.c
    gcc -o P4 p4.c
    gcc -o P5 p5.c
    gcc -o P6 p6.c
    gcc -o P7 p7.c
    gcc -o P8 p8.c
    gcc -o P9 p9.c
    gcc -o P10 p10.c
*/

#define TIME_QUANTUM 1

#define ROUND_ROBIN 0
#define PRIORITY 1
#define REAL_TIME 2

#define true 1
#define false 0

void erro_fork(void);

int main(int argc, char* argv[])
{
    int shmid, status;
    // criando a area de memoria compartilhada
    shmid = shmget(IPC_PRIVATE, sizeof(Processo), IPC_CREAT | S_IRUSR | S_IWUSR); 
    if (shmid < 0) 
    {
        perror("shmget");
        exit(1);
    }

    // Converte shmid para string
    char shmid_str[20];
    sprintf(shmid_str, "%d", shmid);
    
    pid_t interpretador = fork();
    if (interpretador < 0)
    {
        // erro 
        erro_fork();
    }
    else if (interpretador == 0)
    {
        //filho 
        char* args[] = {"./interpretador", shmid_str, NULL};
        execvp(args[0], args);
    }

    pid_t escalonador = fork();
    if (escalonador < 0)
    {
        erro_fork();
    }
    else if (escalonador == 0)
    {
        char* args[] = {"./escalonador", shmid_str, NULL};
        execvp(args[0], args);
    }
    
    waitpid(interpretador, &status, 0);
    waitpid(escalonador, &status, 0);
    printf("\n\n\n\nSTATUS: %d\n\n\n\n\n", status);

    shmctl(shmid, IPC_RMID, 0); // libera a memoria compartilhada
    return 0;
}

void erro_fork(void)
{
    printf("Erro no fork. Abortando o programa.\n");
    exit(1);
}