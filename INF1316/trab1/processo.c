#include "processo.h"

Processo* criaProcesso(char* nome, int tipo, int prioridade, int inicio, int duracao, int estado) {
    Processo* novo = (Processo*)malloc(sizeof(Processo));
    if (novo == NULL) 
    {
        printf("Erro ao alocar Processo.\n");
        exit(1);
    }
    //CHECK NULL OK

    strncpy(novo->nome, nome, MAX_NOME);
    novo->nome[MAX_NOME - 1] = '\0'; // Garantir terminação
    novo->id = -1; // ID do processo, pode ser atribuído depois
    novo->tipo = tipo;
    novo->prioridade = prioridade;
    novo->inicio = inicio;
    novo->duracao = duracao;
    novo->estado = estado;
    novo->lido = 1;

    return novo;
}

void exibe_dados(Processo* p)
{
    if (p == NULL)
    {
        return;
    }
    if (p->tipo == PRIORITY)
        printf("Processo: %d, Nome: %s, Tipo: PRIORIDADE, Prioridade: %d ", p->id, p->nome, p->prioridade);
    else if (p->tipo == REAL_TIME)
        printf("Processo: %d, Nome: %s, Tipo: REAL TIME, Inicio: %d, Fim: %d ", p->id, p->nome, p->inicio, p->duracao + p->inicio);
    else
        printf("Processo: %d, Nome: %s, Tipo: ROUND ROBIN ", p->id, p->nome);

    if (p->estado == waiting)
        printf("Estado: WAITING\n\n");
    else
        printf("Estado: RUNNING\n\n");
}