#include "udp_server.h"

int run_srv(struct CONFIG config, int * sockfd){

    //TODO: error check

    *sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(config.PORT);
    servaddr.sin_addr.s_addr = inet_addr(config.HOST_IP);

    if (bind(*sockfd, (struct sockaddr *)&servaddr, (socklen_t) sizeof(servaddr))) {
        handle_error("bind");
    }

    printf("Server is running, waiting for connections\n");

    return 0;
}

int rcv(int sockfd, char * income, struct sockaddr_in * clientaddr){

    //TODO: error check

    ssize_t msgLen;
    int n = sizeof(*clientaddr);
    msgLen = recvfrom(sockfd, income, MAXBUFLEN, 0, (struct sockaddr*)clientaddr, &n);
    income[msgLen] = '\0';
    printf("%s\n", income);
    
    return 0;
}


int processData(){
    //TODO: implement
    return 0;
}

int snd(){   //"send()"
    //TODO: implement
    return 0;
}
