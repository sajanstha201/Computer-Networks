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

    //Create socket:
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    printf("Socket created...\n");

    //Set server address:
    struct sockaddr_in seraddr;
    seraddr.sin_family = AF_INET;
    seraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    seraddr.sin_port = htons(PORTNO);
    
    //Get dimensions:
    int m,n;
    printf("Enter dimensions of matrix: ");
    scanf("%d %d", &m, &n);
    buf[0] = m;
    buf[1] = n;
    printf("Sending dimensions to server...\n");
    sendto(sockfd, buf, sizeof(buf), 0, (struct sockaddr*)&seraddr, sizeof(seraddr));

    //Get actual row data:
    for(int i = 0; i < m; i++)
    {
        printf("Enter data for Row#%d: ", i+1);
        for(int j = 0; j < n; j++)
        {
            scanf("%d", &buf[j]);
        }
        printf("Sending row to server...\n");
        sendto(sockfd, buf, sizeof(buf), 0, (struct sockaddr*)&seraddr, sizeof(seraddr));
    }

    //Receive matrix from server:
    printf("Waiting for server matrix...\n");
    int serlen = sizeof(seraddr);
    recvfrom(sockfd, buf, sizeof(buf), 0, (struct sockaddr*)&seraddr, &serlen);

    printf("MATRIX:\n");
    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            printf("%d\t", buf[i*n + j]);
        }
        printf("\n");
    }

    close(sockfd);
    return 0;
}