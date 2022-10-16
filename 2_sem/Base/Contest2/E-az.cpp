#include <stdlib.h>
#include <stdio.h>

struct pair {
    int count;
    unsigned char sym;
};

int cmp(const void* lft, const void* rht) {
    pair* lf = (pair*) lft;
    pair* rh = (pair*) rht;
    if (lf->count == rh->count) return lf->sym - rh->sym;
    return rh->count - lf->count;
}

int main() {
    pair elems[256] = {0};
    for (int it = 0; it < 256; ++it) {
        elems[it].sym = (unsigned char)it;
    }
    unsigned char ch;
    while ((ch = getchar()) != '\n') {
        elems[ch].count++;
    }

    qsort(elems, 256, sizeof(pair), cmp);

    for (int it = 0; it < 256; ++it) {
        if (elems[it].count == 0) break;
        printf("%c %d\n", elems[it].sym, elems[it].count);
    }
    
    return 0;
    
}