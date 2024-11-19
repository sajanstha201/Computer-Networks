/*
TCP daytime
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>

#define PORTNO 9999

int main(void)
{
    char buf[256];
    int buf2[256];

    //Create socket:
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    printf("Socket created!\n");

    //Set server address:
    struct sockaddr_in seraddr;
    seraddr.sin_family = AF_INET;
    seraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    seraddr.sin_port = htons(PORTNO);

    //Send connection request to server:
    int result = connect(sockfd, (struct sockaddr*)&seraddr, sizeof(seraddr));
    if(result==-1)
    {
        printf("Connection error...\n");
        close(sockfd);
        exit(1);
    }

    //Get time from server:
    printf("Waiting for server to provide time...\n");
    read(sockfd, buf, sizeof(buf));
    printf("Current date-time: %s\n",buf);
    read(sockfd, buf2, sizeof(buf2));
    printf("PID = %d\n", buf2[0]);

    close(sockfd);
    return 0;
}