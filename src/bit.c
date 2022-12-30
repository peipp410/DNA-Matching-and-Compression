#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ULL unsigned long long
#define N 100005
ULL hash[N],c[N][2];

int lowbit(int x){
    return x&(-x);
}

void update(int x,ULL val,int y){
    while (x<=N){
        c[x][y]+=val;
        x+=lowbit(x);
    }
}

ULL sum(int x,int y){
    ULL ret=0;
    while (x>0){
        ret+=c[x][y];
        x-=lowbit(x);
    }
    return ret;
}