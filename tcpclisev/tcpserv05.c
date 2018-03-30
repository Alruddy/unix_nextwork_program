#include "unp.h"

int
main(int argc, char** argv) {
    int i, maxi, maxfdp1, nready, connfd, listenfd, sockfd;
    int client[FD_SETSIZE];
    char buff[MAXLINE];
    ssize_t n;
    struct sockaddr_in servaddr, clientaddr;
    socklen_t clientlen;
    fd_set rset, allset;
    
    printf("%d\n", FD_SETSIZE);
    listenfd = Socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(9997);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    Bind(listenfd, (SA*) &servaddr, sizeof(servaddr));
    Listen(listenfd, LISTENQ);

    FD_ZERO(&allset);
    FD_SET(listenfd, &allset);
    for (i = 0; i < FD_SETSIZE; i++) {
        client[i] = -1;
    }
    maxfdp1 = listenfd;
    maxi = -1;
    for ( ; ; ) {
        rset = allset;
        nready = Select(maxfdp1+1, &rset, NULL, NULL, NULL);

        if (FD_ISSET(listenfd, &rset)) {
            clientlen = sizeof(clientaddr);
            connfd = Accept(listenfd, (SA *) &clientaddr, &clientlen);

            for(i = 0; i < FD_SETSIZE; i++) {
                if (client[i] < 0) {
                    client[i] = connfd;
                    break;
                }
            }
            if(i == FD_SETSIZE) {
                err_quit("too many client");
            }
            
            FD_SET(connfd, &allset);
            if (connfd > maxfdp1) {
                maxfdp1 = connfd;
            }
            if(maxi < i) {
                maxi = i;
            }

            if (--nready <= 0) {
                continue;
            }

        }

        for (i = 0; i <= maxi; i++) {
            if ((sockfd = client[i]) < 0) {
                continue;
            }

            if (FD_ISSET(sockfd, &rset))
            {
                if ((n = Read(sockfd, buff, MAXLINE)) == 0)
                {
                    Close(sockfd);
                    FD_CLR(sockfd, &allset);
                    client[i] = -1;
                } else {
                    Writen(sockfd, buff, n);
                }
                if (--nready <= 0) {
                    break;
                }
            }
        }
    }
}
