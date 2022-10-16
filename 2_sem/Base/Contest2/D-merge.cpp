#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

// #define DEBUG

int main() {
    size_t N;
    scanf("%lu", &N);
    int64_t* arr = (int64_t*) malloc(sizeof(int64_t) * N);
    size_t f_size = N, s_size  = N;
    
    for (size_t it = 0; it < N; ++it) {
        scanf("%ld", arr + it);
    }
//5
// 1 1 3 7 9
// 3 7 8 9 10
    int64_t cur_s_elem, cur_sum = 0;
    scanf("%ld", &cur_s_elem);
    s_size--;
    int odd_flag = 1;
    while (f_size != 0 && s_size != 0) {
        if (odd_flag == 1) {
            if (cur_s_elem < arr[N - f_size]) {
                #ifdef DEBUG
                printf("%ld %ld %d cmp odd sec , %ld cur_sum\n", cur_s_elem, arr[N - f_size], cur_s_elem < arr[N - f_size], cur_sum);
                #endif
                cur_sum += cur_s_elem;
                scanf("%ld", &cur_s_elem);
                s_size--;         
            } else {
                #ifdef DEBUG
                printf("%ld %ld %d cmp odd fist, %ld cur_sum\n", cur_s_elem, arr[N - f_size], cur_s_elem < arr[N - f_size], cur_sum);
                #endif
                cur_sum += arr[N - f_size];
                f_size--;
            }
            odd_flag = 0;
        } else {
            if (cur_s_elem < arr[N - f_size]) {
                #ifdef DEBUG
                printf("%ld %ld %d cmp even sec, %ld cur_sum\n", cur_s_elem, arr[N - f_size], cur_s_elem < arr[N - f_size], cur_sum);
                #endif
                scanf("%ld", &cur_s_elem);
                s_size--;         
            } else {
                #ifdef DEBUG
                printf("%ld %ld %d cmp even fist, %ld cur_sum\n", cur_s_elem, arr[N - f_size], cur_s_elem < arr[N - f_size], cur_sum);
                #endif
                f_size--;
            }
            odd_flag = 1;
        }
    }
    #ifdef DEBUG
    printf("cursum %ld\n", cur_sum);
    #endif
    if (s_size == 0) {
        #ifdef DEBUG
        printf("lol");
        #endif
        int ins_pos = N;
        for (int it = N - f_size; it < N; ++it) {
            if (cur_s_elem < arr[it]) {
                ins_pos = it;
                break;
            }
        }
        #ifdef DEBUG
        printf("%d inst pos\n", ins_pos);
        #endif
        for (int it = N - f_size; it < ins_pos; ++it) {
            if (odd_flag) {
                cur_sum = (cur_sum + arr[it]) % 1000000000;
                odd_flag = 0;
            } else {
                odd_flag = 1;
            }
        }

        if (odd_flag) {
            cur_sum = (cur_sum + cur_s_elem)  % 1000000000;
            odd_flag = 0;
        } else {
            odd_flag = 1;
        }

        for (int it = ins_pos; it < N; ++it) {
            if (odd_flag) {
                cur_sum = (cur_sum + arr[it]) % 1000000000;
                odd_flag = 0;
            } else {
                odd_flag = 1;
            }
        }

        printf("%ld", cur_sum);
        return 0;
    }

    if (f_size == 0) {
        #ifdef DEBUG
        printf("ssize %ld\n", s_size);
        #endif
        for (size_t it = N - s_size; it < N; ++it) {
            if (odd_flag) {
                cur_sum = (cur_sum + cur_s_elem) % 1000000000;
                #ifdef DEBUG
                printf("cursum__ %ld\n", cur_sum);
                #endif
                scanf("%ld", &cur_s_elem);
                odd_flag = 0;
            } else {
                // cur_sum += cur_s_elem;
                scanf("%ld", &cur_s_elem);
                odd_flag = 1;
            }
        }
        // cur_sum += cur_s_elem;
    }
    
    printf("%ld", cur_sum);
    
    
    return 0;
    
}