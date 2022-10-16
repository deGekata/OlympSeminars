#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main() {
    //yaroslav
    int N;
    scanf("%d", &N);

    int mas[23];
    int* ptr = mas;
    int alsum = 0;
    for (int it = 0; it < N; ++it) {
        scanf("%d", mas + it);
        alsum += mas[it];
    }

    int mn = INT_MAX, bar = 1 << (N);

    for (int counter = 1; counter <= bar; ++counter) {
        int s_sum = 0;
        ptr = mas;
        for (int pos = counter; pos > 0; pos >>= 1) {
            s_sum += (pos & 0x1) * *ptr++;
        }
        
        if (mn > abs(alsum - s_sum * 2)) {
            mn = abs(alsum - s_sum * 2);
        }

        ++counter;
    }

    printf ("%d", mn);

    return 0;
}