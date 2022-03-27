#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <inttypes.h>
#include <string.h>
#include <assert.h>

#define MAX(a, b) (((a) < (b)) ? (b) : (a))

#define MIN(a, b) (((a) > (b)) ? (b) : (a))

typedef struct pair {
    int64_t val;
    int index;
} pair;

int comp(const void* lhs, const void* rhs) {
    if (((pair*)lhs)->val > ((pair*)rhs)->val) return 1;
    if (((pair*)lhs)->val < ((pair*)rhs)->val) return -1;
    return 0;
}


int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    pair* vals = (pair*) malloc(sizeof(pair) * N);
    for (int it = 0; it < N; ++it) {
        scanf("%ld", (int64_t*)(vals + it));
        vals[it].index = it;
    }
    qsort(vals, N, sizeof(pair), comp);
    // for (int it = 0; it < N; ++it) {
    //     printf("%ld, %d\n", vals[it].val, vals[it].index);
    // }

    for (int it = 0; it < M; ++it) {
        int64_t temp;
        // printf("inp\n");
        scanf("%ld", &temp);
        // printf("vals %ld, %ld\n", vals[0].val, vals[N-1].val);
        int64_t cur_sum = vals[0].val + vals[N - 1].val;
        int lhs = 0, rhs = N - 1;
        int prev_l = -1, prev_r = -1;
        int64_t min_elem = vals[N - 1].val;
        while (lhs != rhs) {
            if (cur_sum > temp) {
                cur_sum = vals[lhs].val + vals[--rhs].val;
                continue;
            }

            if (cur_sum < temp) {
                cur_sum = vals[++lhs].val + vals[rhs].val;
                continue;
            }

            int64_t cur_min = MIN(vals[lhs].val, vals[rhs].val);
            if (min_elem > cur_min) {
                min_elem = cur_min;
                prev_l = lhs;
                prev_r = rhs;
            }
            
            cur_sum = vals[lhs].val + vals[--rhs].val;
            /* code */
        }
        if (prev_l != -1) {
            printf("%ld %ld\n", MIN(vals[prev_l].val, vals[prev_r].val), MAX(vals[prev_l].val, vals[prev_r].val));
        } else {
            printf("Not found\n");
        }
        
    }

    return 0;
}