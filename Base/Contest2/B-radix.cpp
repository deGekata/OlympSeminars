#include <stdlib.h>
#include <stdio.h>
#include <string.h>
struct pair {
    int count;
    unsigned char sym;
};



int myStrCmp (const char *s1, const char *s2) {
    const char *p1 = (const char *)s1;
    const char *p2 = (const char *)s2;
    char myStrBuff1[210];
    char myStrBuff2[210];

    strcpy(myStrBuff1, p1);
    strcpy(myStrBuff1 + strlen(p1), p2);

    strcpy(myStrBuff2, p2);
    strcpy(myStrBuff2 + strlen(p2), p1);

    return strcmp(myStrBuff1, myStrBuff2);

    // printf("%s st\n", myStrBuff1);
    // while (*p1 != '\0') {
    //     if (*p2 == '\0') return -1;
    //     if (*p2 > *p1)   return -1;
    //     if (*p1 > *p2)   return 1;

    //     p1++;
    //     p2++;
    // }

    // if (*p2 != '\0') return 11;

    return 0;
}

int cmp(const void* lft, const void* rht) {
    char *lst = *(char**)lft;
    char *rst = *(char**)rht;
    return -myStrCmp(*(char**)lft, *(char**)rht);
}

int main() {

    char* arr[120];
    
    char* buff;
    int cur_ind = 0;
    // printf("%d", scanf("%ms", &buff));
    // return 0;
    while (scanf("%ms", &buff) != -1) {
        arr[cur_ind++] = buff;
    }
    // printf("kek");

    // for (int it = 0; it < cur_ind; ++it) {
    //     printf("%s\n", arr[it]);
    // }

    qsort(arr, cur_ind, sizeof(char*), cmp);
    // printf("---------\n");
    for (int it = 0; it < cur_ind; ++it) {
        printf("%s", arr[it]);
    }
    return 0;
    
}
