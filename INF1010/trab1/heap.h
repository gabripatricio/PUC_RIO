#pragma once
#include <stdlib.h>
#include <stdio.h>

#define N 256

typedef struct dados {
    char c;
    int frequencia;
}Dados;

typedef struct heap {
    int max;
    int pos;
    Dados* dados;
}Heap;

Dados* cria_vetor_dados(int tam)
{
    Dados* vetor = (Dados*)malloc(sizeof(Dados) * tam);
    if (vetor == NULL)
    {
        printf("Erro na alocacao de memoria. Abortando programa.");
        exit(1);
    }
    return vetor;
}

void preenche_vetor_dados(Dados* v, int* tabela)
{
    int pos = 0;
    for (int i = 0; i < N; i++)
    {
        if (tabela[i] > 0)
        {
            v[pos].c = (char)i;
            v[pos].frequencia = tabela[i];
            pos++;
        }
    }
}

Heap* cria_heap(int max)
{
    Heap* heap = (Heap*)malloc(sizeof(Heap));
    if (heap == NULL)
    {
        printf("Erro na alocacao de memoria. Abortando programa.\n");
        exit(1);
    }

    heap->max = max;
    heap->pos = 0;

    heap->dados = (Dados*)malloc(sizeof(Dados) * max);
    if (heap->dados == NULL)
    {
        printf("Erro na alocacao de memoria. Abortando programa.\n");
        exit(1);
    }
    return heap;
}

static void troca(int a, int b, Dados* vetor)
{
    Dados c = vetor[a];
    vetor[a] = vetor[b];
    vetor[b] = c;
}
static void corrige_acima(Heap* heap, int pos)
{
    while (pos > 0)
    {
        int pai = (pos - 1) / 2;
        if (heap->dados[pai].frequencia > heap->dados[pos].frequencia)
        {
            troca(pai, pos, heap->dados);
        }
        else
        {
            break;
        }
        pos = pai;
    }
}

static void corrige_abaixo(Heap* heap)
{
    int pai = 0;
    while (2 * pai + 1 < heap->pos)
    {
        int f;
        int fesq = 2 * pai + 1;
        int fdir = 2 * pai + 2;

        if (fdir >= heap->pos)
            fdir = fesq;

        if (heap->dados[fesq].frequencia <= heap->dados[fdir].frequencia)
        {
            f = fesq;
        }
        else
        {
            f = fdir;
        }

        if (heap->dados[pai].frequencia > heap->dados[f].frequencia)
        {
            troca(pai, f, heap->dados);
        }
        else
        {
            break;
        }
        pai = f;
    }
}

Dados* heap_sort(Heap* heap, int tamanho)
{
    Dados* v = (Dados*)malloc(sizeof(Dados) * tamanho);
    if (v == NULL)
    {
        printf("Erro na alocacao de memoria.");
        exit(1);
    }

    int n = heap->pos;
    for (int i = 0; i < n; i++)
    {
        Dados topo = heap->dados[0];
        v[i] = topo;
        troca(0, heap->pos - 1, heap->dados);
        heap->pos--;
        corrige_abaixo(heap);
    }
    heap->pos = n;
    return v;
}

void heap_insere(Heap* heap, Dados* info)
{
    if (heap->pos > heap->max)
    {
        printf("Heap cheio. Impossivel inserir mais dados");
        return;
    }

    heap->dados[heap->pos].c = info->c;
    heap->dados[heap->pos].frequencia = info->frequencia;
    corrige_acima(heap, heap->pos);
    heap->pos++;
}

static void heap_remove(Heap* heap)
{
    int pai = 0;
    while(2 * pai + 1 < heap->pos)
    {
        int fesq = 2 * pai + 1;
        int fdir = 2 * pai + 1;
        int filho;
        if (fdir >= heap->pos)
            fdir = fesq;
        if (heap->dados[fesq].frequencia <= heap->dados[fdir].frequencia)
            filho = fesq;
        else
            filho = fdir;

        if (heap->dados[pai].frequencia > heap->dados[filho].frequencia)
            troca(pai, filho, heap->dados);
        else
            break;
        pai = filho;
    }
}

void libera_heap(Heap* heap)
{
    free(heap->dados);
    free(heap);
    printf("Toda a memoria do heap foi liberda.\n");
}