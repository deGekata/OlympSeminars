#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int ins_sort_size = 10;

int64_t merge(int64_t array[], int64_t const left, int64_t const mid,
              int64_t const right) {
    int64_t subArrLft = mid - left + 1;
    int64_t subArrRht = right - mid;
    int64_t inv_cnt = 0;

    int64_t *lArr = (int64_t *)calloc(sizeof(int64_t), subArrLft),
            *rArr = (int64_t *)calloc(sizeof(int64_t), subArrRht);

    for (int64_t i = 0; i < subArrLft; i++) lArr[i] = array[left + i];
    for (int64_t j = 0; j < subArrRht; j++) rArr[j] = array[mid + 1 + j];

    int64_t indSubArrL = 0, indSubArrR = 0;
    int64_t indMergeArr = left;

    while (indSubArrL < subArrLft && indSubArrR < subArrRht) {
        if (lArr[indSubArrL] >= rArr[indSubArrR]) {
            array[indMergeArr] = lArr[indSubArrL];
            indSubArrL++;
        } else {
            inv_cnt += subArrLft - indSubArrL;
            array[indMergeArr] = rArr[indSubArrR];
            indSubArrR++;
        }
        indMergeArr++;
    }

    while (indSubArrL < subArrLft) {
        array[indMergeArr] = lArr[indSubArrL];
        indSubArrL++;
        indMergeArr++;
    }

    while (indSubArrR < subArrRht) {
        array[indMergeArr] = rArr[indSubArrR];
        indSubArrR++;
        indMergeArr++;
    }

    free(lArr);
    free(rArr);
    return inv_cnt;
}


int64_t mergeSort(int64_t array[], int64_t begin, int64_t end) {
    if (begin >= end) return 0;

    int64_t mid = begin + (end - begin) / 2;
    int64_t inv_cnt = 0;
    inv_cnt += mergeSort(array, begin, mid);
    inv_cnt += mergeSort(array, mid + 1, end);
    inv_cnt += merge(array, begin, mid, end);
    return inv_cnt;
}

int main() {
    int64_t N, K;
    scanf("%ld %ld", &N, &K);
    int64_t *arr = (int64_t *)malloc(sizeof(int64_t) * 2 * K);

    for (int64_t it = 0; it < K; ++it) {
        scanf("%ld", arr + it);
    }
    N -= K;

    int64_t s_arr_size = 0;
    // for (s_arr_size = 0; s_arr_size < K && N > 0; s_arr_size++, N--) {
    //     scanf("%ld", arr + K + s_arr_size);
    // }

    // mergeSort(arr, 0, K + s_arr_size);
    mergeSort(arr, 0, K - 1);
    while (N > 0) {
        for (s_arr_size = 0; s_arr_size < K && N > 0; s_arr_size++, N--) {
            scanf("%ld", arr + K + s_arr_size);
        }
        mergeSort(arr, K, K + s_arr_size - 1);
#ifdef DEBUG
        for (int64_t it = 0; it < K + s_arr_size; ++it) {
            printf("%ld ", arr[it]);
        }
        printf("\n^^^^\n");
#endif
        merge(arr, 0, K - 1, K + s_arr_size - 1);
#ifdef DEBUG
        for (int64_t it = 0; it < K + s_arr_size; ++it) {
            printf("%ld ", arr[it]);
        }
        printf("\n------------------------------------\n");
#endif
        /* code */
    }

    // qsort(arr, N, sizeof(mypair), cmp);
    // int64_t inv_cnt =  mergeSort(arr, 0, N - 1);
    for (int64_t it = 0; it < K; ++it) {
        printf("%ld\n", arr[it]);
    }
    // printf("%ld", inv_cnt);

    return 0;
}
