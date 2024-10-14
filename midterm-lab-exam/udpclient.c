#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
int main(){
    int sockfd=socket(AF_INET,SOCK_DGRAM,0);
    struct sockaddr_in sockaddr;
    sockaddr.sin_family=AF_INET;
    sockaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    sockaddr.sin_port=htons(9600);
    char buf[100];
    printf("Enter a string: ");
    int len=sizeof(sockaddr);
    fgets(buf,sizeof(buf),stdin);
    int r=sendto(sockfd,buf,sizeof(buf),0,(struct sockaddr*)&sockaddr,sizeof(sockaddr));
    int l=recvfrom(sockfd,buf,sizeof(buf),0,(struct sockaddr*)&sockaddr,&len);
    printf("Message from the server %s\n",buf);
}