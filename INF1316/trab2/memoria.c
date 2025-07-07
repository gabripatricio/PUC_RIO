#include "memoria.h"
#include <stdio.h> 
#include "acesso.h"


Frame* frame_init(int numero_quadros)
{
    Frame* memoria_fisica = (Frame*)malloc(numero_quadros * sizeof(Frame));  

    if (!memoria_fisica)
    {
        perror("Erro na alocacao dinamica de memoria para os frames\n");
        return NULL;
    }

    for (int i = 0; i < numero_quadros; i++)
    {
        memoria_fisica[i].modificada = 0;
        memoria_fisica[i].pagina_virtual = VAZIA;
        memoria_fisica[i].referenciada = 0;
        memoria_fisica[i].ultimo_acesso = -1;
    }

    return memoria_fisica;
}

int busca_pagina(Frame* vetor, int endereco, int tamanho)
{
    for(int i = 0; i < tamanho; i++)
    {
        if (vetor[i].pagina_virtual == endereco)
        {
            return i;
        }
    }
    return -1;
}

void substitui_pagina(Frame* vetor, int endereco, int indice, int tempo, char bit_rw)
{
    vetor[indice].pagina_virtual = endereco;
    vetor[indice].ultimo_acesso = tempo;
    vetor[indice].modificada = (bit_rw == 'W') ? 1 : 0; // farmar aura
    vetor[indice].referenciada = 1;
}

int encontra_pagina_mais_velha(Frame* vetor, int tamanho_vetor)
{
    if (vetor == NULL || tamanho_vetor <= 0)
    {
        return -1;
    }

    int menor_tempo = vetor[0].ultimo_acesso;
    int indice = 0;

    for (int i = 1; i < tamanho_vetor; i++)
    {
        if (vetor[i].ultimo_acesso < menor_tempo)
        {
            menor_tempo = vetor[i].ultimo_acesso;
            indice = i;
        }
    }
    return indice;
}