#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#define PORT_NO 10200
int main(){
    struct sockaddr_in sockaddr,clientaddr;
    sockaddr.sin_family=AF_INET;
    sockaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    sockaddr.sin_port=htons(PORT_NO);
    int sockfd=socket(AF_INET,SOCK_STREAM,0);
    bind(sockfd,(struct sockaddr*)&sockaddr,sizeof(sockaddr));
    listen(sockfd,5);
    int clilen=sizeof(clientaddr);
    printf("Server is Waiting...\n");
    int newsock=accept(sockfd,(struct sockaddr*)&clientaddr,&clilen);
    char str[256];
    while(1){
        read(newsock,str,sizeof(str));
        printf("Client Message: %s\n",str);
        printf("Enter a message: ");
        fgets(str,sizeof(str),stdin);
        write(newsock,str,sizeof(str));
    }

}