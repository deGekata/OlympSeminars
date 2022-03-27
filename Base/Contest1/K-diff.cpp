#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <inttypes.h>
#include <string.h>
#include <ctype.h>

int comp(const void* lft, const void* rht) {
    if (*(size_t*)lft > *(size_t*)rht) return 1;
    if (*(size_t*)lft < *(size_t*)rht) return -1;
    return 0;

}


int main() {
    size_t* arr1 = (size_t*) malloc(sizeof(size_t) * 150000);
    size_t* arr2 = (size_t*) malloc(sizeof(size_t) * 150000);

    size_t temp = 1;
    int offs = 0;
    while (temp) {
        scanf("%lu", &temp);
        arr1[offs++] = temp;
    }
    int size1 = --offs;

    temp = 1;
    offs = 0;
    while (temp) {
        scanf("%lu", &temp);
        arr2[offs++] = temp;
    }
    int size2 = --offs;

    qsort(arr1, size1, sizeof(size_t), comp);
    qsort(arr2, size2, sizeof(size_t), comp);

    // for (int it = 0; it < size1; ++it) {
    //     printf("%lu ", arr1[it]);
    // }
    // printf("\n");

    // for (int it = 0; it < size2; ++it) {
    //     printf("%lu ", arr2[it]);
    // }
    // printf("\n");


    int cur1 = 0, cur2 = 0;
    while (cur1 < size1 && cur2 < size2) {
        if (arr1[cur1] == arr2[cur2]) {
            cur1++, cur2++;
            continue;
        }
        if (arr1[cur1] < arr2[cur2]) {
            printf("%ld ", arr1[cur1++]);
            continue;
        }

        if (arr1[cur1] > arr2[cur2]) {
            printf("%ld ", arr2[cur2++]);
            continue;
        }
    }
    
    for (; cur1 < size1; ++cur1) {
        printf("%ld ", arr1[cur1]);
    }

    for (; cur2 < size2; ++cur2) {
        printf("%ld ", arr2[cur2]);
    }

    return 0;
}
