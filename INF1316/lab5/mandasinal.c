#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

#define ID_PROCESSO 8981

// ps aux | grep <NOME_PROCESSO>

/*
exemplo:
ps aux | grep ex2

gabripa+   *13957* 99.9  0.0   2680  1280 pts/0    R+   17:46   4:48 ./ex2
gabripa+   14086  0.0  0.0   9284  2304 pts/1    S+   17:51   0:00 grep --color=auto ex2

LOGO, O PID EH 13957

*/

int main(void)
{
    for (int i = 0; i < 1000; i++){
        int v = kill(ID_PROCESSO, SIGINT);
        if (!v)
            printf("O sinal foi enviado ao processo %d\n", ID_PROCESSO);
    }
    return 0;
}