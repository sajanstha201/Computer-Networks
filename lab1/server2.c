#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/types.h>
#define PORTNO 10200
int main(){
    struct sockaddr_in sockaddr,clientaddr;
    sockaddr.sin_family=AF_INET;
    sockaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    sockaddr.sin_port=htons(PORTNO);
    int sockfd=socket(AF_INET,SOCK_STREAM,0);
    bind(sockfd,(struct sockaddr_in*)&sockaddr,sizeof(sockaddr));
    listen(sockfd,5);
    printf("server is waiting...\n");
    int len=sizeof(clientaddr);
    int newsocket=accept(sockfd,(struct sockaddr_in*)&clientaddr,&len);
    char str[256];
    while(1){
        read(newsocket,str,sizeof(str));
        printf("%s\n",str);
        printf("%d\n",strcmp(str,"stop"));
        if(strcmp(str,"stop\n")==0){
            printf("closing the server..\n");
            close(newsocket);
            return 0;
        }
        write(newsocket,"good job",sizeof(str));

    }
}