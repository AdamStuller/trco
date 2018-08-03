#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "config.h"

// util function from man 2 bind
#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)

#define MAXBUFLEN 512

int run_srv(struct CONFIG config, int * sockfd);
int rcv(int sockfd, char * income, struct sockaddr_in * clientaddr);
int snd(int sockfd, char * outcomeMsg, struct sockaddr_in *clientaddr);