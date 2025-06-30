#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"

typedef struct huffman Huffman;
struct huffman
{
    Dados dados;
    Huffman* dir;
    Huffman* esq;
};


void imprimir_arvore_huffman(Huffman* arvore) {
    if (arvore == NULL) {
        return;
    }
    if (arvore->esq == NULL && arvore->dir == NULL) {
        printf("Caractere: %c, Frequencia: %d\n", arvore->dados.c, arvore->dados.frequencia);
        return;
    }
    imprimir_arvore_huffman(arvore->esq);
    imprimir_arvore_huffman(arvore->dir);
}


char* encontrar_representacao(Huffman* arvore, char caractere) {
    if (arvore == NULL) {
        return NULL;
    }

    if (arvore->esq == NULL && arvore->dir == NULL && arvore->dados.c == caractere) {
        return "";
    }

    char* resultado_esq = encontrar_representacao(arvore->esq, caractere);
    if (resultado_esq != NULL) {
        char* representacao = (char*)malloc(strlen(resultado_esq) + 2);
        sprintf(representacao, "0%s", resultado_esq);
        return representacao;
    }

    char* resultado_dir = encontrar_representacao(arvore->dir, caractere);
    if (resultado_dir != NULL) {
        char* representacao = (char*)malloc(strlen(resultado_dir) + 2);
        sprintf(representacao, "1%s", resultado_dir);
        return representacao;
    }

    return NULL;
}


Huffman* h_criaArvore(Dados dados)
{
    Huffman* arvore = (Huffman*)malloc(sizeof(Huffman));
    if (arvore == NULL)
    {
        printf("Erro na alocacao de memoria. Abortando programa.\n");
        exit(1);
    }
    arvore->dados = dados;
    arvore->esq = NULL;
    arvore->dir = NULL;
    return arvore;
}

Huffman** criar_no_huffman(Dados* v, int tam)
{
    Huffman** no = (Huffman**)malloc(sizeof(Huffman*) * tam);
    if (no == NULL)
    {
        printf("Erro na alocacao de memoria. Abortando programa.\n");
        exit(1);
    }

    for (int i = 0; i < tam; i++)
    {
        no[i] = h_criaArvore(v[i]);
    }
    return no;
}

Huffman* criar_arvore_huffman(Huffman** nos, int tam)
{
    while (tam > 1)
    {
        Dados d;
        d.c = '@';
        d.frequencia = nos[0]->dados.frequencia + nos[1]->dados.frequencia;
        Huffman* pai = h_criaArvore(d);
        pai->esq = nos[0];
        pai->dir = nos[1];

        
        for (int i = 2; i < tam; i++)
        {
            nos[i - 2] = nos[i];
        }

        
        tam -= 1;

        
        nos[tam - 1] = pai;
    }
    return nos[0];
}

void liberar_arvore_huffman(Huffman* arvore) {
    if (arvore == NULL) {
        return;
    }
    liberar_arvore_huffman(arvore->esq);
    liberar_arvore_huffman(arvore->dir);
    free(arvore);
}