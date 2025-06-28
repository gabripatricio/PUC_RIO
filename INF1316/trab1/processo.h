#ifndef PROCESSO_H
#define PROCESSO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h> // para pid_t

// Constantes
#define MAX_NOME 32
#define TIME_QUANTUM 1

#define ROUND_ROBIN 0
#define PRIORITY 1
#define REAL_TIME 2

#define true 1
#define false 0

#define running 1
#define waiting 0

// Structs
typedef struct Processo {
    char nome[MAX_NOME];
    int tipo;
    pid_t id;
    int prioridade;
    int inicio;
    int duracao;
    int estado;
    int lido; // 0 = vazio, 1 = pronto para leitura, 2 = já lido
} Processo;

typedef struct Lista {
    Processo* processo;
    struct Lista* proximo;
} Lista;

// Funções
Processo* criaProcesso(char* nome, int tipo, int prioridade, int inicio, int duracao, int estado);
void exibe_dados(Processo* p);

#endif