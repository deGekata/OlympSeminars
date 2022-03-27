#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <inttypes.h>
#include <string.h>
#include <assert.h>

#define MAX(a, b) (((a) < (b)) ? (b) : (a))

#define MIN(a, b) (((a) > (b)) ? (b) : (a))


int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    size_t* vals = (size_t*) malloc(sizeof(size_t) * N);
    for (int it = 0; it < N; ++it) {
        scanf("%lu", vals + it);
    }

    for (int it = 0; it < M; ++it) {
        size_t temp;
        scanf("%lu", &temp);
        size_t cur_sum = vals[0];
        for (int lhs = 0, rhs = 0; lhs < N && rhs < N;) {
            if (cur_sum == temp) {
                printf("%d %d\n", lhs + 1, rhs + 2);
                break;
            }

            if (lhs > rhs && lhs < N) {
                cur_sum += vals[++rhs];
                continue;
            }

            

            if (cur_sum < temp && rhs < N) {
                cur_sum += vals[++rhs];
            }

            if (cur_sum > temp) {
                cur_sum -= vals[lhs++];
            }
        }
        if (cur_sum != temp) {
            printf("Not found\n");
        }
    }

    return 0;
}