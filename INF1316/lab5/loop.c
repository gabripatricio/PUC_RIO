#include <stdio.h>
#include <unistd.h>
#include <signal.h>


int main(void)
{
    while(1)
    {
        printf("Loop rodando! PID: %d\n", getpid());
        sleep(1); // so para nao ficar printando igual louco
    }
    return 0;
}
