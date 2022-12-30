#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
    int weight;
    int parent, left, right;
}HTNode, *HuffmanTree;
typedef char ** HuffmanCode;

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

void PrintHuffmanCode(HuffmanCode htable,int* w,int n, char* s){
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