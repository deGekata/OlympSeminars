#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <inttypes.h>
#include <string.h>

int64_t binPowM(int64_t num, int64_t power, int64_t mod) {
    int64_t shft = 1;
    num %= mod;
    while (power) {
        if (power & 1) {
            shft = (shft * num) % mod;
        }
        num = (num * num) % mod;
        power >>= 1;
    }
    return shft;
}


int main() {
    int64_t power, arg_cnt, mod;
    scanf("%ld %ld %ld", &power, &arg_cnt, &mod);
    int64_t* coefs = (int64_t*) calloc(power + 1, sizeof(int64_t));
    for (int64_t it = 0; it < power + 1; ++it) {
        scanf ("%ld", coefs + (power - it));
    }

    for (int64_t it = 0; it < arg_cnt; ++it) {
        int64_t cur_ans = coefs[0], cur_val, base_val;
        scanf("%ld", &cur_val);
        base_val = cur_val;
        for (int64_t cur_part = 1; cur_part <= power; ++cur_part) {
            cur_ans = (cur_ans + cur_val * coefs[cur_part]) % mod;
            cur_val = (cur_val * base_val) % mod;
        }
        printf("%ld\n", cur_ans);
    }
    // printf("%ld\n", binPowM(3, 3, 5));
    return 0;
}