#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <inttypes.h>

int back_track(int* weight, int h_sum, int cur_sum, int* mx_weight) {
    // if (cur_sum >= h_sum) { printf("cur_weight =%d, cur_sum = %d g\n", *weight, cur_sum); return abs(h_sum - cur_sum);}
    if (cur_sum >= h_sum) return cur_sum;

    // if (weight == mx_weight) { printf("cur_weight =%d, cur_sum = %d, d = %d end\n", *weight, cur_sum, abs(h_sum - cur_sum)); return abs(h_sum - cur_sum);}
    if (weight == mx_weight) return cur_sum;

    // printf("cur_weight =%d, cur_sum = %d\n", *weight, cur_sum);
    int mn = back_track(weight + 1, h_sum, cur_sum + *weight, mx_weight);
    int en = back_track(weight + 1, h_sum, cur_sum,           mx_weight);
    // printf("(mn) %d ? %d (en) \n", mn, en);
    return abs(mn - h_sum) < abs(en - h_sum) ? mn: en;
}


void generate(int* weight, int* mx_weight, int cur_sum, int** dest) {
    if (weight == mx_weight) {
        **dest = cur_sum;
        *dest += 1;
        // printf("cur_sum = %d, diff = %dmx\n", cur_sum, mx_weight - weight);
        return;
    }
    // printf("cur_sum = %d, diff = %d\n", cur_sum, mx_weight - weight);
    generate(weight + 1, mx_weight, cur_sum,           dest);
    generate(weight + 1, mx_weight, cur_sum + *weight, dest);

}

int comp(const void * lft, const void * rht) {
    return ( *(int*)lft - *(int*)rht );
}

int main() {
    
    int N;
    scanf("%d", &N);

    int mas[50];
    int alsum = 0, h_sum = 0;;
    for (int it = 0; it < N; ++it) {
        scanf("%d", mas + it);
        alsum += mas[it];
    }
    h_sum = alsum / 2;

    int* h1 = (int*) malloc(sizeof(int) * ((1 << (N / 2)) + 1));
    int* h2 = (int*) malloc(sizeof(int) * ((1 << (N / 2)) + 1));
    int* h1_s = h1;
    int* h2_s = h2;
    int h_size = ((1 << (N / 2)));
    if (N % 2 == 0) {
        generate(mas, mas + N / 2, 0, &h1_s);
        generate(mas + N / 2, mas + N, 0, &h2_s);
    } else {
        generate(mas + 1, mas + N / 2 + 1, mas[0], &h1_s);
        generate(mas + 1 + N / 2, mas + N, 0, &h2_s);

    }
    // for (int it = 0; it < ((1 << (N / 2))); ++it) {
    //     printf("%d ", h1[it]);
    // }
    // printf("\n");
    // for (int it = 0; it < ((1 << (N / 2))); ++it) {
    //     printf("%d ", h2[it]);
    // }

    qsort(h1, h_size, sizeof(int), comp);
    qsort(h2, h_size, sizeof(int), comp);
    
    // for (int it = 0; it < ((1 << (N / 2))); ++it) {
    //     printf("%d ", h1[it]);
    // }
    // printf("\n");
    // for (int it = 0; it < ((1 << (N / 2))); ++it) {
    //     printf("%d ", h2[it]);
    // }

    // printf("\n");
    
    int sm = h1[0] + h2[h_size - 1], mn = abs(h_sum - sm);
    char flag = 1;
    for (int it1 = 0, it2 = h_size - 1; it1 < h_size && it2 >= 0; ) {
        flag = 1;
        // printf("%d = mn\n", mn);
        while (sm > h_sum && it2 >= 0) {
            flag = 0;
            sm = h1[it1] + h2[--it2];
            mn = mn > abs(h_sum - sm) ? abs(h_sum - sm) : mn;
        }

        while (sm < h_sum && it2 < h_size) {
            flag = 0;
            sm = h1[++it1] + h2[it2];
            mn = mn > abs(h_sum - sm) ? abs(h_sum - sm) : mn;
        }
        if (flag) break;
        
    }

    // printf("hsum = %d\n", h_sum);
    // printf("alsum = %d\n", alsum);
    printf("%d", mn * 2 + alsum % 2);


    return 0;
}