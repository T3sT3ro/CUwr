//
// Created by Tooster on 18.10.17.
//

#include <stdio.h>

long long factorial(long long n){
    if(n==1) return 1;
    return n*factorial(n-1);
}

int main(){
    printf("Please, input a number n from range 1-18\n");
    int n;
    scanf("%d");
    printf("%d! = %lld", n, factorial((long long) n));
}
