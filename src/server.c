#include "libs/headers/udp_server.h"

int main () {

    struct CONFIG config;
    int e, sockfd;                                              //e - error checker(not implemented), sockfd - socket file descriptor
    struct sockaddr_in clientaddr;                              
    char *incomeMsg, *outcomeMsg;
    char * output;                                              //moze sa dynamicky menit v processData()? // not implemented

    incomeMsg = (char *)malloc(sizeof(char) * MAXBUFLEN);
    outcomeMsg = (char *)malloc(sizeof(char) * MAXBUFLEN);

    //load and verify config file
    if ( (e = load_config("config/server.cfg", &config) ) != 0){
        exit(EXIT_FAILURE);
    }
    print_CONFIG(config);
    
    //creates socket file descriptor and realizes bind
    run_srv(config, &sockfd);

    for(;;){

        //recieve from client, set clientaddr
        rcv(sockfd, incomeMsg, &clientaddr);

        printf("%s\n", incomeMsg);

        snd(sockfd, "OK", &clientaddr);

    }

    return 0;
}
