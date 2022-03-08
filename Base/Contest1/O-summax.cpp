#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <inttypes.h>
#include <string.h>

#define MAX(a, b) (((a) < (b)) ? (b) : (a))

#define MIN(a, b) (((a) > (b)) ? (b) : (a))

int main() {
    int N;
    scanf("%d", &N);
    int64_t* arr1 = (int64_t*) malloc(sizeof(int64_t) * N);
    int64_t* arr2 = (int64_t*) malloc(sizeof(int64_t) * N);
    int64_t* pref_maxflft = (int64_t*) malloc(sizeof(int64_t) * N);
    int64_t* pref_maxfrht = (int64_t*) malloc(sizeof(int64_t) * N);
    
    for (int it = 0; it < N; ++it) {
        scanf("%ld", arr1 + it);
    }

    for (int it = 0; it < N; ++it) {
        scanf("%ld", arr2 + it);
    }

    int64_t cur_maxL = arr1[0];
    for (int it = 0; it < N; ++it) {
        if (cur_maxL <= arr1[it]) {
            pref_maxflft[it] = arr1[it];
            cur_maxL = arr1[it];
            arr1[it] = it;
            continue;
        }
        pref_maxflft[it] = cur_maxL;
        if (it > 0)
            arr1[it] = arr1[it - 1];
    }

    int64_t cur_maxR = arr2[N - 1];
    for (int it = N - 1; it >= 0; --it) {
        if (cur_maxR <= arr2[it]) {
            pref_maxfrht[it] = arr2[it];
            cur_maxR = arr2[it];
            arr2[it] = it;
            continue;
        }
        pref_maxfrht[it] = cur_maxR;
        if (it < N - 1 )
            arr2[it] = arr2[it + 1];
    }

    
    int index1 = 0, index2 = N-1;
    // for (int it = 0; it < N; ++it) {
    //     printf("\t%ld, %d ind  ", pref_maxflft[it], arr1[it]);
    // }
    // printf("  lft\n");

    // for (int it = 0; it < N; ++it) {
    //     printf("\t%ld, %d ind  ", pref_maxfrht[it], arr2[it]);
    // }
    // printf("   rht\n");
    int64_t mx_sum = pref_maxflft[0] + pref_maxfrht[0];
    for (int it = N - 1; it >= 0; --it) {
        if (mx_sum == pref_maxflft[it] + pref_maxfrht[it]) {
            index1 = arr1[it];
            index2 = arr2[it];
            continue;
        }
        if (mx_sum < pref_maxflft[it] + pref_maxfrht[it]) {
            mx_sum = pref_maxflft[it] + pref_maxfrht[it];
            index1 = arr1[it];
            index2 = arr2[it];
        }
        
    }

    // printf("%ld\n", mx_sum);
    printf("%d %d", index1, index2);

    free(arr1);
    free(arr2);
    free(pref_maxflft);
    free(pref_maxfrht);

    return 0;
}