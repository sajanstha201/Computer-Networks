#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<time.h>
int main(){
    int sockfd=socket(AF_INET,SOCK_DGRAM,0);
    struct sockaddr_in sockaddr;
    sockaddr.sin_family=AF_INET;
    sockaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    sockaddr.sin_port=htons(9600);
    char buf[100];
    time_t t;
    time(&t);
    printf("The value of time is %s\n",ctime(&t));
    printf("Enter a message: ");
    fgets(buf,sizeof(buf),stdin);
    sendto(sockfd,buf,sizeof(buf),0,(struct sockaddr*)&sockaddr,sizeof(sockaddr));
    int len=sizeof(sockaddr);
    recvfrom(sockfd,buf,sizeof(buf),0,(struct sockaddr*)&sockaddr,&len);
    printf("The message from the server is %s\n",buf);
}