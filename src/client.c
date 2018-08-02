#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "libs/headers/config.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: ./clientc message\n");
        return -1;
    }

    struct CONFIG config;
    int e = load_config("config/client.cfg", &config);
    if (e != 0) {
        exit(EXIT_FAILURE);
    }
    

    // simple argv protection v0.0.1
    int mess_len;
    if ((mess_len = strlen(argv[1])) > 512) {
        printf("Message is too long\n");
        return -1;
    }

    int udp_socket = socket(AF_INET, SOCK_DGRAM, 0);

    struct in_addr addr_send_to; // *
    addr_send_to.s_addr = inet_addr(config.HOST_IP);

    struct sockaddr_in sockaddr_send_to;
    sockaddr_send_to.sin_family = AF_INET;    
    sockaddr_send_to.sin_port = htons(config.PORT);
    sockaddr_send_to.sin_addr = addr_send_to; // *
    // ssize_t sendto(int sockfd, const void *buf, size_t len, int flags,
    //                const struct sockaddr *dest_addr, socklen_t addrlen);





    char *buf = (char *)malloc(mess_len * sizeof(char));
    strncpy(buf, argv[1], mess_len);

    // if (sendto(udp_socket, buf, 1023, flags,(struct sockaddr *) &sockaddr_send_to, sizeof(sockaddr_send_to)) == -1) {
    //     perror("sendto");
    //     exit(EXIT_FAILURE);
    // }
    if (sendto(udp_socket, buf, mess_len, MSG_CONFIRM, (struct sockaddr *) &sockaddr_send_to, sizeof(sockaddr_send_to)) == -1) {
        perror("send");
        exit(EXIT_FAILURE);     
    }

    char msgFromSrv[512];
    int addrlen = sizeof(sockaddr_send_to);
    ssize_t msglen = recvfrom(udp_socket, msgFromSrv, 512, 0, (struct sockaddr *)&sockaddr_send_to, &addrlen);
    msgFromSrv[msglen] = '\0';
    printf("Server: %s\n", msgFromSrv);

    return 0;
}