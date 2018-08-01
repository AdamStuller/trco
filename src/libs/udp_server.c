#include "udp_server.h"

int run_srv(struct CONFIG config, int * sockfd){

    if ( (*sockfd = socket(AF_INET, SOCK_DGRAM, 0)) != 0) {
        handle_error("socket");
    }

    struct sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(config.PORT);
    servaddr.sin_addr.s_addr = inet_addr(config.HOST_IP);

    if (bind(sockfd, (struct sockaddr *)&servaddr, (socklen_t) sizeof(servaddr))) {
        handle_error("bind");
    }

    return 0;
}

int rcv(int sockfd, char * income){

    //TODO: error check

    ssize_t msgLen;
    struct sockaddr_in clientaddr;
    int n = sizeof(clientaddr);
    msgLen = recvfrom(sockfd, *income, sizeof(*income), 0, (struct sockaddr*)&clientaddr, &n);
    *income[msgLen] = '\0';
    printf("%s\n", *income);
    return 0;
}


int processData(){
    //TODO
    return 0;
}

int snd(){
    //TODO
    return 0;
}
