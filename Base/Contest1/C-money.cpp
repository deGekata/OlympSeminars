#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <inttypes.h>
#include <string.h>
#include <assert.h>

int main() {
    int64_t N;
    scanf("%ld", &N);
    int64_t cur_sum = 0;
    for (int it = 0; it < N; ++it) {
        int temp;
        scanf("%d", &temp);
        if (temp > cur_sum + 1) {
            printf("%ld", cur_sum + 1);
            return 0;
        }
        cur_sum += temp;
    }
    printf("%ld", cur_sum + 1);
    return 0;
}