#pragma once
#include <stdlib.h>
#include <stdio.h>

#define N 256

int* cria_tabela(void)
{
    int* tabela = (int*)malloc(N * sizeof(int));
    if (tabela == NULL)
    {
        printf("Erro na alocacao de memoria. Abortando programa");
        exit(1);
    }
    return tabela;
}

void preenche_zero(int* tabela)
{
    for (int i = 0; i < N; i++)
        tabela[i] = 0;
}

void preenche_tabela_arq(int* tabela, FILE* file)
{
    char c;
    c = fgetc(file);
    while (c != EOF)
    {
        tabela[c]++;
        c = fgetc(file);
    }
}

void exibe_tabela(int* tabela)
{
    printf("\n\n------------------------TABELA DE FREQUENCIAS-------------------\n\n");
    for (int i = 0; i < N; i++)
    {
        if (tabela[i] != 0)
            if (i == 32) {
                printf("Indice: %d Quantidade: %d Caracter: (ESPACO)\n", i, tabela[i]);
            }
            else if (i == 10) {
                printf("Indice: %d Quantidade: %d Caracter: (ENTER)\n", i, tabela[i]);
            }
            else {
                printf("Indice: %d Quantidade: %d Caracter: %c\n", i, tabela[i], i);
            }
    }
}

int tamanho_tabela(int* tabela)
{
    int cont = 0;
    for (int i = 0; i < N; i++)
    {
        if (tabela[i] != 0)
        {
            cont++;
        }
    }
    return cont;
}

void libera_tabela(int* tabela)
{
    free(tabela);
    printf("A memoria da tabela foi liberada com sucesso!\n");
}