#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT 80
#define MAX_ARGS 40
#define TRUE 1

int main(void) 
{
    char comando[MAX_INPUT];
    char* args[MAX_ARGS];

    while(TRUE)
    {
        printf("$ ");
        if (fgets(comando, MAX_INPUT, stdin) == NULL)
        {
            break;
        }

        comando[strcspn(comando, "\n")] = 0; // pra tirar o \n so

        int i = 0; 
        char* params = strtok(comando, " ");

        while(params != NULL && i < MAX_ARGS - 1)
        {
            args[i++] = params;
            params = strtok(NULL, " ");
        }

        args[i] = NULL; // tem que ser NULL pq o execv pede

        if (fork() != 0)
        {
            wait(NULL);
        }
        else
        {
            if (strcmp(args[0], "meucat") == 0)
            {
                execv("./meucat", args);
            }
            else if (strcmp(args[0], "meuecho") == 0)
            {
                execv("./meuecho", args);
            }

            else if (strcmp(args[0], "ls") == 0)
            {
                execvp("ls", args);
            }
            else
            {
                printf("Comando não reconhecido.\n");
            }
        }
    }
    return 0;
}