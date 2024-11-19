#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/in.h>
int main(){
    int sockfd=socket(AF_INET,SOCK_DGRAM,0);
    struct sockaddr_in sockaddr;
    sockaddr.sin_family=AF_INET;
    sockaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    sockaddr.sin_port=htons(9600);
    int m,n;
    int len=sizeof(sockaddr);
    bind(sockfd,(struct sockaddr*)&sockaddr,sizeof(sockaddr));
    listen(sockfd,5);
    recvfrom(sockfd,&m,sizeof(int),0,(struct sockaddr*)&sockaddr,&len);
    recvfrom(sockfd,&n,sizeof(int),0,(struct sockaddr*)&sockaddr,&len);
    printf("Received matrix dimension is %d %d\n",m,n);
    int i,j;
    int r_arr[m*n];
    for(i=0;i<m;i++){
        int arr[n];
        recvfrom(sockfd,arr,sizeof(arr),0,(struct sockaddr*)&sockaddr,&len);
        printf("Received %d row value: ",i+1);
        for(j=0;j<n;j++){
            printf("%d ",arr[j]);
            r_arr[i*m+j]=arr[j];
        }
        printf("\n");
    }
    printf("Result matrix is :\n");
    for(i=0;i<m;i++){
        for(j=0;j<n;j++){
            printf("%d ",r_arr[i*m+j]);
        }
        printf("\n");
    }
    sendto(sockfd,r_arr,sizeof(r_arr),0,(struct sockaddr*)&sockaddr,sizeof(sockaddr));
}