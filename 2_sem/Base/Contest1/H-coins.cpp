#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <inttypes.h>
#include <string.h>
#include <ctype.h>

struct pair {
    int sum;
    int cnt;
};


int64_t binPow(int64_t num, int64_t power) {
    int64_t shft = 1;

    while (power) {
        if (power & 1) {
            shft *= num;
        }
        num *= num;
        power >>= 1;
    }
    return shft;
}


typedef struct pair pair;

void generate(int64_t* weight, int64_t* mx_weight, int64_t cur_sum, int64_t cur_cnt, pair** dest) {
    if (weight == mx_weight) {
        (**dest).sum = cur_sum;
        (**dest).cnt = cur_cnt;
        // printf("cur sum %ld, cur cnt %ld \n", cur_sum, cur_cnt);
        *dest += 1;
        // printf("cur_sum = %d, diff = %dmx\n", cur_sum, mx_weight - weight);
        return;
    }
    // printf("cur_sum = %d, diff = %d\n", cur_sum, mx_weight - weight);
    generate(weight + 1, mx_weight, cur_sum          , cur_cnt    , dest);
    generate(weight + 1, mx_weight, cur_sum + *weight, cur_cnt + 1, dest);
    generate(weight + 1, mx_weight, cur_sum + *weight * 2, cur_cnt + 2, dest);

}

int compinc(const void * lft, const void * rht) {
    if ((*(pair*)lft).sum == (*(pair*)rht).sum ) 
        return (*(pair*)lft).cnt - (*(pair*)rht).cnt;
    return ((*(pair*)lft).sum - (*(pair*)rht).sum );
}

int compdec(const void * lft, const void * rht) {
    if ((*(pair*)lft).sum == (*(pair*)rht).sum ) 
        return (*(pair*)lft).cnt - (*(pair*)rht).cnt;
    return ((*(pair*)rht).sum - (*(pair*)lft).sum );
}

int main() {
    int64_t V, N, sum = 0;
    scanf("%lu %lu", &V, &N);
    
    N += N % 2;

    int64_t* arr = (int64_t*) calloc(N, sizeof(int64_t));
    
    for (int64_t it = 0; it < N; ++it) {
        scanf("%lu", arr + it); 
        sum += arr[it];
        // arr[it * 2 + 1] = arr[it * 2];
    }

    if (sum * 2 < V) {
        printf("Impossible");
        return 0;
    }

    int64_t size = binPow(3, N / 2);
    // printf("lol");

    pair* h1 = (pair*) malloc(sizeof(pair) * size);
    pair* h2 = (pair*) malloc(sizeof(pair) * size);
    pair* h1_s = h1;
    pair* h2_s = h2;
    // printf("lol2");

    // int64_t h_size = (1 << N);
    // printf("%lu sz \n", h_size);
    generate(arr        , arr + N / 2  , 0, 0, &h1_s);
    generate(arr + N / 2, arr + N      , 0, 0, &h2_s);
    // for (int it = 0; it < h_size; ++it) {
    //     h2[it] = h1[it];
    // }
    qsort(h1, size, sizeof(pair), compinc);
    qsort(h2, size, sizeof(pair), compdec);

    // for (int it = 0; it < size; ++it) {
    //     printf("sum = %lu, cnt = %lu\n ", h1[it].sum, h1[it].cnt);
    // }
    // printf("endl\n");

    int64_t  mn = 40;
    // char flag = 1, found = 0;
    for (int it1 = 0, it2 = 0; it1 < size && it2 < size; ) {
        int sum =  h1[it1].sum + h2[it2].sum;
        // printf("%d = it1 %d = it2 %ld = sum %ld = mn \n", it1, it2, sum, mn);
        // printf("sum = %d\n", sm);
        if (sum == V) {
            mn = (mn < (h1[it1].cnt + h2[it2].cnt)) ? mn : (h1[it1].cnt + h2[it2].cnt);

            if (it1 < size) ++it1;
            else break;

            if (it2 < size) ++it2;
            else break;
                // mn = mn < (h1[it1].cnt + h2[it2].cnt) ? mn : (h1[it1].cnt + h2[it2].cnt);
        } else if (sum < V) {
            if (it1 < size) ++it1;
            else break;
        } else {
            if (it2 < size) ++it2;
                else break;
        }

    }

    

    // printf("%lu", mn);



    if (sum * 2 < V) {
        printf("Impossible");
    } else if (mn == 40) {
        printf("Change");
    } else {
        printf("%lu", mn);
        // printf("%lu", res);
    }
    // printf("%lu", backtrack(V, 0, arr, arr + 2 * N, 0));
    return 0;
}
