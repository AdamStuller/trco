#include "libs/udp_server.h"
// #include "libs/config.h"

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
        
        /*
            clientaddr sa vzdy nastavi na adresu clienta v rcv()
        */


        //recieve from client, set clientaddr
        rcv(sockfd, incomeMsg, &clientaddr);
       
        /*
            incomeMsg je je raw sprava od clienta,
            teraz je uz len na uvazeni, ci chceme v main mat nejaky data processing alebo to pojde rovno
            do processData(), ktora do output vypise chceny text z packetu a outcomeMsg ktory sa posle na client ako succes/fail/todo/request...
        */

        //processData(incomeMsg, output, outcomeMsg);           //not implemented

        printf("%s", incomeMsg);

        //snd(sockfd, outcomeMsg, clientaddr);                  //not implemented

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
