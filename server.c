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
    // create socket - man ip 7
    int udp_socket;
    if ((udp_socket = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        handle_error("socket");
    }

    
    struct sockaddr_in addr_listen_on;
    addr_listen_on.sin_family = AF_INET; // AF_INET is an address family that is used to designate the type of addresses that your socket can communicate with (in this case, Internet Protocol v4 addresses)
    addr_listen_on.sin_port = htons(5000);
    
    struct in_addr inaddr;
    inaddr.s_addr = htonl(INADDR_LOOPBACK); // the struct s_addr is a 4-byte number that represents one digit in an IP address per byte
    
    addr_listen_on.sin_addr = inaddr;
    
    // assigning a name to a socket is called binding & error check
    if (bind(udp_socket, (struct sockaddr *)&addr_listen_on, sizeof(struct sockaddr_in))) {
        handle_error("bind");
    }

    int numbytes = -1; // default value for failure; othertimes will hold number of incoming bytes in buf
    int addr_len = 0;
    struct sockaddr_in addr_incoming_from_outside; // hold their address
    char buf[MAXBUFLEN]; // space for holding incoming data in memory

    printf("Server is running, waiting for connections\n");

    while(1) {
        addr_len = sizeof(struct sockaddr);

        /**
         * recvfrom() places the received message into the buffer buf.  The caller must specify the size of the buffer in len.
         * If the caller is not interested in the source address, src_addr and addrlen should be specified as NULL.
        */
        if ((numbytes = recvfrom(udp_socket, buf, MAXBUFLEN-1 , 0,
            (struct sockaddr *)&addr_incoming_from_outside, &addr_len)) == -1) {
            handle_error("recvfrom");
        }

        buf[numbytes] = '\0';
        printf("length: %d\ncontent: %s\n", numbytes, buf);

		/*
		 * Save received data into log file		
		*/

		FILE *logptr;
		logptr = fopen("./build/log", "a+");
		if (logptr != NULL)
		{
			fputs(buf, logptr);
			fclose(logptr);
		}

    }

    return 0;
}
