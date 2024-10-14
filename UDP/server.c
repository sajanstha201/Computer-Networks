#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
int main(){
    struct sockaddr_in addr,caddr;
    int sockfd=socket(AF_INET,SOCK_DGRAM,0);
    addr.sin_family=AF_INET;
    addr.sin_addr.s_addr=inet_addr("127.0.0.1");
    addr.sin_port=htons(9600);
    int result=bind(sockfd,(struct sockaddr*)&addr,sizeof(addr));
    char buf[100];
    int len=sizeof(caddr);
    int m=recvfrom(sockfd,buf,sizeof(buf),0,(struct sockaddr*)&caddr,&len);
    printf("The received message is %s\n",buf);

}