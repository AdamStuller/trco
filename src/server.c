#include "libs/headers/udp_protocol.h"

int main (int argc, char *argv[]) {

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
    run(config, &sockfd, 0);
    
    for(;;){

        //recieve from client, set clientaddr
        if (rcv(sockfd, incomeMsg, &clientaddr) != 0) {
            // error case
        }

        printf("%s\n", incomeMsg);
    
        if (snd(sockfd, "OKs\0", &clientaddr) != 0) {
            // error case
        }
    }


    free(incomeMsg);
    free(outcomeMsg);
    
    return 0;
}
