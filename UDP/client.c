#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>
int main(){
    struct sockaddr_in sockaddr;
    int sd=socket(AF_INET,SOCK_DGRAM,0);
    sockaddr.sin_family=AF_INET;
    sockaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    sockaddr.sin_port=htons(9600);
    char buf[100];
    printf("Enter the string: ");
    fgets(buf,sizeof(buf),stdin);
    int m=sendto(sd,buf,sizeof(buf),0,(struct sockaddr*)&sockaddr,sizeof(sockaddr));
}