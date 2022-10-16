#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct pr {
    int even;
    int odd;
};



inline int MAX(int lft, int rht) {
    return lft > rht ? lft : rht;
}

unsigned long long int upper_2pow(unsigned long long int size) {
    for (unsigned long long int curPower = 0; curPower < 65; curPower++) {
        if ((1LLU << curPower) >= size) {
            return (1 << curPower); 
        }
    }

    return 3;
}

void tree_ctor(pr* data, unsigned long long int capacity, unsigned long long int cur_pos) {
    if (cur_pos >= capacity) {
        return;
    }

    tree_ctor(data, capacity, 2 * cur_pos);
    tree_ctor(data, capacity, 2 * cur_pos + 1);

    data[cur_pos].even = data[2 * cur_pos].even + data[2 * cur_pos + 1].even;
    data[cur_pos].odd  = data[2 * cur_pos].odd  + data[2 * cur_pos + 1].odd;

    return;
}

void set_val(pr* arr, unsigned long long int size, unsigned long long int index, int n_val) {
    index += size;
    
    if (index % 2) {
        arr[index].even = 0;
        arr[index].odd  = n_val;
    } else {
        arr[index].odd  = 0;
        arr[index].even = n_val;
    }

    index >>= 1;

    while (index) {
        arr[index].odd  = arr[2 * index].odd  + arr[2 * index + 1].odd;
        arr[index].even = arr[2 * index].even + arr[2 * index + 1].even;

        index >>= 1;
    }
}

pr* get_val(pr* arr, unsigned long long int index, unsigned long long int left, unsigned long long int right, unsigned long long int lft, unsigned long long int rht) {
    if ((left <= lft) && (right >= rht)) {
        return arr + index;
    }

    unsigned long long int mid = (lft + rht) / 2;

    pr* rht_ch = NULL, *lft_ch = NULL;

    if (left <= mid) {
        lft_ch = get_val(arr, 2 * index, left, (mid < right) ? mid : right, lft, mid);
    }
    mid++;
    if (right >= mid) {
        rht_ch = get_val(arr, 2 * index + 1, MAX(left, mid), right, mid, rht);
    }

    pr* retElem = NULL;

    if (lft_ch != NULL && rht_ch != NULL) {
        retElem = (pr*) calloc(1, sizeof(pr));

        retElem->even = lft_ch->even + rht_ch->even; 
        retElem->odd  = lft_ch->odd  + rht_ch->odd;
    }
    else {
        if (lft_ch) {
            retElem = lft_ch;
        }
        else {
            retElem = rht_ch;
        }
    }

    return retElem;
}   

int main() {
    uint arrSize    = 0;
    scanf("%u", &arrSize);

    unsigned long long int round_sz = upper_2pow(arrSize);

    pr* arr = (pr*) calloc(2 * round_sz, sizeof(pr));

    for (uint curElem = 0; curElem < arrSize; curElem++) {
        int tempValue = 0;

        scanf("%d", &tempValue);

        if (curElem % 2 == 0) {
            arr[round_sz + curElem].even = tempValue;
        }
        else {
            arr[round_sz + curElem].odd = tempValue;
        }
    }

    tree_ctor(arr, round_sz, 1);
    
    uint rqstAmount = 0;
    scanf("%u", &rqstAmount);
    unsigned long long int left  = 0, right = 0;
    unsigned long long int index   = 0;
    int newValue = 0;
    
    for (uint curRqst = 0; curRqst < rqstAmount; curRqst++) {
        int curCmd = 0;
        scanf("%d", &curCmd);

        switch (curCmd) {
            case 0: {       
                scanf("%lu %d", &index, &newValue);
                index--;
                set_val(arr, round_sz, index, newValue);
            break;

            case 1: 
                scanf("%lu %lu", &left, &right);
                right--, left--;
                pr* answer = get_val(arr, 1, left, right, 0, round_sz - 1);
                int res = 0;
                if (left % 2) {
                    res = answer->odd - answer->even;
                } else {
                    res = answer->even - answer->odd;
                }

                printf("%d\n", res);

                if ((answer < arr) || (answer > (arr + 2 * round_sz - 1))) {
                    free(answer);
                }
            }
            break;
        }
    }

    free(arr);
}