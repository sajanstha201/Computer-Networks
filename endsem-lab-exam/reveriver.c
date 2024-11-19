#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
int main(){
    int sockfd=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in sockaddr;
    sockaddr.sin_family=AF_INET;
    sockaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    sockaddr.sin_port=htons(9600);
    bind(sockfd,(struct sockaddr*)&sockaddr,sizeof(sockaddr));
    listen(sockfd,5);
    int len=sizeof(sockaddr);
    int newfd=accept(sockfd,(struct sockaddr*)&sockaddr,&len);
    char buf[100];
    read(newfd,buf,sizeof(buf));
    printf("Messsage from the clien is %s\n",buf);
    printf("Enter  a message you want to sent to client: ");
    fgets(buf,sizeof(buf),stdin);
    write(newfd,buf,sizeof(buf));
}
