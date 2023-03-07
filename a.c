#include <stdio.h> 
int main(int argc,char* argv[]){
    int i, sum;
    while(scanf("%d", &i) != EOF){
        sum += i;
    }
    printf("%d", sum);
    return 0;
}       
