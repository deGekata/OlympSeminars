#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


int main() {
    uint64_t dividend = 0;
    uint64_t divizor = 0;
    uint64_t fact_base = 2;

    scanf("%lu %lu", &dividend, &divizor);

    dividend = (dividend % divizor);

    while (dividend) {
        dividend *= fact_base++;

        printf("%lu ", dividend / divizor);
    
        dividend %= divizor;
    }

    return 0;
}