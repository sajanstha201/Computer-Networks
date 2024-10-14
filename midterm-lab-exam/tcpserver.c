#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
int main(){
    int sockfd=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in sockaddr,clienaddr;
    sockaddr.sin_family=AF_INET;
    sockaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    sockaddr.sin_port=htons(9600);
    bind(sockfd,(struct sockaddr*)&sockaddr,sizeof(sockaddr));
    listen(sockfd,5);
    int len=sizeof(clienaddr);
    int fd=accept(sockfd,(struct sockaddr*)&clienaddr,&len);
    char buf[100];
    read(fd,buf,sizeof(buf));
    printf("Message from the clinet %s\n",buf);
    printf("Entert a text: ");
    fgets(buf,sizeof(buf),stdin);
    write(fd,buf,sizeof(buf));
    close(sockfd);
    close(fd);
}