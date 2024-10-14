#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#define PORTNO 10200
int main(){
    struct sockaddr_in seraddress,clientaddress;
    int newsockfd;
    int sockfd;
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    seraddress.sin_family=AF_INET;
    seraddress.sin_addr.s_addr=inet_addr("127.0.0.1");
    seraddress.sin_port=htons(PORTNO);
    bind(sockfd,(struct sockaddr_in *)&seraddress,sizeof(seraddress));
    listen(sockfd,5);
    printf("server is waiting...");
    int clientlen;
    clientlen=sizeof(clientaddress);
    newsockfd=accept(sockfd,(struct sockaddr_in *)&clientaddress,&clientlen);
    char buf[256];
    read(newsockfd,buf,sizeof(buf));
    printf("%s",buf);
    close(sockfd);
    close(newsockfd);
}