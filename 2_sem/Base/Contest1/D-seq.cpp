#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <inttypes.h>
#include <string.h>

char get_sym(int N, int pos, int leng[], int len) {
    if (pos != 0) {
        return get_sym(N - 1, (pos - 1) % leng[N - 1], leng, len);
    }
    
    return 'a' + N;
}

int main() {
    int leng[] = {1, 3, 7, 15, 31, 63, 127, 255, 511, 1023, 2047, 4095, 8191, 16383, 32767, 
                     65535, 131071, 262143, 524287, 1048575, 2097151, 4194303, 8388607, 16777215, 33554431};
    size_t N, K, L;

    scanf("%lu %lu %lu", &N, &K, &L);
    N--, K--, L--;
    // printf("%c", get_sym(N, K, leng, 0));
    for (size_t it = K; it <= L; ++it) {
        printf("%c", get_sym(N, it, leng, 0));
    }

    return 0;
}