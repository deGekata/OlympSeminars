#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <inttypes.h>
#include <string.h>

int comp(const void* elem1, const void* elem2) {
    return *((char*)elem1) - *((char*)elem2);
}


int main() {
    char arr[1000] = {0};
    // char ans[1000] = {0};
    scanf("%s", arr);
    int N = strlen(arr);
    // printf("%s", arr);
    

    //last permutation
    // bool flag = false;
    // for (int it = 0; it < N - 1; ++it) {
    //     if (arr[it] > arr[it + 1]) {
    //         flag = true;
    //         break;
    //     }
    // }
    // if (flag) {
    //     for (int it = 0; it < N; ++it) {
    //         ans[it] = arr[N - it - 1];
    //     }
    //     printf("%s", ans);
    //     return 0;
    // }
    int swp_posel = 0;
    // int swp_poser = 0;
    for (int it = N - 1; it >= 0; --it) {
        for (int jit = it - 1; jit >= 0; --jit) {
            if (arr[jit] < arr[it]) {
                char tmp = arr[jit];
                arr[jit] = arr[it];
                arr[it] = tmp;
                swp_posel = jit;
                // swp_poser = it;
                jit = -1;
                it = -1;
            }
        }
    }

    qsort(arr + swp_posel + 1, N - swp_posel - 1, sizeof(char), comp);
    // printf("%d\n", swp_posel);
    // printf("%d\n", swp_poser);
    printf("%s", arr);

    return 0;
}


