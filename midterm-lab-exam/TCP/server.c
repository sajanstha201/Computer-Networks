#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>
int main(){
    struct sockaddr_in sockaddr,clienaddr;
    sockaddr.sin_family=AF_INET;
    sockaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    sockaddr.sin_port=htons(9600);
    int sockfd=socket(AF_INET,SOCK_STREAM,0);
    bind(sockfd,(struct sockaddr*)&sockaddr,sizeof(sockaddr));
    listen(sockfd,5);
    int len=sizeof(clienaddr);
    int fd=accept(sockfd,(struct sockaddr*)&clienaddr,&len);
    char buffer[100];
    read(fd,buffer,sizeof(buffer));
    printf("The message from the client is %s\n",buffer);
    printf("Enter a message: ");
    fgets(buffer,sizeof(buffer),stdin);
    write(fd,buffer,sizeof(buffer));
}