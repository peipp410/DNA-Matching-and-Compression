#ifndef CODE_PROJ_H
#define CODE_PROJ_H

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

void trie(char* seq);
void str_hash(char* s,char process);

#endif //CODE_PROJ_H
