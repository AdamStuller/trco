#include "libs/headers/udp_protocol.h"
#include "libs/headers/format.h"

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
    run(config, &sockfd, SERVER_SIDE);
    
    FILE * log_data = fopen(config.DAT_FILE, "a+"); 
    if (log_data == NULL) {
        perror("Cannot open Data file.\n");
        exit(EXIT_FAILURE);
    }
    
    printf("DATA FILE %s OPENED.\n", config.DAT_FILE);

    for(;;){

        //recieve from client, set clientaddr
        if (rcv(sockfd, incomeMsg, &clientaddr) != 0) {
            // error case
            perror("rcv Failed\n");
        } else {
            char * formated_str = format(incomeMsg, strlen(incomeMsg), 5);
            if (formated_str == NULL) {
                // error occured, malformed message, cannot be saved
                snd(sockfd, "Malformed message", &clientaddr);    
            } else {
                fprintf(log_data, "%s\n", formated_str);
                free(formated_str);
                fflush(log_data);
            }
        }

        printf("%s\n", incomeMsg);
    
        if (snd(sockfd, "OKs", &clientaddr) != 0) {
            // error case
        } else {
            ;
        }
    }


    free(incomeMsg);
    free(outcomeMsg);
    fclose(log_data);
    return 0;
}
