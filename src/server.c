#include "libs/udp_server.h"
// #include "libs/config.h"

int main () {

    //load and verify config file
    struct CONFIG config;
    int e, sockfd;
    char income[MAXBUFLEN];

    if ( (e = load_config("config/server.cfg", &config) ) != 0){
        exit(EXIT_FAILURE);
    }
    print_CONFIG(config);
    
    if ( (e = run_srv(config, &sockfd)) != 0){
        exit(EXIT_FAILURE);
    }
    printf("Server is running, waiting for connections\n");

    //main server loop
    for(;;){

        //waiting for data
        if ( (e = rcv(sockfd, income)) != 0 ){
            exit(EXIT_FAILURE);
        }

        if ( (e = processData()) != 0 ){
            exit(EXIT_FAILURE);
        }

        if ( (e = snd()) != 0 ){
            exit(EXIT_FAILURE);
        }

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
