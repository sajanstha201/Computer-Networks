#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
int main(){
    struct sockaddr_in sockaddr;
    sockaddr.sin_family=AF_INET;
    sockaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    sockaddr.sin_port=htons(9600);
    int sockfd=socket(AF_INET,SOCK_DGRAM,0);
    bind(sockfd,(struct sockaddr*)&sockaddr,sizeof(sockaddr));
    listen(sockfd,5);
    char buffer[100];
    int len=sizeof(sockaddr);
    recvfrom(sockfd,buffer,sizeof(buffer),0,(struct sockaddr*)&sockaddr,&len);
    printf("Message from the clinet is %s\n",buffer);
    printf("Enter a message: ");
    fgets(buffer,sizeof(buffer),stdin);
    sendto(sockfd,buffer,sizeof(buffer),0,(struct sockaddr*)&sockaddr,len);
}