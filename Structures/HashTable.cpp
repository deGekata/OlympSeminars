#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <inttypes.h>
#include <malloc.h>

typedef int64_t T;


struct ht {
    enum ht_e {
        EMPTY = 0,
        DELETED, 
        BUSY,
    };
    T* data;
    char* state;
    size_t capacity;
    size_t size;

    size_t hits;
    size_t total;
};

size_t ht_size(struct ht const *h) {
    assert(h);
    return h->size;
}

struct ht *ht_new(size_t capacity) {
    struct ht *h = (struct ht*) calloc(1, sizeof(struct ht));
    if (h == NULL) return h;
    h->data = (T*) calloc(h->capacity = capacity, h->data[0]);
    h->state = (char*) calloc(capacity, sizeof h->state[0]);
    if (h->data == NULL || h->state == NULL) {
        free(h->state);
        free(h->data);
        free(h);
        return NULL;
    }
    return h;
}


void ht_find(struct ht *h, T x) {
    assert(h != NULL);
    assert(h->size + h->size <= h->capacity);
    if (ht_find(h, x)) return;
    for (size_t it = H1(x) % h->capacity, inc = H2(x), tries = 0;
        tries != h->capacity;
        it = (it + inc) % h->capacity, tries++) {
            switch (h->state[it])
            {
            case BUSY: {
                if (h->data[it] == x) {
                    h->total += tries;
                    h->hits++;
                }
            } break;
            
            case EMPTY: {
                h->total += tries+1
            } break;
            
            case DELETED: {
                continue;
            } break;
            
            default:
                assert(0);
                break;
            }
        }
}


int main(int argc, char **argv) {
    struct ht* table = hashTableNew(257);
    for (int c = getchar(); c != EOF; c = getchar()) {
        switch (c) {
        case '+': {
            T x;
            scanf("%llu", &x);
            ht_insert(h, x);
        } break;

        case '-': {
            T x;
            scanf("%llu", &x);
            ht_erase(h, x);
        } break;

        case '?': {
            T x;
            scanf("%llu", &x);
            puts(ht_find(h, x) ? "TRUE" : "FALSE");
        } break;
        
        case '*': {
            ht_dump(h);
        } break;

        case '=': {
            printf("%zu\n", ht_size(h));
        } break;

        default:
            continue;
        }
    }
}