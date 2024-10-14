#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/types.h>
#define PORTNO 10200
int main(){
    struct sockaddr_in sockaddr;
    sockaddr.sin_family=AF_INET;
    sockaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    sockaddr.sin_port=htons(PORTNO);
    int sockfd=socket(AF_INET,SOCK_STREAM,0);
    connect(sockfd,(struct sockaddr*)&sockaddr,sizeof(sockaddr));
    char str[256];
    while(1){
        printf("Enter message: ");
        fgets(str,sizeof(str),stdin);
        write(sockfd,str,sizeof(str));
        int c=read(sockfd,str,sizeof(str));
        if(c==0){
            printf("Server is closed");
            close(sockfd);
            return 0;
        }
        printf("Server Message: %s\n",str);
    }
    close(sockfd);
    return 0;
}