//GABRIEL PATRICIO 2310806
//GABRIEL MARTINS 2311271

#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <time.h>
#include "processo.h"

// funcoes do grupo lista
Lista *cria_lista(void);
Lista *insere_lista(Lista *lista, Processo *p);
Lista *insere_final(Lista *lista, Processo *p);
Lista *lista_remove(Lista *lista, Processo *p);
void exibe_lista(Lista *l);
int lista_vazia(Lista *lista);

// funcoes de escalonamento
void round_robin_scheduling(Lista **lista);
int real_time_scheduling(Lista **lista);
int priority_scheduling(Lista **lista);
Processo *buscar_processo_real_time_para_executar(Lista *lista, int segundos_atuais);

// Gerenciamento de processos
void iniciar_processo(Processo *p);
void parar_processo(Processo *p);
void rodar_processo(Processo *p);
Processo *rodando_atualmente(Lista *real_time, Lista *prioridade, Lista *round_robin);
int houve_preempcao(Processo *atual, Processo *anterior);

// funcoes para horario
int mostra_hora(void);
int mostrar_segundos(void);

#define VAZIA 0
#define F_TEMPO 1
#define TO_DECIDINDO 69

int main(int argc, char *argv[])
{

    if (argc < 2)
    {
        // CHECK NULO OK
        fprintf(stderr, "Uso: %s <shmid>\n", argv[0]);
        exit(1);
    }

    // Testando a memoria compartilhada
    int shmid = atoi(argv[1]);
    Processo *shmp = shmat(shmid, NULL, 0);
    if (shmp == (Processo *)-1)
    {
        // CHECK NULO OK
        perror("shmat");
        exit(1);
    }
    printf("Memoria compartilhada: %p\n", (void *)shmp);

    // nossa estrategia: criar uma fila para cada tipo

    Lista *fila_prioridade = cria_lista();
    Lista *fila_round_robin = cria_lista();
    Lista *fila_real_time = cria_lista();
    // CHECK

    mostra_hora(); // CHECK NULO OK
    printf("------------------------------------------------------------------------------------------------\n\n");

    printf("Inicializando o escalonador:\n\n\n\n");

    int rts;
    while (true)
    {
        if (shmp->lido == 1)
        {
            Processo *shmp = shmat(shmid, NULL, 0);
            if (shmp == (Processo *)-1)
            {
                // CHECK NULO OK
                perror("[DEBUG] SHMP @ ESCALONADOR\n");
                exit(1);
            }
            Processo *novo = criaProcesso(shmp->nome, shmp->tipo, shmp->prioridade, shmp->inicio, shmp->duracao, shmp->estado);
            shmp->lido = 2;
            novo->lido = 2;
            iniciar_processo(novo);//CHECK NULL OK

            if (novo->tipo == PRIORITY)
            {
                fila_prioridade = insere_lista(fila_prioridade, novo);
                //CHECK NULL OK
            }
            else if (novo->tipo == ROUND_ROBIN)
            {
                fila_round_robin = insere_lista(fila_round_robin, novo);
            }
            else
            {
                fila_real_time = insere_lista(fila_real_time, novo);
            }
        }
        

        rts = real_time_scheduling(&fila_real_time);
        if (rts == VAZIA || rts == F_TEMPO)
        {
            if (lista_vazia(fila_prioridade) == false)
                priority_scheduling(&fila_prioridade);
            else
            {
                round_robin_scheduling(&fila_round_robin);
            }
            mostra_hora();
        }   
    }

        // Detach na memoria compartilhada
        if (shmdt(shmp) == -1)
        {
            perror("shmdt");
            exit(1);
        }
        printf("Memoria compartilhada desanexada.\n");

        return 0;
    }

Lista *cria_lista(void)
{
    return NULL;
}

