#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define TAM 10000
#define TRABALHADORES 10

int v[TAM];

void* trabalhador(void* arg) {
    for (int i = 0; i < TAM; i++) {
        v[i] *= 2;
        v[i] += 2;
    }
    return NULL;
}

int main() {
    pthread_t threads[TRABALHADORES];

    for (int i = 0; i < TAM; i++) {
        v[i] = 10;
    }

    for (int i = 0; i < TRABALHADORES; i++) {
        pthread_create(&threads[i], NULL, trabalhador, NULL);
    }

    for (int i = 0; i < TRABALHADORES; i++) {
        pthread_join(threads[i], NULL);
    }

    int verifica = 1;
    for (int i = 1; i < TAM; i++) {
        if (v[i] != v[0]) {
            verifica = 0;
            break;
        }
    }

    if (verifica) {
        printf("Todas as posicoes sao iguais. Valor = %d\n", v[0]);
    } else {
        printf("As posicoes sao diferentes\n");
    }

    return 0;
}