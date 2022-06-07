#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main() {
    uint32_t min_size = 0, max_size = 0, len = 0;

    scanf("%u %u %u", &min_size, &max_size, &len);

    uint32_t** min_arrs = (uint32_t**) calloc(min_size, sizeof(uint32_t*));
    uint32_t** max_arrs = (uint32_t**) calloc(max_size, sizeof(uint32_t*));

    for (uint32_t cur_it = 0; cur_it < min_size; cur_it++) {
        min_arrs[cur_it] = (uint32_t*) calloc(len, sizeof(uint32_t));
        for (uint32_t it = 0; it < len; it++) {
            scanf("%u", min_arrs[cur_it] + it);
        }
    }

    for (uint32_t cur_it = 0; cur_it < max_size; cur_it++) {
        max_arrs[cur_it] = (uint32_t*) calloc(len, sizeof(uint32_t));
        for (uint32_t it = 0; it < len; it++) {
            scanf("%u", max_arrs[cur_it] + it);
        }
    }

    uint32_t rAmount = 0;
    scanf("%u", &rAmount);
    
    uint32_t* answers = (uint32_t*) calloc(rAmount, sizeof(uint32_t));

    for (uint32_t curReq = 0; curReq < rAmount; curReq++) {
        uint32_t min_index = 0, max_index = 0;

        scanf("%u %u", &min_index, &max_index);
        min_index--, max_index--;

        int32_t lft  = 0, rht = len - 1, mid = 0;

        uint32_t answer = 0;

        while (lft <= rht) {
            mid = (lft + rht) / 2;
            int32_t delta = (int32_t)min_arrs[min_index][mid] - (int32_t)max_arrs[max_index][mid];

            if (delta < 0) {
                lft = mid + 1;
            } else if (delta > 0) {
                rht = mid - 1;
            } else {
                break;
            }
        }

        int32_t delta1 = INT32_MAX;
        if (mid > 0) {
            delta1 = (min_arrs[min_index][mid - 1] > max_arrs[max_index][mid - 1]) ? min_arrs[min_index][mid - 1] : max_arrs[max_index][mid - 1];
        }

        int32_t delta2 = (min_arrs[min_index][mid] > max_arrs[max_index][mid]) ? min_arrs[min_index][mid] : max_arrs[max_index][mid];

        int32_t delta3 = INT32_MAX;
        if (mid < len - 1) {
            delta3 = (min_arrs[min_index][mid + 1] > max_arrs[max_index][mid + 1]) ? min_arrs[min_index][mid + 1] : max_arrs[max_index][mid + 1];
        }

        answer = (delta1  <= delta2) ? mid - 1 : mid;
        delta1  = (delta1  < delta2) ? delta1 : delta2;
        answer = (delta1 <= delta3) ? answer : mid + 1;
        
        answers[curReq] = answer + 1;
    }

    for (uint32_t curReq = 0; curReq < rAmount; curReq++) printf("%u\n", answers[curReq]);

    for (uint32_t curA = 0; curA < min_size; curA++) free(min_arrs[curA]);

    for (uint32_t curB = 0; curB < max_size; curB++) free(max_arrs[curB]);

    free(min_arrs);
    free(max_arrs);
    free(answers);
    return 0;
}