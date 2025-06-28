#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>

#define MAX_MSG 256
#define BUFFER_SIZE 64

struct msgbuf {
    long mtype;
    int valor;
};

void produtor(int msgid) {
    struct msgbuf msg;
    msg.mtype = 1;

    for (int i = 0; i < MAX_MSG; i++) {
        msg.valor = i;
        if (msgsnd(msgid, &msg, sizeof(int), 0) == -1) {
            perror("msgsnd");
            exit(1);
        }
        printf("[PRODUTOR] Enviou: %d\n", msg.valor);
        sleep(1);
    }
}

void consumidor(int msgid, int id, int delay) {
    struct msgbuf msg;
    int count = 0;

    while (count < MAX_MSG) {
        if (msgrcv(msgid, &msg, sizeof(int), 0, 0) == -1) {
            perror("msgrcv");
            exit(1);
        }
        printf("[CONSUMIDOR %d] Recebeu: %d\n", id, msg.valor);
        count++;
        sleep(delay);
    }
}

int main() {
    int msgid = msgget(IPC_PRIVATE, IPC_CREAT | 0666);

    if (msgid == -1) 
    {
        perror("msgget");
        exit(1);
    }

    pid_t p1 = fork();
    if (p1 == 0) 
    {
        produtor(msgid);
        exit(0);
    }

    pid_t p2 = fork();
    if (p2 == 0) 
    {
        consumidor(msgid, 1, 1);
        exit(0);
    }

    pid_t p3 = fork();
    if (p3 == 0) 
    {
        consumidor(msgid, 2, 2);
        exit(0);
    }

    wait(NULL);
    wait(NULL);
    wait(NULL);

    msgctl(msgid, IPC_RMID, NULL);
    return 0;
}