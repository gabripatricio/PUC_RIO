#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/msg.h>
#include <sys/wait.h>

#define MSG_COUNT 32

struct msgbuf {
    long mtype;
    int valor;
};

void produtor(int msgid) {
    struct msgbuf msg;
    msg.mtype = 1;

    for (int i = 0; i < MSG_COUNT; i++) {
        msg.valor = i;
        if (msgsnd(msgid, &msg, sizeof(int), 0) == -1) {
            perror("msgsnd");
            exit(1);
        }
        printf("[PRODUTOR] Enviou: %d\n", msg.valor);
        // aguarda sinalização... poderia usar wait)
        sleep(1);
    }
}

void consumidor(int msgid) {
    struct msgbuf msg;

    for (int i = 0; i < MSG_COUNT; i++) {
        if (msgrcv(msgid, &msg, sizeof(int), 0, 0) == -1) {
            perror("msgrcv");
            exit(1);
        }
        printf("[CONSUMIDOR] Recebeu: %d\n", msg.valor);
        sleep(1);
    }
}

int main() {
    int msgid = msgget(IPC_PRIVATE, IPC_CREAT | 0666);
    if (msgid == -1) 
    {
        perror("msgget");
        exit(1);
    }

    pid_t pid = fork();
    if (pid == 0) 
    {
        consumidor(msgid);
        exit(0);
    } 
    else 
    {
        produtor(msgid);
        wait(NULL);
        msgctl(msgid, IPC_RMID, NULL);
    }

    return 0;
}