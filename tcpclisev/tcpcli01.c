#include "unp.h"

int
main(int argc, char** argv) {
    int     sockfd;
    struct sockaddr_in servaddr;
    
    if (argc != 2) {
        err_quit("usage: tcpcli<IPAddress>");
    }

    sockfd = Socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(9997);
    Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

    Connect(sockfd, (SA*) &servaddr, sizeof(servaddr));
    str_cli(stdin, sockfd);
    Close(sockfd);
    exit(0);
}