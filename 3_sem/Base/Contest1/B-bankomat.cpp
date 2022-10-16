#include <stdio.h>
#include <string.h>

#include <stdlib.h>


struct my_pair
{  
    int ways = -1, prev_pos = 0;
};

int comp(const void* lft, const void* rht) {
    return (*(int*)lft) - (*(int*)rht);
}

int main() {
    int N = 0;
    scanf("%d", &N);
    int* nominals = new int[N];
    for (int it = 0; it < N; ++it) {
        scanf("%d", nominals + it);
    }

    qsort(nominals, N, sizeof(int), comp);

    int S = 0;
    scanf("%d", &S);

    my_pair* variants = new my_pair[S + 1];
    for (int it = 0; it  <= S; ++it) {

        variants[it] = {__INT_MAX__, 0};
    }

    for (int it = 0; it < N; ++it) {
        if (nominals[it] > S) break;
        variants[nominals[it]] = {1, it};
    }

    // for (int it = 0; it <= S; ++it) {
    //     printf("num: %d    ways: %d, move nominals: %d\n", it, variants[it].prev_pos, variants[it].ways);
    // }
    // return 0;

    for (int cur_sm = 1; cur_sm <= S; ++cur_sm) {
        for (int check_nom = 0; check_nom < N; ++check_nom) {
            if (cur_sm - nominals[check_nom] <=0) break;

            if (variants[cur_sm].ways - 1 > variants[cur_sm - nominals[check_nom]].ways) {
                variants[cur_sm].ways = variants[cur_sm - nominals[check_nom]].ways + 1;
                variants[cur_sm].prev_pos = check_nom;
            }
        }
    }

    // for (int it = 0; it <= S; ++it) {
    //     printf("num: %d    ways: %d, move nominals: %d\n", it, variants[it].ways, variants[it].prev_pos);
    // }

    if (variants[S].ways == __INT_MAX__) {
        printf("-1");
        return 0;
    }


    int cur_sm = S;
    printf("%d\n", variants[cur_sm].ways);
    while (cur_sm > 0) {
        printf("%d ", nominals[variants[cur_sm].prev_pos]);
        cur_sm -= nominals[variants[cur_sm].prev_pos];
    }
    return 0;
}