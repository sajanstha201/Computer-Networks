#include<stdio.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<unistd.h>
#define PORTNO 10200
int main(){
    struct sockaddr_in serverAddress;
    serverAddress.sin_family=AF_INET;
    serverAddress.sin_addr.s_addr=inet_addr("127.0.0.1");
    serverAddress.sin_port=htons(PORTNO);
    int connectSocketFd=socket(AF_INET,SOCK_STREAM,0);
    bind(connectSocketFd,(struct sockaddr*)&serverAddress,sizeof(serverAddress));
    listen(connectSocketFd,5);
    struct sockaddr_in clientAddr;
    int len=sizeof(clientAddr);
    printf("server is wating\n");
    int acceptedFd=accept(connectSocketFd,(struct sockaddr*)&clientAddr,&len);
    char string[200];
    read(acceptedFd,string,sizeof(string));
    printf("%s",string);
    write(acceptedFd,"shrestha",200);
    close(connectSocketFd);
    close(acceptedFd);

}