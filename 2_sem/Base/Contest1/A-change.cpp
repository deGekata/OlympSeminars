#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <inttypes.h>
#include <string.h>


int main() {
    int cur_cnt = 0;
    int min_cnt = 0;
    int orders;
    scanf("%d", &orders);
    for (int it = 0; it < orders; ++it) {
        int temp;
        scanf("%d", &temp);
        if (temp == 5) {
            cur_cnt++;
        } else {
            cur_cnt -= (temp - 5) / 5;
        }
        if (cur_cnt < min_cnt) {
            min_cnt = cur_cnt;
        }
    }
    
    printf("%d", -min_cnt);
    return 0;
}