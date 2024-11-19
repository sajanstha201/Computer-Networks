/*
UDP matrix rows
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
    int buf[256];
    int matrix[256][256];

    //Create socket:
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    printf("Socket created...\n");

    //Bind server address to socket:
    struct sockaddr_in seraddr, cliaddr;
    int clilen = sizeof(cliaddr);

    seraddr.sin_family = AF_INET;
    seraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    seraddr.sin_port = htons(PORTNO);
    bind(sockfd, (struct sockaddr*)&seraddr, sizeof(seraddr));
    printf("Socket binded!\n");

    //Get dimensions:
    int m,n;
    recvfrom(sockfd, buf, sizeof(buf), 0, (struct sockaddr*)&cliaddr, &clilen);\
    m = buf[0];
    n = buf[1];
    printf("Dimensions received: %d x %d\n", m,n);

    //Get actual data:
    for(int i = 0; i < m; i++)
    {
        recvfrom(sockfd, buf, sizeof(buf), 0, (struct sockaddr*)&cliaddr, &clilen);
        printf("Received row#%d: ", i+1);
        for(int j = 0; j < n; j++)
        {
            printf("%d\t", buf[j]);
            matrix[i][j] = buf[j];
        }
        printf("\n");
    }

    //Send matrix to client:
    printf("Sending matrix to client...\n");
    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            buf[i*n + j] = matrix[i][j];
        }
    }
    sendto(sockfd, buf, sizeof(buf), 0, (struct sockaddr*)&cliaddr, sizeof(cliaddr));

    close(sockfd);
    return 0;
}