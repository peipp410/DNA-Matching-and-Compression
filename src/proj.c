#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define M 500
struct node{
    int tr[M][26];
    int is_end[M];
    int fail[M];
};
typedef struct node TNode;
#define ULL unsigned long long
#define N 100005
ULL hash[N],c[N][2];
typedef struct {
    int weight;
    int parent, left, right;
}HTNode, *HuffmanTree;
typedef char ** HuffmanCode;

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
    int now=0;
    for (int i=0;s[i];i++){
        now=p->tr[now][s[i]-'A'];
        for (int j=now;j && p->is_end[j]!=-1;j=p->fail[j]){
            if (p->is_end[j]!=0){
                printf("Found pattern string NO.%d in index %d\n",p->is_end[j],i+1);
            }
        }
    }
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

void str_hash(char* s,char process){
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
        if (s1==s2) printf("is palindrome\n");
        else printf("not palindrome\n");
    }
    else if (process=='c'){
        scanf("%d %c",&pos,&ch);
        getchar();
        int change=ch-s[pos-1];
        s[pos-1]=ch;
        update(pos,change*hash[pos-1],0);
        update(len-pos+1,change*hash[len-pos],1);
        s[pos-1]=ch;
    }
}

void Select(HuffmanTree HT, int end, int *s1, int *s2){
    int min1, min2;
    int i = 1;
    while(HT[i].parent != 0 && i <= end){
        i++;
    }
    min1 = HT[i].weight;
    *s1 = i;
    i++;
    while(HT[i].parent != 0 && i <= end){
        i++;
    }
    if(HT[i].weight < min1){
        min2 = min1;
        *s2 = *s1;
        min1 = HT[i].weight;
        *s1 = i;
    }else{
        min2 = HT[i].weight;
        *s2 = i;
    }
    for(int j=i+1; j <= end; j++){
        if(HT[j].parent != 0){
            continue;
        }
        if(HT[j].weight < min1){
            min2 = min1;
            min1 = HT[j].weight;
            *s2 = *s1;
            *s1 = j;
        }
        else if(HT[j].weight >= min1 && HT[j].weight < min2){
            min2 = HT[j].weight;
            *s2 = j;
        }
    }
}

void CreateHuffmanTree(HuffmanTree *HT, int *w, int n)
{
    if(n<=1) return;
    int m = 2*n-1;
    *HT = (HuffmanTree) malloc((m+1) * sizeof(HTNode));
    HuffmanTree p = *HT;
    for(int i = 1; i <= n; i++)
    {
        (p+i)->weight = *(w+i-1);
        (p+i)->parent = 0;
        (p+i)->left = 0;
        (p+i)->right = 0;
    }
    for(int i = n+1; i <= m; i++)
    {
        (p+i)->weight = 0;
        (p+i)->parent = 0;
        (p+i)->left = 0;
        (p+i)->right = 0;
    }
    for(int i = n+1; i <= m; i++)
    {
        int s1, s2;
        Select(*HT, i-1, &s1, &s2);
        (*HT)[s1].parent = (*HT)[s2].parent = i;
        (*HT)[i].left = s1;
        (*HT)[i].right = s2;
        (*HT)[i].weight = (*HT)[s1].weight + (*HT)[s2].weight;
    }
}

void HuffmanCoding(HuffmanTree HT, HuffmanCode *HC,int n){
    *HC = (HuffmanCode) malloc((n+1) * sizeof(char *));
    char *cd = (char *)malloc(n*sizeof(char));
    cd[n-1] = '\0';

    for(int i=1; i<=n; i++){
        int start = n-1;
        int c = i;
        int j = HT[i].parent;
        while(j != 0){
            if(HT[j].left == c)
                cd[--start] = '0';
            else
                cd[--start] = '1';
            c = j;
            j = HT[j].parent;
        }
        (*HC)[i] = (char *)malloc((n-start)*sizeof(char));
        strcpy((*HC)[i], &cd[start]);
    }
    free(cd);
}

void PrintHuffmanCode(HuffmanCode htable,int* w,int n, char* s)
{
    printf("Huffman code:\n");
    for (int i=0; i<strlen(s); i++){
        if (s[i]=='A') printf("%s",htable[1]);
        else if (s[i]=='T') printf("%s",htable[2]);
        else if (s[i]=='G') printf("%s",htable[3]);
        else if (s[i]=='C') printf("%s",htable[4]);
    }
    printf("\n");
}

void huffman(char* seq){
    int len=strlen(seq);
    int w[4];
    int n = 4;
    for(int i=0;i<4;i++){
        w[i]=0;
    }
    for (int i = 0; i < len; i++){
        switch (seq[i]) {
            case 'A':
                w[0]++;
                break;
            case 'T':
                w[1]++;
                break;
            case 'G':
                w[2]++;
                break;
            case 'C':
                w[3]++;
                break;
        }
    }
    HuffmanTree htree;
    HuffmanCode htable;
    CreateHuffmanTree(&htree, w, n);
    HuffmanCoding(htree, &htable, n);
    PrintHuffmanCode(htable,w, n, seq);
}