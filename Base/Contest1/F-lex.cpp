#include "stdio.h"

size_t find_order(size_t N, size_t K) {
    size_t posi = 0, 
           mn = -1, 
           mx = (K - 1) * 10 + 9;

    for (size_t i = K; i > 0; i /= 10) {
        posi += i + 1;
    }

    for (mn = 1; mn <= K; mn *= 10) {
        posi -= mn;
    }

    while (mn <= N) {
        if (mx > N) return posi + N - mn + 1;
        posi += mx - mn + 1;
        mx = mx * 10 + 9;
        mn *= 10;
    }
    return posi;
}

int main() {
    size_t N = -1, K = -1;

    scanf("%lu %lu", &N, &K);

    size_t len = -1;
    for (size_t i = 1; i <= N; i *= 10) ++len;

    size_t ans = find_order(N, K);
    printf("%lu\n", ans);

    return 0;
}