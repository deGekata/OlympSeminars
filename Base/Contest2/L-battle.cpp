#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

int64_t destroy_panels(int64_t *HP, 
                       int64_t cnt, 
                       int64_t main_target,
                       int64_t splash,
                       int64_t ans) {

    int64_t d_dmg = main_target - splash, basic_hits_left = ans;
    for (int64_t dragon = 0; dragon < cnt; ++dragon) {
        if (HP[dragon] - splash * ans > 0) {
            basic_hits_left -= (HP[dragon] - splash * ans + d_dmg - 1) / d_dmg;
        }
    }
    return basic_hits_left;
}

int64_t find_ans(int64_t *HP, int64_t cnt, int64_t main_target, int64_t splash, int64_t max_hits) {
    int64_t min_hits = 0;
    int64_t ans = 0;
    while (min_hits + 1 < max_hits) {
        ans = (min_hits + max_hits) >> 1;
        int64_t check_result = destroy_panels(HP, cnt, main_target, splash, ans);
        if (check_result >= 0) {
            max_hits = ans;
        } else if (check_result < 0) {
            min_hits = ans;
        }
    }
    return max_hits;
}

int main() {
    int64_t n = 0, p = 0, q = 0;
    int64_t max_healthpoints = 0;
    
    scanf("%ld %ld %ld", &n, &p, &q);
    
    int64_t *HP = (int64_t*) calloc(n, sizeof(int64_t));

    for (int64_t i = 0; i < n; ++i) {
        scanf("%ld", HP + i);
        max_healthpoints = (HP[i] > max_healthpoints) ? HP[i] : max_healthpoints;
    }

    int64_t max_hits = max_healthpoints / q;
    max_hits += (max_hits * q) != max_healthpoints;

    if (p == q) {
        printf("%ld\n", max_hits);
        return 0;
    }

    printf("%ld\n", find_ans(HP, n, p, q, max_hits));
    return 0;
}

