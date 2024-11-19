#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
int main(){
    int sockfd=socket(AF_INET,SOCK_DGRAM,0);
    struct sockaddr_in sockaddr;
    sockaddr.sin_family=AF_INET;
    sockaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    sockaddr.sin_port=htons(9600);
    bind(sockfd,(struct sockaddr*)&sockaddr,sizeof(sockaddr));
    listen(sockfd,5);
    char buf[100];
    int len=sizeof(sockaddr);
    recvfrom(sockfd,buf,sizeof(buf),0,(struct sockaddr*)&sockaddr,&len);
    printf("The message received from the client is %s\n",buf);
    printf("Enter a message you want to sent to client: ");
    fgets(buf,sizeof(buf),stdin);
    sendto(sockfd,buf,sizeof(buf),0,(struct sockaddr*)&sockaddr,sizeof(sockaddr));
}