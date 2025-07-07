#include "utils.h"
#include <stdio.h>
#include <math.h>  

int conta_linhas(char* nome_arquivo)
{
    FILE* f = fopen(nome_arquivo, "r");
    if (!f) {
        perror("Não foi possível abrir o arquivo para contar as linhas");
        return 0;
    }

    int linhas = 0;
    char linha[128];
    while (fgets(linha, sizeof(linha), f) != NULL) {
        linhas++;
    }

    fclose(f);
    return linhas;
}

int calcula_shift(int tamanho_pagina)
{
    return log2(tamanho_pagina);
}

void gera_estatisticas(int falta_pagina, int pagina_escrita)
{
    printf("Estatisticas geradas:\n");
    printf("Numero de paginas faltantes: %d\n", falta_pagina);
    printf("Numero de paginas escritas: %d\n", pagina_escrita);
}

int encontra_maximo(int* v, int tamanho)
{
    int maximo = 0;
    int indice = 0;
    for(int i = 0; i < tamanho; i++)
    {
        if (v[i] > maximo)
        {
            maximo = v[i];
            indice = i;
        }
    }
    return indice;
}