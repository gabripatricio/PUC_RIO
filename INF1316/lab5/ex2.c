#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#define EVER \
    ;        \
    ;
void killHandler(int sinal);
int soma = 0;

int main(void)
{
    void (*p)(int); // ponteiro para função que recebe int como parâmetro
    p = signal(SIGINT, killHandler);
    printf("Endereco do manipulador anterior %p\n", p);
    puts("TENTANDO INTERCEPTAR UM SIGKILL");
    for (EVER)
        ;
}
void killHandler(int sinal)
{
    printf("Tentaram me matar :( (%d)\n", soma++);
}