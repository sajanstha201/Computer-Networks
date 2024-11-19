#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>
int main(){
    struct sockaddr_in clienaddr;
    clienaddr.sin_family=AF_INET;
    clienaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    clienaddr.sin_port=htons(9600);
    int sockfd=socket(AF_INET,SOCK_STREAM,0);
    int connectid=connect(sockfd,(struct sockaddr*)&clienaddr,sizeof(clienaddr));
    char buffer[100];
    printf("Enter a sentence: ");
    fgets(buffer,sizeof(buffer),stdin);
    write(sockfd,buffer,sizeof(buffer));
    read(sockfd,buffer,sizeof(buffer));
    printf("The message from the server is %s\n",buffer);
}