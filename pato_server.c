#include <string.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>

#define PORT 8080
#define MAXLINE 1024

int main(int argc, char const *argv[])
{
    int sockfd;
    char messageFromClient[MAXLINE];
    struct sockaddr_in servaddr, clientaddr;
    char buffer[MAXLINE];

    //Create UDP Sockett
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);
    servaddr.sin_family = AF_INET;

    //Bind socket to file descriptor
    bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

    for(;;){
        //Recieve datagram
        ssize_t msgLen;
        int n = sizeof(clientaddr);
        msgLen = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&clientaddr, &n);
        buffer[msgLen] = '\0';
        printf("%s\n", buffer);

        sendto(sockfd, "Message arrived!\n", 18, 0, (const struct sockaddr*)&clientaddr, (socklen_t) sizeof(clientaddr));
    }
    
    return 0;
}

