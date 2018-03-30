#include "unp.h"


void
str_echo(int sockfd) {
    char    buff[MAXLINE];
    ssize_t n;
again:
    while((n = read(sockfd, buff, MAXLINE)) > 0) {
        Writen(sockfd, buff, n);
    }

    if(n < 0 && errno == EINTR)
        goto again;
    else if (n < 0) {
        err_sys("str_echo: read error");
    }
}


