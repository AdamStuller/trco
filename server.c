#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

// util function from man 2 bind
#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)

#define MAXBUFLEN 1024

int main () {
    // man ip 7 | man 
    // create socket
    int udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
    int cfd;

    if (udp_socket == -1) {
        handle_error("socket");
    }

    
    struct sockaddr_in my_addr;

    struct in_addr inaddr;
    inaddr.s_addr = htonl(INADDR_LOOPBACK);

    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(5000);
    my_addr.sin_addr = inaddr;
    
    // assigning a name to a socket is called binding
    int b = bind(udp_socket, (struct sockaddr *)&my_addr, sizeof(struct sockaddr_in));

    if (b == -1) {
        handle_error("bind");
    }

    int numbytes = -1;
    int addr_len = 0;
    struct sockaddr_in their_addr;
    char buf[MAXBUFLEN];

    printf("Server is running, waiting for connection\n");

    while(1) {
        addr_len = sizeof(struct sockaddr);
        if ((numbytes = recvfrom(udp_socket, buf, MAXBUFLEN-1 , 0,
            (struct sockaddr *)&their_addr, &addr_len)) == -1) {
            handle_error("recvfrom");
        }

        buf[numbytes] = '\0';
        printf("length: %d\ncontent: %s\n", numbytes, buf);
    }

    return 0;
}
