#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <unistd.h>
#include "processo.h"

#define MAX_LINE 100

Processo* le_linha(const char* linha); 

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Uso: %s <shmid>\n", argv[0]);
        exit(1);
    }

    // Attach na memoria compartilhada
    int shmid = atoi(argv[1]);
    Processo* shmp = shmat(shmid, NULL, 0);
    if (shmp == (Processo*)-1) {
        perror("shmat");
        exit(1);
    }
    printf("Memoria compartilhada: %p\n", (void *)shmp);

    // Leitura do arquivo exec.txt
    FILE* arquivo = fopen("exec.txt", "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }
    char linha[MAX_LINE];

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        while (shmp->lido == 1) {
            usleep(1000);  // espera até o escalonador liberar
        }
        
        // Processa a linha lida
        Processo* p = le_linha(linha);
        memcpy(shmp, p, sizeof(Processo));  // copia struct inteira para shm
        free(p);
        
        sleep(1); //Le uma linha de 1 em 1 segundo
    }

    //Fechando o arquivo
    fclose(arquivo);
    printf("Arquivo exec.txt lido com sucesso.\n");

    // Detach na memoria compartilhada
    if (shmdt(shmp) == -1) {
        perror("shmdt");
        exit(1);
    }
    printf("Memoria compartilhada desanexada.\n");
    return 0;
}

Processo* le_linha(const char *linha) {
    char nome[32];
    int prioridade, inicio, duracao;
    Processo* p;

    if (strstr(linha, "P=")) {
        sscanf(linha, "Run %s P=%d", nome, &prioridade);
        printf("PRIORIDADE → nome: %s | prioridade: %d\n", nome, prioridade);
        p = criaProcesso(nome, PRIORITY, prioridade, -1, 0, waiting);
    } else if (strstr(linha, "I=") && strstr(linha, "D=")) {
        sscanf(linha, "Run %s I=%d D=%d", nome, &inicio, &duracao);
        printf("REAL-TIME → nome: %s | inicio: %d | duracao: %d\n", nome, inicio, duracao);
        p = criaProcesso(nome, REAL_TIME, -1, inicio, duracao, waiting);
    } else {
        sscanf(linha, "Run %s", nome);
        printf("ROUND-ROBIN → nome: %s\n", nome);
        p = criaProcesso(nome, ROUND_ROBIN, -1, -1, 0, waiting);
    }

    return p;
}