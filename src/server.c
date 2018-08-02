#include "libs/udp_server.h"

int main () {

    struct CONFIG config;
    int e, sockfd;                                              //e - error checker(not implemented), sockfd - socket file descriptor
    struct sockaddr_in clientaddr;                              
    char incomeMsg[MAXBUFLEN], outcomeMsg[MAXBUFLEN];
    char * output;                                              //moze sa dynamicky menit v processData()? // not implemented

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

        //processData(incomeMsg, output, outcomeMsg);           //not implemented

        printf("%s", incomeMsg);

        //snd(sockfd, outcomeMsg, clientaddr);                  //not implemented

    }

    return 0;
}
