#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ULL unsigned long long
#define N 100005
ULL hash[N],c[N][2];

void update(int x,ULL val,int y);
ULL sum(int x,int y);

void str_hash(char* s,char process){
    FILE* f;
    f=fopen("output.txt", "a");
    hash[0]=1;
    for (int i=1;i<=N;i++){
        hash[i]=hash[i-1]*13;
    }
    int n,l,r,pos;
    char ch;
    int len=strlen(s);
    memset(c,0,sizeof(c));
    for (int i=0;i<len;i++){
        update(i+1,(s[i]-'A')*hash[i],0);
        update(i+1,(s[len-1-i]-'A')*hash[i],1);
    }
    if (process=='p') {
        scanf("%d %d",&l,&r);
        getchar();
        ULL s1=(sum(r,0)-sum(l-1,0))*hash[len-r];
        ULL s2=(sum(len-l+1,1)-sum(len-r,1))*hash[l-1];
        if (s1==s2) {
            printf("is palindrome\n");
            fprintf(f,"The %dth to %dth substring is palindrome.\n", l, r);
        }
        else {
            printf("not palindrome\n");
            fprintf(f,"The %dth to %dth substring is not palindrome.\n", l, r);
        }
    }
    else if (process=='c'){
        scanf("%d %c",&pos,&ch);
        getchar();
        fprintf(f,"The %dth char is changed to %c.\n", pos, ch);
        int change=ch-s[pos-1];
        s[pos-1]=ch;
        update(pos,change*hash[pos-1],0);
        update(len-pos+1,change*hash[len-pos],1);
        s[pos-1]=ch;
    }
    fclose(f);
}


