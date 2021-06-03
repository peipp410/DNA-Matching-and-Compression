#include "proj.h"

char seq[N];
int main(){
    FILE* f;
    char filename[100];
    scanf("%s",filename);
    getchar();
    f=fopen(filename, "r"); //读入fasta
    while(fgets(seq, sizeof(seq), f)){
        if (seq[0]!='>') break;
    }
    fclose(f);
    char c;
    while(scanf("%c",&c)){
        getchar();
        if (c=='q') break;
        else if (c=='m') trie(seq);
        else if (c=='p' || c=='c') str_hash(seq,c);
        else if (c=='h') huffman(seq);
    }
    return 0;
}