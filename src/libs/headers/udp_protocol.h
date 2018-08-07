#include <stdint.h>
#include <stdlib.h>
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

int run_srv(struct CONFIG config, int * sockfd);

#define MESSAGE_BODY_LEN 412
#define MESSAGE_HEADER_LEN 7
#define MAXBUFLEN 512
#define CLIENT_SIDE 1
#define SERVER_SIDE 0

struct Message_Header {
    uint16_t size;
    uint16_t count;
    uint16_t order;
    uint16_t type;
};

struct Message {
    struct Message_Header header;
    char body[MESSAGE_BODY_LEN];
};



int msg_to_bytes(struct Message m, unsigned char** buf);
int bytes_to_msg(struct Message *m, unsigned char *buf, int body_len);
int rcv(int sockfd, char * income, struct sockaddr_in * clientaddr);
int snd(int sockfd, char * outcomeMsg, struct sockaddr_in *clientaddr);
int run(struct CONFIG config, int * sockfd, int side);