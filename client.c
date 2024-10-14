#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdio.h>
#define PORTNO 10200
int main(){
    struct sockaddr_in address;
    int sockfd;
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    address.sin_family=AF_INET;
    address.sin_addr.s_addr=inet_addr("127.0.0.1");
    address.sin_port=htons(PORTNO);
    connect(sockfd,(struct sockaddr*)&address,sizeof(address));
    char str[100];
    printf("Enter a word:");
    scanf("%s",str);
    write(sockfd,str,sizeof(str));
    char string[256];
    read(sockfd,string,sizeof(string));
    printf("The string send by the server is : %s",string);
    close(sockfd);
}