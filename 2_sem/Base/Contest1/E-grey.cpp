#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <inttypes.h>
#include <string.h>
#include <assert.h>

#define MAX(a, b) (((a) < (b)) ? (b) : (a))

#define MIN(a, b) (((a) > (b)) ? (b) : (a))



void grey_code(int all_len, int cur_len, char* buff, char reverse) {
    if (cur_len == all_len) {
        printf(buff);
        return;
    }

    buff[cur_len] = '0' + reverse;
    grey_code(all_len, cur_len + 1, buff, 0);
    buff[cur_len] = '1' - reverse;
    grey_code(all_len, cur_len + 1, buff, 1);

    return;
}
/*
buff[cur_len] = '0' + reverse;
grey_code(all_len, cur_len + 1, buff, reverse);
buff[cur_len] = '1' - reverse;
grey_code(all_len, cur_len + 1, buff, !reverse);
*/

/*
if (!reverse) {
        0;
        buff[cur_len] = '0' + reverse;
        grey_code(all_len, cur_len + 1, buff, reverse);0;
        buff[cur_len] = '1' - reverse;
        grey_code(all_len, cur_len + 1, buff, !reverse);1;
    } else {
        1;
        buff[cur_len] = '1' - rev;
        grey_code(all_len, cur_len + 1, buff, !reverse);0;
        buff[cur_len] = '0';
        grey_code(all_len, cur_len + 1, buff, reverse);1;
    }
*/
int main() {
    int N;
    scanf("%d", &N);
    char* buff  = (char*) malloc(sizeof(char) * (N + 5));
    buff[N] = '\n'; 
    buff[N + 1] = '\0'; 
    grey_code(N, 0, buff, 0);
    return 0;
}