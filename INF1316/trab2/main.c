#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#include "memoria.h"
#include "acesso.h"
#include "utils.h"
#include "algoritmos.h"

#define KILOBYTE 1024

int main(int argc, char* argv[])
{
    

    if (argc < 5)
    {
        printf("Uso incorreto do programa.\nUso correto: ./%s <algoritmo> <arquivo_entrada> <tamanho_pagina> <quantidade_memoria>", argv[0]);
        return 1;
    }

    char* nome_algoritmo = argv[1];
    char* nome_arquivo = argv[2];
    int tamanho_pagina = atoi(argv[3]); 
    int tamanho_memoria = atoi(argv[4]);

    int tamanho_pagina_bytes = tamanho_pagina * KILOBYTE;
    int tamanho_memoria_bytes = tamanho_memoria * KILOBYTE * KILOBYTE; // pq eh mb

    int numero_quadros = tamanho_memoria_bytes / tamanho_pagina_bytes;
    int shift = calcula_shift(tamanho_pagina_bytes);

    int quantidade_linhas = conta_linhas(nome_arquivo);
    Frame* memoria_fisica = frame_init(numero_quadros);
    Acesso* acessos = acesso_init(quantidade_linhas);

    int quantidade_paginas_faltantes;
    int quantidade_paginas_escritas;

    if (memoria_fisica == NULL || acessos == NULL)
    {
        return 1;
    }

    preenche_vetor(acessos, nome_arquivo);

    if ( strcmp(nome_algoritmo, "LRU")  == 0)
    {
        algoritmo_LRU(memoria_fisica, acessos, shift, numero_quadros, quantidade_linhas, &quantidade_paginas_faltantes, &quantidade_paginas_escritas);
    }
    else if (strcmp(nome_algoritmo, "clock") == 0)
    {
        algoritimo_clock(memoria_fisica, acessos, shift, numero_quadros, quantidade_linhas, &quantidade_paginas_faltantes, &quantidade_paginas_escritas);
    }
    else if (strcmp(nome_algoritmo, "2nd") == 0)
    {
        algoritimo_segunda_chance(memoria_fisica, acessos, shift, numero_quadros, quantidade_linhas, &quantidade_paginas_faltantes, &quantidade_paginas_escritas);;
    }
    else if (strcmp(nome_algoritmo, "otimo") == 0)
    {
        algoritimo_otimo(memoria_fisica, acessos, shift, numero_quadros, quantidade_linhas, &quantidade_paginas_faltantes, &quantidade_paginas_escritas);;
    }
    else
    {
        printf("Esse algoritmo nao esta entre nos\n.");
        printf("Possiveis entradas: LRU, clock, 2nd, otimo\n");
        return 1;
    }

    printf("Executando o simulador...\n");
    printf("Arquivo de entrada: %s\n", nome_arquivo);
    printf("Tamanho da memória física: %d (bytes)\n", tamanho_memoria_bytes);
    printf("Tamanho das páginas: %d (bytes)\n", tamanho_pagina_bytes);
    printf("Algoritmo de substituição: %s\n", nome_algoritmo);

    gera_estatisticas(quantidade_paginas_faltantes, quantidade_paginas_escritas);

    free(acessos);
    free(memoria_fisica);
}