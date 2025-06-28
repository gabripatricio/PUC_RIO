#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <time.h>

#define BUFFER_SIZE 64
#define MAX_MESSAGES 256

// Struct que vai na memória compartilhada
typedef struct {
    int buffer[BUFFER_SIZE];
    int in, out;
    int total_produced;
    int total_consumed;
} SharedData;

// Operações para semáforo (P = down, V = up)
void sem_op(int semid, int semnum, int op) {
    struct sembuf sb = { semnum, op, 0 };
    semop(semid, &sb, 1);
}

// Função do produtor
void produtor(SharedData* data, int semid) {
    while (1) {
        sem_op(semid, 0, -1); // empty
        sem_op(semid, 2, -1); // mutex

        if (data->total_produced >= MAX_MESSAGES) {
            sem_op(semid, 2, 1); // libera mutex
            sem_op(semid, 1, 1); // libera full para desbloquear consumidor
            break;
        }

        int msg = data->total_produced + 1;
        data->buffer[data->in] = msg;
        data->in = (data->in + 1) % BUFFER_SIZE;
        data->total_produced++;

        printf("[Produtor] Gerou %d (total: %d)\n", msg, data->total_produced);
        fflush(stdout);

        sem_op(semid, 2, 1); // mutex
        sem_op(semid, 1, 1); // full

        sleep(1);
    }
    exit(0);
}

// Função do consumidor
void consumidor(SharedData* data, int semid, int id, int delay) {
    while (1) {
        sem_op(semid, 1, -1); // full
        sem_op(semid, 2, -1); // mutex

        if (data->total_consumed >= MAX_MESSAGES) {
            sem_op(semid, 2, 1); // mutex
            sem_op(semid, 1, 1); // libera outro consumidor se estiver preso
            break;
        }

        int msg = data->buffer[data->out];
        data->out = (data->out + 1) % BUFFER_SIZE;
        data->total_consumed++;

        printf("[Consumidor %d] Recebeu %d (total: %d)\n", id, msg, data->total_consumed);
        fflush(stdout);

        sem_op(semid, 2, 1); // mutex
        sem_op(semid, 0, 1); // empty

        sleep(delay);
    }
    exit(0);
}

int main() {
    key_t shmkey = ftok(".", 'x');
    int shmid = shmget(shmkey, sizeof(SharedData), IPC_CREAT | 0666);
    SharedData* data = (SharedData*) shmat(shmid, NULL, 0);

    data->in = data->out = 0;
    data->total_produced = data->total_consumed = 0;

    key_t semkey = ftok(".", 's');
    int semid = semget(semkey, 3, IPC_CREAT | 0666);

    // Semáforos: [0] empty, [1] full, [2] mutex
    semctl(semid, 0, SETVAL, BUFFER_SIZE); // empty
    semctl(semid, 1, SETVAL, 0);           // full
    semctl(semid, 2, SETVAL, 1);           // mutex

    pid_t p1 = fork();
    if (p1 == 0) produtor(data, semid);

    pid_t p2 = fork();
    if (p2 == 0) consumidor(data, semid, 1, 1);

    pid_t p3 = fork();
    if (p3 == 0) consumidor(data, semid, 2, 2);

    wait(NULL); wait(NULL); wait(NULL);

    printf("\n--- Fim da Execução ---\n");
    printf("Total produzido: %d\n", data->total_produced);
    printf("Total consumido: %d\n", data->total_consumed);

    shmdt(data);
    shmctl(shmid, IPC_RMID, NULL);
    semctl(semid, 0, IPC_RMID);

    return 0;
}