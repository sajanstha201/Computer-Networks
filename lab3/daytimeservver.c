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
#include <time.h>
#include <string.h>

#define PORTNO 9999

int main(void)
{
    char buf[256];
    int buf2[256];

    //Create socket:
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    printf("Socket created...\n");

    //BInd server address to socket:
    struct sockaddr_in seraddr, cliaddr;
    int clilen = sizeof(cliaddr);

    seraddr.sin_family = AF_INET;
    seraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    seraddr.sin_port = htons(PORTNO);
    bind(sockfd, (struct sockaddr*)&seraddr, sizeof(seraddr));
    printf("Server address binded to port...\n");

    //Listen for client conneciton requests:
    listen(sockfd, 5);

    while(1)
    {
        int newsockfd = accept(sockfd, (struct sockaddr*)&cliaddr, &clilen);

        int pid = fork();

        if(pid==0)
        {
            time_t t;
            time(&t);
            printf("Current time: %s\n", ctime(&t));
            strcpy(buf, ctime(&t));
            printf("Sending to client...\n");
            write(newsockfd, buf, sizeof(buf));
            buf2[0] = getpid();
            write(newsockfd, buf2, sizeof(buf2));
            close(newsockfd);
            exit(0);
        }
        else
        {
            close(newsockfd);
        }
    }
    return 0;
}