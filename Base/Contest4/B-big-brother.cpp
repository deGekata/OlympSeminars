#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>



uint64_t round_2pow(uint64_t sz) {
    for (uint64_t cur_pow = 0; cur_pow < 65; ++cur_pow) {
        if ((1 << cur_pow) >= sz) {
            return (1 << cur_pow); 
        }
    }

    return 3;
}

void create_tree(int64_t* data, uint64_t sz, uint64_t ind, int64_t* mx) {
    if (ind >= sz) {
        *mx = data[ind];
        return;
    }

    int64_t mx1 = 0, mx2 = 0;
    create_tree(data, sz, 2 * ind, &mx1);
    create_tree(data, sz, 2 * ind + 1, &mx2);

    data[ind] = (mx1 > mx2) ? mx1 : mx2;

    *mx = data[ind];
}

void change_at(int64_t* arr, uint64_t sz, uint64_t ind, int64_t n_val) {
    ind += sz;
    
    arr[ind] = n_val;

    ind >>= 1;

    while (ind) {
        arr[ind] = (arr[2 * ind] > arr[2 * ind + 1]) ? arr[2 * ind] : arr[2 * ind + 1]; 

        ind >>= 1;
    }
}

int64_t get_val(int64_t* data, uint64_t sz, uint64_t ind, uint64_t n_ind, int64_t value, uint64_t lft, uint64_t rht) {
    if (ind >= sz) {
        return (1 + ind - sz);
    }

    uint64_t mid = (rht + lft) >> 1;
    int64_t ret = INT64_MAX;

    if ((data[2 * ind] >= value) && (mid >= n_ind)) {
        int64_t l_tree_ret = get_val(data, sz, 2 * ind, n_ind, value, lft, mid);

        ret = (ret >= l_tree_ret) ? l_tree_ret : ret;
    }

    ++mid;
    if ((ret == INT64_MAX) && (data[2 * ind + 1] >= value)) {
        int64_t r_tree_ret = get_val(data, sz, 2 * ind + 1, n_ind, value, mid, rht);
        
        ret = (ret < r_tree_ret) ?
                    ret : r_tree_ret;
    }
    
    return ret;
}   

int main() {
    uint32_t size = 0, oper_cnt = 0;

    scanf("%u %u", &size, &oper_cnt);
    uint64_t rnd_size = round_2pow(size);
    int64_t* arr = (int64_t*) calloc(2 * rnd_size, sizeof(int64_t));
    for (uint64_t cur_ind = 0; cur_ind < size; cur_ind++) {
        scanf("%ld", &arr[rnd_size + cur_ind]);
    }

    int64_t tr = 0;
    create_tree(arr, rnd_size, 1, &tr);

    for (uint64_t cur_op_num = 0; cur_op_num < oper_cnt; cur_op_num++) {
        
        uint32_t op_name = 0, op_ind = 0;
        int64_t opElem = 0;
        scanf("%u %u %ld", &op_name, &op_ind, &opElem);

        if (op_name) {
            int64_t ret_val = get_val(arr, rnd_size, 1, op_ind - 1, opElem, 0, rnd_size - 1);
            ret_val = (ret_val == INT64_MAX) ? -1 : ret_val;
            printf("%ld\n", ret_val);
        } else {
            change_at(arr, rnd_size, op_ind - 1, opElem);
        }
    }

    free(arr);

    return 0;
}