#include <inttypes.h>
#include <stdlib.h>

int64_t merge(int64_t array[], int64_t const left, int64_t const mid,
              int64_t const right) {
    int64_t subArrLft = mid - left + 1;
    int64_t subArrRht = right - mid;
    int64_t inv_cnt = 0;

    int64_t *lArr = (int64_t *) calloc(sizeof(int64_t), subArrLft),
            *rArr = (int64_t *) calloc(sizeof(int64_t), subArrRht);

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
