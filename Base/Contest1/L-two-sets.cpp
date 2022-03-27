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
    int size1, size2;
    scanf("%d", &size1);
    scanf("%d", &size2);

    int64_t* arr1 = (int64_t*) malloc(sizeof(int64_t) * size1);
    int64_t* arr2 = (int64_t*) malloc(sizeof(int64_t) * size2);

    for (int it = 0; it < size1; ++it) {
        scanf("%ld", arr1 + it);
    }

    for (int it = 0; it < size2; ++it) {
        scanf("%ld", arr2 + it);
    }


    int cur1 = 0, cur2 = 0;
    while (cur1 < size1 && cur2 < size2) {
        if (arr1[cur1] == arr2[cur2]) {
            printf("%ld ", arr1[cur1]);
            cur1++, cur2++;
            continue;
        }
        if (arr1[cur1] < arr2[cur2]) {
            cur1++;
            continue;
        }

        if (arr1[cur1] > arr2[cur2]) {
            cur2++;
            continue;
        }
    }
    
    // for (; cur1 < size1; ++cur1) {
    //     printf("%ld ", arr1[cur1]);
    // }

    // for (; cur2 < size2; ++cur2) {
    //     printf("%ld ", arr2[cur2]);
    // }

    return 0;
}
