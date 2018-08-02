/*
    udp_server.c provides all functions required to run communication server trough UDP.
    This source file provides only simple functions for creating file descriptor and bind int to a socket,
    recieve and send raw messages to client.
*/
#include "headers/udp_server.h"


/*
    creates file descriptor and passes it through arg1 - int * sockfd.
    Properly loaded config file needed to succesfull run.
*/
int run_srv(struct CONFIG config, int * sockfd){

    //TODO: error check

    *sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(config.PORT);
    servaddr.sin_addr.s_addr = inet_addr(config.HOST_IP);

    if (bind(*sockfd, (struct sockaddr *)&servaddr, (socklen_t) sizeof(servaddr)) == -1) {
        handle_error("bind");
    }

    printf("Server is running, waiting for connections\n");

    return 0;
}

/*
    recieve function writes raw income message into arg1,
    sets client address into arg2
*/
int rcv(int sockfd, char * income, struct sockaddr_in * clientaddr){
    ssize_t msgLen;
    int n = sizeof(*clientaddr);
    msgLen = recvfrom(sockfd, income, MAXBUFLEN - 1, 0, (struct sockaddr*)clientaddr, &n);    
    if (msgLen == -1) {
        perror("recvfrom");
        income = NULL;
        return -1;
    }
    
    income[msgLen] = '\0';

    return 0;
}

/*
    sends raw message to client
*/
int snd(int sockfd, char * outcomeMsg, struct sockaddr_in *clientaddr){ 

    if (sendto(sockfd, outcomeMsg, MAXBUFLEN, 0, (struct sockaddr*)clientaddr, sizeof(*clientaddr)) == -1) {
        perror("sendto");
        return -1;
    }
    return 0;
}
