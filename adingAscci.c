#include<stdio.h>
int main(){
    char a,b;
    while(1){
    printf("Enter one char: ");
    scanf(" %c",&a);
    printf("Enter ath char: ");
    scanf(" %c",&b);
    printf("Value: %c\n",(a-'a'+b-'a'+1)%26+'a');
    }

}

// BGYVMC