#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#define TAM 10000
#define TRABALHADORES 10

int v[TAM];
int soma[TRABALHADORES];

void* trabalhador(void* arg) {
    int id = *(int*)arg;
    int inicio = id * (TAM / TRABALHADORES);
    int fim = (id + 1) * (TAM / TRABALHADORES);
    int soma_parcial = 0;

    for (int i = inicio; i < fim; i++) {
        v[i] *= 2;
        soma_parcial += v[i];
    }

    soma[id] = soma_parcial;
    free(arg);
    return NULL;
}

int main() {
    pthread_t threads[TRABALHADORES];
    struct timeval inicio, fim;

    for (int i = 0; i < TAM; i++) {
        v[i] = 10;
    }

    gettimeofday(&inicio, NULL);

    for (int i = 0; i < TRABALHADORES; i++) {
        soma[i] = 0;
        int* id = malloc(sizeof(int));
        *id = i;
        pthread_create(&threads[i], NULL, trabalhador, id);
    }

    for (int i = 0; i < TRABALHADORES; i++) {
        pthread_join(threads[i], NULL);
    }

    gettimeofday(&fim, NULL);

    long tempo_us = (fim.tv_sec - inicio.tv_sec) * 1000000L + (fim.tv_usec - inicio.tv_usec);

    for (int i = 0; i < TRABALHADORES; i++) {
        printf("Soma[%d]: %d\n", i, soma[i]);
    }

    printf("Tempo de execucao: %.3f ms\n", tempo_us / 1000.0);

    return 0;
}