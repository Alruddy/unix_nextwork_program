#include "unp.h"

void sig_chldwaitpid(int signo);

int
main(int argc, char** argv) {
    int     listenfd, connfd;
    pid_t   childpid;
    struct sockaddr_in servaddr, clieaddr;
    socklen_t   clielen;

    listenfd = Socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(9997);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    Bind(listenfd, (SA*) &servaddr, sizeof(servaddr));

    Listen(listenfd, LISTENQ);
    Signal(SIGCHLD, sig_chldwaitpid);
    for ( ; ; ) {
        clielen = sizeof(clieaddr);
        connfd = Accept(listenfd, (SA *)&clieaddr, &clielen);

        if ((childpid = Fork()) == 0) {
            Close(listenfd);
            str_echo(connfd);
            Close(connfd);
            exit(0);
        }
        Close(connfd);
    }
}
