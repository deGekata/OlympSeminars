#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <inttypes.h>





struct item {
    char name[50];
    int cnt;
    int64_t* data;
};

int comparator(const void* item1, const void* item2) {
    struct item* item1_ = (struct item*) item1;
    struct item* item2_ = (struct item*) item2;
    for (int it = 0; it < item1_->cnt; ++it) {
        if (item1_->data[it] != item2_->data[it]) return item1_->data[it] - item2_->data[it];
    }
    return 0;
}


int main() {
    int64_t N, k;
    scanf("%ld", &N);
    scanf("%ld", &k);
    int64_t* prior = (int64_t*) calloc(k, sizeof(int64_t));
    int64_t* prior_morph = (int64_t*) calloc(k, sizeof(int64_t));

    for (int64_t it = 0; it < k; ++it) {
        scanf("%ld", &prior[it]);
        prior[it] -= 1;
    }

    for (int64_t it = 0; it < k; ++it) {
        prior_morph[prior[it]] = it;
    }

    struct item* items = (struct item*) calloc(N, sizeof(struct item));
    for (int64_t it = 0; it < N; ++it) {
        items[it].data = (int64_t*) calloc(N, sizeof(int64_t));
        items[it].cnt = k;
    }

    for (int64_t it = 0; it < N; ++it) {
        scanf("%s", items[it].name);
        for (int64_t elem_num = 0; elem_num < k; ++elem_num) {
            scanf("%ld", &(items[it].data[prior_morph[elem_num]]));
        }
    }

    // for (int it = 0; it < N; ++it) {
    //     printf("%s ", items[it].name);
    //     for (int jit = 0; jit < items[it].cnt; ++jit) {
    //         printf("%ld ", items[it].data[jit]);
    //     }
    //     printf("\n");
    // }

    // for (int it = 0; it < k; ++it) {
    //     printf("%ld ", prior[it]);
    // }
    // printf(" prior\n");

    qsort(items, N, sizeof(struct item), comparator);

    // for (int64_t round = 0; round < k; ++round) {
    //     qsort(items, N, sizeof(struct item), comparator);

    //     for (int64_t it = 0; it < N; ++it) {
    //         printf("%s\n", items[it].name);
    //     }
    //     printf("%ld --------------\n", prior[round]);
    // }

    for (int64_t it = N - 1; it >= 0; --it) {
        printf("%s\n", items[it].name);
    }
 

    return 0;
}


