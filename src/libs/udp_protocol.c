#include "headers/udp_protocol.h"

/**
 * Allocate new message with size of header.size
 * returned as buf arg.
 */
int msg_to_bytes(struct Message m, unsigned char** buf) {
    // buf = (unsigned char *) malloc(sizeof(unsigned char*) * sizeof(struct Message));
    // if (buf == NULL)
    //     return -1;
    // buf = (unsigned char*)&m;
    *buf = (unsigned char*)&m;
    return 0;
}

/**
 * Convert Bytes to message of len
 */
int bytes_to_msg(struct Message *m, unsigned char *buf, int body_len) {
    // first 8 bytes is header
    struct Message_Header mh;
    mh.size = (uint16_t) *(buf + 1) << 8 | *(buf + 0); // 2B
    mh.count = (uint16_t) *(buf + 3) << 8 | *(buf + 2); // 2B
    mh.order = (uint16_t) *(buf + 5) << 8 | *(buf + 4); // 2B
    mh.type = (uint16_t) *(buf + 7) << 8 | *(buf + 6); // 2B
    
    m->header = mh;
    

    // max 412 iters
    for (int i = 8, j = 0; i < body_len; i++)
        m->body[j++] = buf[i]; 

    return 0;
}

/*
    recieve function writes raw income message into arg1,
    sets client address into arg2
*/
int rcv(int sockfd, char * income, struct sockaddr_in * clientaddr){
    ssize_t msgLen;
    int n = sizeof(*clientaddr);
    msgLen = recvfrom(sockfd, income, MAXBUFLEN - 1, 0, (struct sockaddr*)clientaddr, &n);    
    if (msgLen == -1) {
        perror("recvfrom");
        income = NULL;
        return -1;
    }
    
    income[msgLen] = '\0';

    return 0;
}

/*
    sends raw message to client
*/
int snd(int sockfd, char * outcomeMsg, struct sockaddr_in *clientaddr){ 

    if (sendto(sockfd, outcomeMsg, MAXBUFLEN, 0, (struct sockaddr*)clientaddr, sizeof(*clientaddr)) == -1) {
        perror("sendto");
        return -1;
    }
    return 0;
}

/*
    creates file descriptor and passes it through arg1 - int * sockfd.
    Properly loaded config file needed to succesfull run.
*/
int run(struct CONFIG config, int * sockfd, int side){

    //TODO: error check

    *sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(config.PORT);
    servaddr.sin_addr.s_addr = inet_addr(config.HOST_IP);

    if (side == 0){

        if (bind(*sockfd, (struct sockaddr *)&servaddr, (socklen_t) sizeof(servaddr)) == -1) {
            handle_error("bind");
        }
        
        printf("Server is running, waiting for connections\n");
    }
    
    printf("Client running\n");
    
    return 0;
}