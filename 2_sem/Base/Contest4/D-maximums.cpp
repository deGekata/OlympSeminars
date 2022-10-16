#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct Elem{
    int32_t mx_post;
    int32_t mx_pref;
    int32_t ans;
    int32_t sum;
};

template <class T> const T& mmax (const T& a, const T& b) {
  return (a<b)?b:a;
}


uint64_t round_2pow(uint64_t size) {
    for (uint64_t cur_pow = 0; cur_pow < 65; cur_pow++) {
        if ((1LLU << cur_pow) >= size) {
            return 1 << cur_pow; 
        }
    }

    return 3;
}

int32_t reinit_ans(Elem* el1, Elem* el2, Elem* res) {
    if (res) {
        res->sum = el1->sum + el2->sum;
        res->mx_pref  = mmax(el1->mx_pref, el1->sum + el2->mx_pref);
        res->mx_post = mmax(el2->mx_post, el2->sum + el1->mx_post);
    }

    return mmax(mmax(el1->ans, el2->ans), el1->mx_post + el2->mx_pref);
}

Elem* tree_ctor(Elem* arr, const uint64_t size, const uint64_t index) {
    if (index >= size) {
        return arr + index;
    }

    tree_ctor(arr, size, 2 * index);
    tree_ctor(arr, size, 2 * index + 1);

    arr[index].sum  = arr[2 * index].sum + arr[2 * index + 1].sum;
    arr[index].ans  = reinit_ans(arr + 2 * index, arr + 2 * index + 1, arr + index);

    return arr + index;
}

void edit_val(Elem* arr, uint64_t size, uint64_t index, int32_t newValue) {
    index += size;
    
    arr[index].sum      = newValue,
    arr[index].mx_post  = newValue,
    arr[index].mx_pref  = newValue,
    arr[index].ans      = newValue;

    index >>= 1;

    while (index) {
        arr[index].sum     = arr[2 * index].sum + arr[2 * index + 1].sum;
        arr[index].ans  = reinit_ans(arr + 2 * index, arr + 2 * index + 1, arr + index);

        index >>= 1;
    }
}

Elem* get_val(Elem* arr, uint64_t index, uint64_t lft, uint64_t rht, uint64_t cur_lft, uint64_t cur_rht) {
    if ((lft <= cur_lft) && (rht >= cur_rht)) {
        return arr + index;
    }

    uint64_t mid = (cur_lft + cur_rht) >> 1;

    Elem* lft_ret  = NULL, *rht_ret = NULL;

    if (lft <= mid) {
        lft_ret = get_val(arr, 2 * index, lft, (mid < rht) ? mid : rht, cur_lft, mid);
    }

    mid++;

    if (rht >= mid) {
        rht_ret = get_val(arr, 2 * index + 1, (lft > mid) ? lft : mid, rht, mid, cur_rht);
    }

    Elem* retElem = NULL;

    if (lft_ret && rht_ret) {
        retElem = (Elem*) calloc(1, sizeof(Elem));

        retElem->ans = reinit_ans(lft_ret, rht_ret, retElem);
    } else {
        if (lft_ret) {
            retElem = lft_ret;
        } else {
            retElem = rht_ret;
        }
    }

    return retElem;
}   

void tree_ctor_(Elem* arr, uint64_t sz) {
    tree_ctor(arr, sz, 1);
    return;
}

int main() {
    unsigned int size, oper_cnt;
    size = oper_cnt = 0;

    scanf("%u", &size);
    uint64_t pow2_size = round_2pow(size);

    scanf("%u", &oper_cnt);


    Elem* arr = (Elem*) calloc(2 * pow2_size, sizeof(Elem));

    for (uint32_t ind = 0; ind < size; ind++) {
        scanf("%d", &arr[pow2_size + ind].sum);

        arr[pow2_size + ind].ans  = arr[pow2_size + ind].sum;
        arr[pow2_size + ind].mx_post = arr[pow2_size + ind].sum;
        arr[pow2_size + ind].mx_pref  = arr[pow2_size + ind].sum;
    }

    tree_ctor_(arr, pow2_size);

    int32_t cur_cmd = 0, n_val = 0;
    uint64_t left  = 0, right = 0, ind   = 0;
    
    for (uint32_t cur_op = 0; cur_op < oper_cnt; cur_op++) {
        scanf("%d", &cur_cmd);

        if (cur_cmd == 2) {
            scanf("%lu %lu", &left, &right);

            Elem* answer = get_val(arr, 1, left, right, 0, pow2_size - 1);
            printf("%d\n", answer->ans);

            if ((answer < arr) || (answer > (-1 + arr + pow2_size * 2))) {
                free(answer);
            }
        } else {
            scanf("%lu %d", &ind, &n_val);
            edit_val(arr, pow2_size, ind, n_val);
        }
    }

    free(arr);
}