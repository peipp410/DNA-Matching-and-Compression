#include "proj.h"

char seq[N];
int main(){
    FILE* f;
    f=fopen("NM000207.fasta", "r"); //读入fasta
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
    }
    return 0;
}