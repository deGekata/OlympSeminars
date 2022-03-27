#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <inttypes.h>
#include <string.h>
#include <assert.h>

#define MAX(a, b) (((a) < (b)) ? (b) : (a))

#define MIN(a, b) (((a) > (b)) ? (b) : (a))


int main() {
    int N, Q;
    scanf("%d %d", &N, &Q);

    int64_t* vals = (int64_t*) malloc(sizeof(int64_t) * N);
    int64_t* diff = (int64_t*) calloc(N + 1, sizeof(int64_t));
    for (int it = 0; it < N; ++it) {
        scanf("%lu", vals + it);
    }
    int64_t l, r, x;
    for (int it = 0; it < Q; ++it) {
        scanf("%ld %ld %ld", &l, &r, &x);
        diff[l] += x;
        diff[r + 1] -= x;
    }

    int64_t cur_diff = 0;
    for (int it = 0; it < N; ++it) {
        cur_diff += diff[it];
        vals[it] += cur_diff;    
    }

    for (int it = 0; it < N; ++it) {
        printf("%ld ", vals[it]);
    }

    free(vals);
    free(diff);

    return 0;
}