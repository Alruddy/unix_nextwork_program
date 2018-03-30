#include "unp.h"
#include <limits.h>
#define OPEN_MAX (1024)
int
main(int argc, char** argv) {
    int i, maxi, connfd, listenfd, sockfd;
    int nready;
    ssize_t n;
    struct sockaddr_in servaddr, clientaddr;
    char buff[MAXLINE];
    struct pollfd client[OPEN_MAX];
    socklen_t   clientlen;

    listenfd = Socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(9997);

    Bind(listenfd, (SA*) &servaddr, sizeof(servaddr));
    Listen(listenfd, LISTENQ);

    for(i = 1; i < OPEN_MAX; i++) {
        client[i].fd = -1;
    }

    client[0].fd = listenfd;
    client[0].events = POLLRDNORM;
    maxi = 0;

    for ( ; ; ) {
        nready = Poll(client, maxi+1, 0);

        if (client[0].revents & POLLRDNORM) {
            clientlen = sizeof(clientaddr);
            connfd = Accept(listenfd, (SA*) &clientaddr, &clientlen);
            for(i = 0; i < OPEN_MAX; i++){
                if(client[i].fd < 0) {
                    client[i].fd = connfd;
                    client[i].events = POLLRDNORM;
                    break;
                }
            }
            if (i == OPEN_MAX) {
                err_quit("too many clients");
            }

            if (i > maxi) {
                maxi = i;
            }

            if(--nready <= 0) {
                continue;
            }
        }

        for (i = 1; i <= maxi; i++) {
            if ((sockfd = client[i].fd) < 0) {
                continue;
            }

            if ((n = Read(sockfd, buff, MAXLINE)) < 0) {
                if (errno == ECONNRESET)
                {
                    Close(sockfd);
                    client[i].fd = -1;
                } else {
                    err_sys("read error");
                }
            } else if (n == 0) {
                Close(sockfd);
                client[i].fd = -1;
            } else {
                Writen(sockfd, buff, n);
            }

            if (--nready <= 0)
            {
                break;
            }
        }
    }
}
