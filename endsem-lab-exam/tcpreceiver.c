#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
int main(){
    int sockfd=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in sockaddr,clienaddr;
    sockaddr.sin_family=AF_INET;
    sockaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    sockaddr.sin_port=htons(9600);
    bind(sockfd,(struct sockaddr*)&sockaddr,sizeof(sockaddr));
    listen(sockfd,5);
    int len=sizeof(clienaddr);
    int newfd=accept(sockfd,(struct sockaddr*)&clienaddr,&len);
    char buf[100];
    read(newfd,buf,sizeof(buf));
    printf("The message from the client is %s\n",buf);
    printf("Enter  a message to sent to client: ");
    fgets(buf,sizeof(buf),stdin);
    write(newfd,buf,sizeof(buf));
}