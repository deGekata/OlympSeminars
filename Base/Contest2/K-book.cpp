#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>

int main() {
    uint64_t toms_cnt = 0, list_cnt = 0;
    scanf("%lu %lu", &toms_cnt, &list_cnt);

    uint32_t* chapters = 1 + (uint32_t*) calloc(list_cnt + 1, sizeof(uint32_t));
    uint64_t mx_lst = 0;
    uint32_t tmp_val = 0;



    for (int64_t curList = 0; curList < list_cnt; curList++) {
        scanf("%u", &tmp_val);
        mx_lst = (tmp_val > mx_lst) ? tmp_val : mx_lst;
        chapters[curList] = chapters[curList - 1] + tmp_val;
    }

    int64_t lft  = mx_lst, rht = chapters[list_cnt - 1], mid = 0, ans = 0;

    while (lft <= rht) {
        mid = (lft + rht) / 2;
        int64_t lst_tom_ind   = 0, cur_tom_cnt = 0;

        for (uint32_t curList = 0; curList < list_cnt; curList++) {
            if ((chapters[curList] - chapters[lst_tom_ind - 1]) > mid) {
                lst_tom_ind = curList;
                cur_tom_cnt++;
            }
        }
        cur_tom_cnt++;

        if (cur_tom_cnt > toms_cnt) {
            lft = mid + 1;
        } else {
            ans = mid;
            rht = mid - 1;
        }
    }

    printf("%ld\n", ans); 

    free(chapters - 1);

    return 0;
}