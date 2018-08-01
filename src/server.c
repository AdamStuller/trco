#include "libs/udp_server.h"
// #include "libs/config.h"

int main () {

    struct CONFIG config;
    int e, sockfd;
    struct sockaddr_in clientaddr;
    char incomeMsg[MAXBUFLEN], outcomeMsg[MAXBUFLEN];
    char * output;

    //load and verify config file
    if ( (e = load_config("config/server.cfg", &config) ) != 0){
        exit(EXIT_FAILURE);
    }
    print_CONFIG(config);
    
    run_srv(config, &sockfd);

    for(;;){
        
        rcv(sockfd, incomeMsg, &clientaddr);
       
        processData(incomeMsg, output, outcomeMsg);

        printf("%s", output);

        snd(sockfd, outcomeMsg, clientaddr);

    }

		// FILE *logptr;
		// logptr = fopen(config.LOG_FILE, "a+");
		// if (logptr != NULL)
		// {
		// 	fputs(buf, logptr);
		// 	fclose(logptr);
		// }

    return 0;
}
