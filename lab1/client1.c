#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<unistd.h>
#define PORT_NO 10200
int main(){
    struct sockaddr_in clientSocket;
    clientSocket.sin_family=AF_INET;
    clientSocket.sin_addr.s_addr=inet_addr("127.0.0.1");
    clientSocket.sin_port=htons(PORT_NO);
    int socketfd=socket(AF_INET,SOCK_STREAM,0);
    int len=sizeof(clientSocket);
    connect(socketfd,(struct sockaddr*)&clientSocket,len);
    char str[256];
    while(1){
        printf("Enter some word:");
        fgets(str,sizeof(str),stdin);
        write(socketfd,str,sizeof(str));
        read(socketfd,str,sizeof(str));
        printf("Server message: %s\n",str);
    }
    
    
}

