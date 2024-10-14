#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
int main(){
    int status;
    struct sockaddr_in sockaddr,clienaddr;
    sockaddr.sin_family=AF_INET;
    sockaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    sockaddr.sin_port=htons(10200);
    int sockfd=socket(AF_INET,SOCK_STREAM,0);
    bind(sockfd,(struct sockaddr*)&sockaddr,sizeof(sockaddr));
    listen(sockfd,5);
    int len=sizeof(clienaddr);
    int newsocket=accept(sockfd,(struct sockaddr*)&clienaddr,&len);
    int pid=fork();
    int str[256];
    if(pid==0){
        printf("This is child process\n");
        read(newsocket,str,sizeof(str));
        printf("The message got is %s\n",str);
        close(newsocket);
    }
    else if(pid>0){
        wait(&status);
        printf("This is parent process\n");
        close(newsocket);
    }
}