Lista *insere_lista(Lista *lista, Processo *p)
{
    if (p == NULL)
    {
        return lista;
    }

    Lista *novo = (Lista *)malloc(sizeof(Lista));
    if (novo == NULL)
    {
        printf("Erro no malloc. Abortando programa.\n");
        exit(1);
    }

    novo->processo = p;
    novo->proximo = NULL;

    if (p->tipo == PRIORITY)
    {
        if (lista == NULL || lista->processo == NULL || lista->processo->prioridade > p->prioridade)
        {
            novo->proximo = lista;
            return novo;
        }

        Lista *atual = lista;
        while (atual->proximo != NULL &&
               atual->proximo->processo != NULL &&
               atual->proximo->processo->prioridade <= p->prioridade)
        {
            atual = atual->proximo;
        }

        novo->proximo = atual->proximo;
        atual->proximo = novo;
        return lista;
    }
    else if (p->tipo == REAL_TIME)
    {
        if (p->inicio + p->duracao > 60)
        {
            printf("O processo %s com id %d nao pode ser adicionado por ter inicio mais duração > 60\n", p->nome, p->id);
            free(novo);
            return lista;
        }

        Lista *aux = lista;
        while (aux != NULL)
        {
            if (aux->processo == NULL)
            {
                aux = aux->proximo;
                continue;
            }

            int ini1 = p->inicio;
            int fim1 = ini1 + p->duracao;

            int ini2 = aux->processo->inicio;
            int fim2 = ini2 + aux->processo->duracao;

            if (!(fim1 <= ini2 || fim2 <= ini1))
            {
                printf("Conflito detectado!\n");
                printf("Nao conseguimos inserir o processo %s com id = %d na lista de real-time, devido a um conflito com o processo %s com id = %d\n",
                       p->nome, p->id, aux->processo->nome, aux->processo->id);
                printf("Intervalo [%d, %d) conflita com [%d, %d)\n", ini1, fim1, ini2, fim2);
                printf("Vamos aniquilar o processo mais recente\n");
                free(novo);
                return lista;
            }

            aux = aux->proximo;
        }

        if (lista == NULL || lista->processo == NULL || lista->processo->inicio > p->inicio)
        {
            novo->proximo = lista;
            return novo;
        }

        Lista *atual = lista;
        while (atual->proximo != NULL &&
               atual->proximo->processo != NULL &&
               atual->proximo->processo->inicio <= p->inicio)
        {
            atual = atual->proximo;
        }

        novo->proximo = atual->proximo;
        atual->proximo = novo;
        return lista;
    }
    else
    {
        // ROUND ROBIN
        if (lista == NULL)
        {
            return novo;
        }

        Lista *atual = lista;
        while (atual->proximo != NULL)
        {
            atual = atual->proximo;
        }

        atual->proximo = novo;
        return lista;
    }
}

void exibe_lista(Lista *lista)
{
    printf("\n\n\n");
    printf("==========================================================================================\n");
    while (lista != NULL)
    {
        exibe_dados(lista->processo);
        lista = lista->proximo;
    }
    printf("==========================================================================================");
    printf("\n\n\n");
}

