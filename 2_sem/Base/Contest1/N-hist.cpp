#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <inttypes.h>
#include <string.h>

#define MAX(a, b) (((a) < (b)) ? (b) : (a))

#define MIN(a, b) (((a) > (b)) ? (b) : (a))


int main() {
    int64_t N;
    scanf("%ld", &N);
    
    int64_t* arr = (int64_t*) malloc(N * sizeof(int64_t));
    for (int64_t it = 0; it < N; ++it) {
        scanf("%ld", arr + it);
    }

    int64_t lhs, rhs, prev = 0, space, ans = 0;
    for (int it = 0; it  < N; ++it) {
        lhs = rhs = it;

        if (it != 0) {
            if (arr[it] == arr[it - 1]) {
                continue;
            }

            if (arr[it] < arr[it - 1]) {
                lhs = prev;
            }
        }

        while(lhs && arr[lhs - 1] >= arr[it]) {
            lhs--;
        }

        while(rhs < N - 1 && arr[rhs + 1] >= arr[it]) {
            rhs++;
        }

        space = (rhs - lhs + 1) * arr[it];
        ans = MAX(ans, space);
        prev = lhs;
    }

    printf("%ld", ans);
    free(arr);
    return 0;
}