#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
int main(){
    int sockfd=socket(AF_INET,SOCK_DGRAM,0);
    struct sockaddr_in sockaddr;
    sockaddr.sin_family=AF_INET;
    sockaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    sockaddr.sin_port=htons(9600);
    int m,n;
    printf("Enter the dimension of matrix: ");
    scanf("%d%d",&m,&n);
    sendto(sockfd,&m,sizeof(int),0,(struct sockaddr*)&sockaddr,sizeof(sockaddr));
    sendto(sockfd,&n,sizeof(int),0,(struct sockaddr*)&sockaddr,sizeof(sockaddr));
    int i,j;
    for(i=0;i<m;i++){
        printf("Enter the %d row value: ",i+1);
        int arr[n];
        for(j=0;j<n;j++)
            scanf("%d",&arr[j]);
        sendto(sockfd,arr,sizeof(arr),0,(struct sockaddr*)&sockaddr,sizeof(sockaddr));
    }
    int result_arr[m*n];
    int len=sizeof(sockaddr);
    recvfrom(sockfd,result_arr,sizeof(result_arr),0,(struct sockaddr*)&sockaddr,&len);
    for(i=0;i<m;i++){
        for(j=0;j<n;j++){
            printf("%d\t",result_arr[i*m+j]);
        }
        printf("\n");
    }
}