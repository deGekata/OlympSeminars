#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int ins_sort_size = 10;


int64_t merge(int64_t array[], int64_t const left, int64_t const mid, int64_t const right)
{
	int64_t subArrLft = mid - left + 1;
	int64_t subArrRht = right - mid;
    int64_t inv_cnt = 0;
	
    
	int64_t *lArr = (int64_t*) calloc(sizeof(int64_t), subArrLft),
		    *rArr = (int64_t*) calloc(sizeof(int64_t), subArrRht);

	for (int64_t i = 0; i < subArrLft; i++)
		lArr[i] = array[left + i];
	for (int64_t j = 0; j < subArrRht; j++)
		rArr[j] = array[mid + 1 + j];

	int64_t indSubArrL = 0, indSubArrR = 0; 
	int64_t indMergeArr = left;

	while (indSubArrL < subArrLft && indSubArrR < subArrRht) {
		if (lArr[indSubArrL] <= rArr[indSubArrR]) {
			array[indMergeArr] = lArr[indSubArrL];
			indSubArrL++;
		}
		else {
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

int64_t mergeSort(int64_t array[], int64_t begin, int64_t end)
{
	if (begin >= end)
		return 0; 

	int64_t mid = begin + (end - begin) / 2;
    int64_t inv_cnt = 0;
	inv_cnt += mergeSort(array, begin, mid);
	inv_cnt += mergeSort(array, mid + 1, end);
	inv_cnt += merge(array, begin, mid, end);
    return inv_cnt;
}



/*
void ins_sort(int64_t *a, int64_t n) {
    for (int64_t i = 1; i < n; i++) {
        int64_t t = a[i], j;
        for (j = i - 1; j >= 0 && t < a[j]; j--) {
            a[j + 1] = a[j];
        }

        a[j + 1] = t;
    }
}

int64_t _merge_sort(int64_t *a, int64_t n, int64_t *t) {
    if (n == 1) {
        // ins_sort(a, n);
        return 0;
    }

    int64_t mid = n / 2;
    int64_t inv_cnt = 0;
    inv_cnt += _merge_sort(a, mid, t);
    inv_cnt += _merge_sort(a + mid, n - mid, t);

    memcpy(t, a, mid * sizeof(*a));

    int64_t k = 0, i, j;
    for (i = 0, j = mid; i < mid && j < n; k++) {
        if (t[i] <= a[j]) {
            // inv_cnt += mid - i;
            a[k] = t[i++];
        } else {
            inv_cnt += n - j;
            a[k] = a[j++];
        }
    }

    memcpy(a + k, t + i, (mid - i) * sizeof(*a));
    return inv_cnt;
}

int64_t merge_sort(int64_t *a, int64_t n) {
    if (n < 2) return 1;

    int64_t *tmp = (int64_t *)malloc((n / 2) * sizeof(*a));
    if (!tmp) return 0;

    int64_t inv_cnt =  _merge_sort(a, n, tmp);
    free(tmp);

    return inv_cnt;
}
*/


int main() {
    int64_t N;
    scanf("%ld", &N);
    int64_t *arr = (int64_t *) malloc(sizeof(int64_t) * N);
    for (int64_t it = 0; it < N; ++it) {
        scanf("%ld", arr + it);
        // arr[it].ord = it;
    }

    // qsort(arr, N, sizeof(mypair), cmp);
    int64_t inv_cnt =  mergeSort(arr, 0, N - 1);

    // for (int64_t it = 0; it < N; ++it) {
    //     printf("num:%ld \n", arr[it]);
    // }
    printf("%ld", inv_cnt);

    return 0;
}
