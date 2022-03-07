#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <inttypes.h>


struct matrix {
    int64_t* data;
    /* 2 by 2*/
};

void matrix_mult(struct matrix* a, struct matrix* b, int mod) {
    int64_t r11 = (a->data[0] * b->data[0] + a->data[1] * b->data[2]) % mod; 
    int64_t r12 = (a->data[0] * b->data[1] + a->data[1] * b->data[3]) % mod; 
    int64_t r21 = (a->data[2] * b->data[0] + a->data[3] * b->data[2]) % mod; 
    int64_t r22 = (a->data[2] * b->data[0] + a->data[3] * b->data[3]) % mod;
    a->data[0] = r11;
    a->data[1] = r12;
    a->data[2] = r21;
    a->data[3] = r22;
    return;
}

void matrix_pow2(struct matrix* a, int mod) {
    int64_t a11 = (a->data[0] * a->data[0] + a->data[1] * a->data[2]) % mod; 
    int64_t a12 = (a->data[0] * a->data[1] + a->data[1] * a->data[3]) % mod; 
    int64_t a21 = (a->data[0] * a->data[2] + a->data[3] * a->data[2]) % mod; 
    int64_t a22 = (a->data[2] * a->data[1] + a->data[3] * a->data[3]) % mod;
    a->data[0] = a11;
    a->data[1] = a12;
    a->data[2] = a21;
    a->data[3] = a22;
    return;
}

void matrix_print(struct matrix* a) {
    printf("\t%ld \t%ld\n", a->data[0], a->data[1]);
    printf("\t%ld \t%ld\n", a->data[2], a->data[3]);
    printf("\n");
}

int main() {
    int64_t a1, a2, N, M;
    scanf("%ld %ld %ld %ld", &a1, &a2, &N, &M);

    if (N == 0) {
        printf("%ld", a1 % M);
        return 0;
    }
    if (N == 1) {
        printf("%ld", a2 % M);
        return 0;
    }


    int64_t a_[4] = {1, 1, 1, 0};
    int64_t b_[4] = {1, 1, 1, 0};
    struct matrix a;
    struct matrix b;
    a.data = a_;
    b.data = b_;
    int64_t it = N - 2;
    while (it != 0) {
        if (it & 1) {
            matrix_mult(&b, &a, M);
        }
        matrix_pow2(&a, M);
        it >>= 1;
        // matrix_print(&a);
        // matrix_print(&b);
    }
    
    // matrix_print(&b);
    printf("%ld", (b.data[0]*a2 + b.data[1]*a1) % M);
    // matrix_print(&a);
    // for (int it = 0; it < 4; ++it) {
    //     matrix_pow2(&a, 1000000000);
    //     matrix_print(&a);
    // }
    return 0;
}
    