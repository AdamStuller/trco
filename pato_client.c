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
    char * message = "daco";
    int sockfd;
    struct sockaddr_in servaddr;

    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);
    servaddr.sin_family = AF_INET;

    //create socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

    for(;;){
        scanf("%s", message);
        sendto(sockfd, message, MAXLINE, 0, NULL, sizeof(servaddr));

        //wait for response
        char buffer[MAXLINE];
        ssize_t msgLen;
        msgLen = recvfrom(sockfd, buffer, sizeof(buffer), 0, NULL, NULL);
        buffer[msgLen] = '\0';
        printf("%s", buffer);
    }
    

    return 0;
}
