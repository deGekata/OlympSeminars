#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

const int32_t CAPACITY = 50000;

enum states {
    EMPTY = 0,
    DELETED,
    BUSY,
};

struct pair {
    int32_t key;
    int32_t value;
};

struct hashT {
    struct pair*   data;
    enum states*   state;

    uint32_t capacity;
};

uint32_t H1(int32_t s, const uint32_t hashsize) {
    uint32_t sum = 0;
    const int32_t FACTOR = 5;

    sum += s;
    sum <<= FACTOR;

    return sum % hashsize;
}

uint32_t H2(int32_t s, uint32_t hashsize) {
    uint32_t h = 0, a = 31415, b = 27183;

    h = (a * h + s) % hashsize;
    a = a * b % (hashsize - 1);

    return h;
}

hashT* newHT(uint64_t capacity) {
    hashT* h = (hashT*) calloc(1, sizeof(struct hashT));
    if (h == NULL)
        return h;

    h->data  = (pair*) calloc(h->capacity = capacity, sizeof(h->data[0]));
    h->state = (states*) calloc(capacity, sizeof(h->state[0]));
    
    if ((h->data == NULL) || (h->state == NULL)) {
        free(h->state);
        free(h->data);
        free(h);

        return NULL;
    }
    
    return h;
}

int32_t findHT(struct hashT* hT, int32_t key) {
    assert(hT != NULL);

    for (uint64_t curPlace = H1(key, hT->capacity), increment = H2(key, hT->capacity), tries = 0; 
      tries != hT->capacity; 
      curPlace = (curPlace + increment) % hT->capacity, tries++) {
        switch (hT->state[curPlace]) {
            case BUSY: {
                if (hT->data[curPlace].key == key) {
                    return hT->data[curPlace].value;
                }
                break;
            }
            case EMPTY: {
                return key;
            }

            case DELETED: 
                break;
            default:
                assert(0);
        }
    }

    return 0;
}

void insertHT(struct hashT* hT, int32_t key, int32_t value) {
    assert(hT != NULL);

    for (uint64_t curPlace = H1(key, hT->capacity), increment = H2(key, hT->capacity), tries = 0; 
      tries != hT->capacity; 
      curPlace = (curPlace + increment) % hT->capacity, tries++) {
        if ((hT->state[curPlace] != BUSY) || (key == hT->data[curPlace].key)) {
            hT->data[curPlace].key   = key;
            hT->data[curPlace].value = value;
            hT->state[curPlace] = BUSY;
            
            return;
        }
    }
}

void eraseHT(struct hashT* hT, int32_t key) {
    assert(hT != NULL);

    for (uint64_t curPlace = H1(key, hT->capacity), increment = H2(key, hT->capacity), tries = 0; 
      tries != hT->capacity; 
      curPlace = (curPlace + increment) % hT->capacity, tries++) {
        switch (hT->state[curPlace]) {
            case BUSY: {
                if (hT->data[curPlace].key == key) {
                    hT->state[curPlace] = DELETED;

                    return;
                }
                break;
            }
            case EMPTY: {
                return;
            }

            case DELETED: 
                break;
            default:
                assert(0);
        }
    }
}

struct hashT* deleteHT(struct hashT* hT) {
    if (hT == NULL)
        return NULL;


    free(hT->state);
    free(hT->data);
    free(hT);
    return NULL;    
}



int main() {
    int cnt = 0;
    
    hashT* map = newHT(2000003);

    scanf("%d", &cnt);

    for (int it = 0; it < cnt; ++it) {
        int lft, rht;
        scanf("%d %d", &lft, &rht);
        int pos1 = findHT(map, lft);
        int pos2 = findHT(map, rht);
        printf("%d\n", abs(pos1 - pos2));

        insertHT(map, lft, pos2), insertHT(map, rht, pos1);
    }

    return 0;
}