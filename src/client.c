#include "libs/headers/udp_protocol.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: ./clientc message\n");
        return -1;
    }

    // simple argv protection v0.0.1
    int mess_len;
    if ((mess_len = strlen(argv[1])) > 512) {
        printf("Message is too long\n");
        return -1;
    }

    struct CONFIG config;
    int e = load_config("config/client.cfg", &config);
    if (e != 0) {
        exit(EXIT_FAILURE);
    }
    
    struct sockaddr_in servaddr;
    int sockfd;

    run(config, &sockfd, CLIENT_SIDE);

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(config.PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    snd(sockfd, argv[1], &servaddr);

    char buff[512];
    rcv(sockfd, buff, &servaddr);
    
    printf("Response: %s\n", buff);
    

    return 0;
}