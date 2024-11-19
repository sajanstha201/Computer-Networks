#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
int main(){
    struct sockaddr_in sockaddr;
    sockaddr.sin_family=AF_INET;
    sockaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    sockaddr.sin_port=htons(9600);
    int sockfd=socket(AF_INET,SOCK_DGRAM,0);
    char buffer[100];
    printf("Enter a message: ");
    fgets(buffer,sizeof(buffer),stdin);
    int len=sizeof(sockaddr);
    sendto(sockfd,buffer,sizeof(buffer),0,(struct sockaddr*)&sockaddr,sizeof(sockaddr));
    recvfrom(sockfd,buffer,sizeof(buffer),0,(struct sockaddr*)&sockaddr,&len);
    printf("Message from the server is %s\n",buffer);
}