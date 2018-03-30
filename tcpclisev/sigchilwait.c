#include "unp.h"


void
signal_wait(int signo){
    pid_t   pid;
    int     stat;

    pid = wait(&stat);
    printf("child %d terminated\n", pid);
    return;
}