int lista_vazia(Lista *l)
{
    if (l == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

Lista *insere_final(Lista *lista, Processo *p)
{
    Lista *novo = (Lista *)malloc(sizeof(Lista));

    if (novo == NULL)
    {
        printf("Erro no malloc. Abortando programa.\n");
        exit(1);
    }

    novo->processo = p;
    novo->proximo = NULL;

    if (lista == NULL)
    {
        return novo;
    }

    Lista *atual = lista;
    while (atual->proximo != NULL)
    {
        atual = atual->proximo;
    }
    atual->proximo = novo;
    return lista;
}

Lista *lista_remove(Lista *lista, Processo *processo)
{
    Lista *atual = NULL;
    Lista *anterior = NULL;
    for (atual = lista; atual != NULL && atual->processo->id != processo->id; atual = atual->proximo)
    {
        anterior = atual;
    }

    if (atual == NULL) // nao existe
    {
        return lista;
    }

    if (anterior == NULL) // primeiro elemento
    {
        lista = atual->proximo;
    }
    else
    {
        anterior->proximo = atual->proximo;
    }
    free(atual);
    return lista;
}

void iniciar_processo(Processo *p)
{
    //CHECK NULL OK
    if (p == NULL)
    {
        return;
    }
    pid_t f = fork();
    if (f < 0)
    {
        perror("Erro no fork");
        exit(1);
    }
    else if (f == 0)
    {
        char caminho[100];
        snprintf(caminho, sizeof(caminho), "./%s", p->nome);
        char *args[] = {caminho, NULL};

        execvp(args[0], args);
        perror("Erro no execvp");
        exit(1);
    }
    else
    {
        p->id = f;
        p->estado = waiting;
        kill(f, SIGSTOP); // para iniciar o processo pausado
    }
}

void rodar_processo(Processo *p)
{
    kill(p->id, SIGCONT);
    p->estado = running;
    printf("===========================================================================================\n");
    exibe_dados(p);
}

void parar_processo(Processo *p)
{
    kill(p->id, SIGSTOP);
    p->estado = waiting;
}

void round_robin_scheduling(Lista **lista)
{
    if (*lista == NULL || lista_vazia(*lista))
    {
        return;
    }

    Processo *p = (*lista)->processo;
    rodar_processo(p);
    sleep(TIME_QUANTUM);
    parar_processo(p);

    *lista = lista_remove(*lista, p);
    *lista = insere_final(*lista, p);
}

int priority_scheduling(Lista **lista)
{
    if (lista == NULL || *lista == NULL || (*lista)->processo == NULL)
    {
        return VAZIA;
    }

    Processo *p = (*lista)->processo;

    rodar_processo(p);
    sleep(TIME_QUANTUM);
    parar_processo(p);

    p->duracao++; // incrementa "ticks executados"

    if (p->duracao >= 3)
    {
        printf("Processo %s (PID = %d) completou 3 segundos. Removendo da fila.\n", p->nome, p->id);
        kill(p->id, SIGKILL);             // mata o processo
        *lista = lista_remove(*lista, p); // remove da fila
    }
    else
    {
        *lista = lista_remove(*lista, p);
        *lista = insere_lista(*lista, p);
    }
    return TO_DECIDINDO;
}

// Retorna o processo que deve rodar agora, ou NULL se nenhum
Processo *buscar_processo_real_time_para_executar(Lista *lista, int segundos_atuais)
{
    while (lista != NULL)
    {
        Processo *p = lista->processo;
        if (p->inicio == segundos_atuais)
        {
            return p;
        }
        lista = lista->proximo;
    }
    return NULL;
}

int real_time_scheduling(Lista **lista)
{
    if (lista == NULL || *lista == NULL)
    {
        return VAZIA;
    }

    time_t tempo_atual = time(NULL);
    if (tempo_atual == (time_t)-1)
    {
        perror("Erro ao obter o tempo");
        return -1;
    }

    struct tm *tempo_local = localtime(&tempo_atual);
    if (tempo_local == NULL)
    {
        perror("Erro na conversao do tempo");
        return -1;
    }

    int segundos_atuais = tempo_local->tm_sec;

    Processo *p = buscar_processo_real_time_para_executar(*lista, segundos_atuais);

    if (p == NULL)
    {
        return F_TEMPO; // Nenhum processo para rodar nesse segundo
    }

    printf("Processo %s (PID = %d) rodando REAL-TIME no segundo %d.\n", p->nome, p->id, segundos_atuais);

    rodar_processo(p);
    for (int i = 0; i < p->duracao; i++)
    {
        sleep(TIME_QUANTUM);
    }
    parar_processo(p);

    printf("Processo %s (PID = %d) finalizou execução real-time por %d segundos.\n", p->nome, p->id, p->duracao);

    return TO_DECIDINDO;
}

Processo *rodando_atualmente(Lista *real_time, Lista *prioridade, Lista *round_robin)
{
    if (real_time != NULL && real_time->processo != NULL)
    {
        Processo *rt = real_time->processo;
        if (rt->estado == running)
        {
            return rt;
        }
    }

    if (prioridade != NULL && prioridade->processo != NULL)
    {
        Processo *pr = prioridade->processo;
        if (pr->estado == running)
        {
            return pr;
        }
    }

    if (round_robin != NULL && round_robin->processo != NULL)
    {
        Processo *rr = round_robin->processo;
        if (rr->estado == running)
        {
            return rr;
        }
    }
    return NULL;
}

int houve_preempcao(Processo *atual, Processo *anterior)
{
    if (atual == NULL || anterior == NULL)
    {
        return false;
    }

    if (atual->id != anterior->id)
    {
        printf("Houve preempcao.\n");
        printf("Processo antigo: \n");
        exibe_dados(anterior);
        printf("Processo novo\n");
        exibe_dados(atual);
        return true;
    }
    return false;
}

int mostra_hora(void)
{
    // CHECK - NULOS
    time_t tempo_atual = time(NULL);
    if (tempo_atual == ((time_t)-1))
    {
        perror("Erro ao obter o tempo!\n");
        return -1;
    }

    printf("HORARIO ATUAL:\n");
    printf("Data e hora: %s", ctime(&tempo_atual));
    return 0;
}

int mostrar_segundos(void)
{
    time_t tempo_atual = time(NULL);
    if (tempo_atual == (time_t)-1)
    {
        perror("Erro ao obter o tempo");
        return -1;
    }

    struct tm *tempo_local = localtime(&tempo_atual);
    if (tempo_local == NULL)
    {
        perror("Erro na conversao do tempo");
        return -1;
    }

    int segundos_atuais = tempo_local->tm_sec;

    printf("Segundos atuais: %d.\n", segundos_atuais);
    return segundos_atuais;
}