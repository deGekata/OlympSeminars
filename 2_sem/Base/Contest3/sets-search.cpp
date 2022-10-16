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
    uint32_t* key;
};

struct hashT {
    pair* data;
    char*   state;

    uint32_t capacity;
};

int32_t arrCmp(uint32_t* elem1, uint32_t* elem2, const uint32_t arrSize) {
    for (uint32_t curElem = 0; curElem < arrSize; curElem++) {
        if (elem1[curElem] != elem2[curElem])
            return 1;
    }
    return 0;
}

uint32_t H1(uint32_t* s, const uint32_t hashsize, const uint32_t arrSize) {
    uint32_t sum = 0;
    const uint32_t FACTOR = 5;

    for (uint32_t curByte = 0; curByte < arrSize; curByte++) {
        sum <<= FACTOR;
        sum += *s++;
    }

    return sum & hashsize;
}

uint32_t H2(uint32_t* s, const uint32_t hashsize, const uint32_t arrSize) {
    uint32_t h = 0, a = 31413, b = 27183;

    for (uint32_t curByte = 0; curByte < arrSize; curByte++) {
        h = (a * h + *s++) % hashsize;
        a = a * b % (hashsize - 1);
    }

    return h;
}

struct hashT* newHT(uint64_t capacity) {
    hashT* h = (hashT*) calloc(1, sizeof(struct hashT));
    if (h == NULL)
        return h;

    h->data  = (pair*) calloc(h->capacity = capacity, sizeof(h->data[0]));
    h->state = (char*) calloc(capacity, sizeof(h->state[0]));
    
    if ((h->data == NULL) || (h->state == NULL)) {
        free(h->state);
        free(h->data);
        free(h);

        return NULL;
    }
    
    return h;
}

int32_t findHT(struct hashT* hT, uint32_t* key, const uint32_t arrSize) {
    assert(hT != NULL);

    for (uint64_t curPlace = H1(key, hT->capacity, arrSize), increment = H2(key, hT->capacity, arrSize), tries = 0; 
      tries != hT->capacity; 
      curPlace = (curPlace + increment) % hT->capacity, tries++) {
        switch (hT->state[curPlace]) {
            case BUSY: {
                if (arrCmp(hT->data[curPlace].key, key, arrSize) == 0) {
                    return curPlace;
                }
                break;
            }
            case EMPTY: {
                return -1;
            }

            case DELETED: 
                break;
            default:
                assert(0);
        }
    }

    return 0;
}

void insertHT(struct hashT* hT, uint32_t* key, const uint32_t arrSize) {
    assert(hT != NULL);

    for (uint64_t curPlace = H1(key, hT->capacity, arrSize), increment = H2(key, hT->capacity, arrSize), tries = 0; 
      tries != hT->capacity; 
      curPlace = (curPlace + increment) % hT->capacity, tries++) {
          if (hT->state[curPlace] != BUSY) {
              hT->data[curPlace].key   = key;
              hT->state[curPlace]      = BUSY;
              
              return;
          }
    }
}

void eraseHT(struct hashT* hT, uint32_t* key, const uint32_t arrSize) {
    assert(hT != NULL);

    for (uint64_t curPlace = H1(key, hT->capacity, arrSize), increment = H2(key, hT->capacity, arrSize), tries = 0; 
      tries != hT->capacity; 
      curPlace = (curPlace + increment) % hT->capacity, tries++) {
        switch (hT->state[curPlace]) {
            case BUSY: {
                if (arrCmp(hT->data[curPlace].key, key, arrSize) == 0) {
                    hT->state[curPlace] = DELETED;

                    free(hT->data[curPlace].key);
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

    for (uint32_t curElem = 0; curElem < hT->capacity; curElem++) {
        if (hT->state[curElem] == BUSY) {
            free(hT->data[curElem].key);
        }
    }

    free(hT->state);
    free(hT->data);
    free(hT);
    return NULL;    
}