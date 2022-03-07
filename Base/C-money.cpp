#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <inttypes.h>
#include <string.h>
#include <assert.h>

int main() {
    int N;
    scanf("%d", &N);
    assert(N < 100000);
    for (int it = 0; it < N; ++it) {
        int temp;
        scanf("%d", &temp);
        assert(temp < 10000);
    }
    return 0;
}