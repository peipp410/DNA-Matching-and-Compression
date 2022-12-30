#define M 500
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct node{
    int tr[M][26];
    int is_end[M];
    int fail[M];
};
typedef struct node TNode;

void insert_trie(char* s, TNode* p, int* cnt, int num){
    int i,q=0;
    while (*s!='\0'){
        i=*s-'A';
        if (p->tr[q][i]==0)
        {p->tr[q][i]=(*cnt);
            (*cnt)=(*cnt)+1;}
        q=p->tr[q][i];
        s++;
    }
    p->is_end[q]=num;
}

void trie_get_fail(TNode* p){
    memset(p->fail,0,sizeof(p->fail));
    int q[1000];
    int l=0, r=0;
    for (int i=0;i<26;i++){
        if (p->tr[0][i]){
            q[r++]=p->tr[0][i];
        }
    }
    while (l<r){
        int k=q[l++];
        for (int i=0;i<26;i++){
            if (p->tr[k][i]){
                p->fail[p->tr[k][i]]=p->tr[p->fail[k]][i];
                q[r++]=p->tr[k][i];
            }
            else p->tr[k][i]=p->tr[p->fail[k]][i];
        }
    }
}

void trie_query(char* s, TNode* p){
    FILE* f;
    f=fopen("output.txt", "a");
    int now=0;
    for (int i=0;s[i];i++){
        now=p->tr[now][s[i]-'A'];
        for (int j=now;j && p->is_end[j]!=-1;j=p->fail[j]){
            if (p->is_end[j]!=0){
                printf("Found pattern string NO.%d in index %d\n",p->is_end[j],i+1);
                fprintf(f,"Found pattern string NO.%d in index %d\n",p->is_end[j],i+1);
            }
        }
    }
    fclose(f);
}

void trie(char* seq){
    int* cnt=(int*)malloc(sizeof(int));
    *cnt=1;
    char line[100];
    TNode* p;
    p=(TNode*)malloc(sizeof(TNode));
    for (int i=0;i<M;i++){
        for (int j=0;j<26;j++){
            p->tr[i][j]=0;
        }
        p->is_end[i]=0;
    }
    FILE* f;
    f=fopen("str.txt", "r"); //读入模式串
    int num=0;
    while(fgets(line, sizeof(line), f)){
        num++;
        line[strlen(line)-1]='\0';
        insert_trie(line,p,cnt,num);
    }
    trie_get_fail(p);
    fclose(f);
    trie_query(seq,p);
}
