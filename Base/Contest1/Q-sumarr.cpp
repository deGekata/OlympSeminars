#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <inttypes.h>
#include <string.h>
#include <assert.h>

#define MAX(a, b) (((a) < (b)) ? (b) : (a))

#define MIN(a, b) (((a) > (b)) ? (b) : (a))

int main() {
    int64_t mx_s, cur_sm = 0, N;
    scanf("%ld", &N);
    assert(N != 1);    
    int64_t temp = 0;
    scanf("%ld", &temp);
    char flag = 0;
    int64_t mx_mis = temp;
    if (temp >= 0) flag = 1;
    mx_s = temp, cur_sm = temp;
    if (cur_sm < 0) {
            mx_s = MAX(mx_s, cur_sm);
            cur_sm = 0;
    }
    for (int64_t it = 1; it < N; ++it) {
        scanf("%ld", &temp);
        if (temp >= 0) flag = 1;
        mx_mis = MAX(mx_mis, temp);
        cur_sm += temp;
        mx_s = MAX(mx_s, cur_sm);
        if (cur_sm < 0) {
            mx_s = MAX(mx_s, cur_sm);
            cur_sm = 0;
        }
        mx_s = MAX(mx_s, cur_sm);
    }

    if (flag == 0) {
        printf("%ld", mx_mis);
        return 0;
    }
    printf("%ld", mx_s);
    return 0;
}