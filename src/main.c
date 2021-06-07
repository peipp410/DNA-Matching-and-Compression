#include "proj.h"

char seq[N];
int main(){
    FILE* f;
    char filename[100];
    printf("This is the implement of some algorithms of string matching and compression.\nTo get more information, please turn to our manual.\n");
    printf("Please input a fasta filename:");
    scanf("%s",filename);
    getchar();
    f=fopen(filename, "r"); //读入fasta
    while(fgets(seq, sizeof(seq), f)){
        if (seq[0]!='>') break;
    }
    fclose(f);
    f=fopen("output.txt", "w+");
    fclose(f);
    char c;
    printf("Please input a command (press q to quit):\n");
    while(scanf("%c",&c)) {
        getchar();
        if (c == 'q') break;
        else if (c == 'm') trie(seq);
        else if (c == 'p' || c == 'c') str_hash(seq, c);
        else if (c == 'h') huffman(seq);
    }
    return 0;
}
