//
// Created by i300791 on 18.10.17.
//

#include <stdio.h>

long long factorial(long long n){
    if(n==1) return 1;
    return n*factorial(n-1);
}

int main(){
    printf("Please, input a number n from range 1-??");
    int n;
    scanf("%d");
    printf("%ld", factorial(n));
}
