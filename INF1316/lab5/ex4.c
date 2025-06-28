#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void signal_handler(int sig)
{
    if (sig == SIGFPE)
    {
        printf("!!!!!!! Divisão por 0 !!!!!!!\n");
        exit(1);
    }
}

int main(void)
{
    float a, b;

    signal(SIGFPE, signal_handler);

    printf("Digite o primeiro número real: ");
    scanf("%f", &a);

    printf("Digite o segundo número real: ");
    scanf("%f", &b);

    printf("\nResultados:\n");
    printf("Soma: %f\n", a + b);
    printf("Subtração: %f\n", a - b);
    printf("Multiplicação: %f\n", a * b);
    printf("Divisão: %f\n", a / b); 

    int c, d;
    printf("\n");
    printf("Digite o primeiro número inteiro: ");
    scanf("%d", &c);

    printf("Digite o segundo número inteiro: ");
    scanf("%d", &d);

    printf("\nResultados:\n");
    printf("Soma: %d\n", c + d);
    printf("Subtração: %d\n", c - d);
    printf("Multiplicação: %d\n", c * d);
    printf("Divisão: %d\n", c / d); 

    return 0;
}