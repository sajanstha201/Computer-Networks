#include<stdio.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#define PORTNO 10200
int main(){
    struct sockaddr_in clientAddress;
    clientAddress.sin_family=AF_INET;
    clientAddress.sin_addr.s_addr=inet_addr("127.0.0.1");
    clientAddress.sin_port=htons(PORTNO);
    int socketFd=socket(AF_INET,SOCK_STREAM,0);
    connect(socketFd,(struct sock_addr*)&clientAddress,sizeof(clientAddress));
    write(socketFd,"sajan",5);
    char string[256];
    read(socketFd,string,sizeof(string));
    printf("The string send by the server is : %s",string);
    close(socketFd);
}
