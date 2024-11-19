#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
int main(){
    int sockfd=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in sockaddr;
    sockaddr.sin_family=AF_INET;
    sockaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    sockaddr.sin_port=htons(9600);
    connect(sockfd,(struct sockaddr*)&sockaddr,sizeof(sockaddr));
    printf("Enter the buffer: ");
    char buf[100];
    fgets(buf,sizeof(buf),stdin);
    write(sockfd,buf,sizeof(buf));
    printf("The message sent to the server is %s\n",buf);
    read(sockfd,buf,sizeof(buf));
    printf("The message from the server is %s\n",buf);
}