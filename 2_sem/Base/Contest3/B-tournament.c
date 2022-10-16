#include <inttypes.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <malloc.h>

enum states {
    EMPTY = 0,
    DELETED,
    BUSY,
};

struct pair {
    char* key;

    int32_t value;
    uint32_t time;
};

struct hashT {
    struct pair* data;
    char*   state;

    uint32_t capacity;
};

uint32_t H1(char* s, uint32_t hashsize) {
    uint32_t sum = 0;
    const int32_t FACTOR = 5;

    while (*s) {
        sum <<= FACTOR;
        sum += *s++;
    }

    return sum % hashsize;
}

uint32_t H2(char* s, uint32_t hashsize) {
    uint32_t h = 0, a = 31415, b = 27183;
    while(*s) {
        h = (a * h + *s++) % hashsize;
        a = a * b % (hashsize - 1);
    }

    return h;
}

struct hashT* newHT(uint64_t capacity) {
    struct hashT* h = calloc(1, sizeof(struct hashT));
    if (h == NULL)
        return h;

    h->data  = calloc(h->capacity = capacity, sizeof(h->data[0]));
    h->state = calloc(capacity, sizeof(h->state[0]));

    for (uint64_t curSpace = 0; curSpace < capacity; curSpace++) {
        h->data[curSpace].time  = UINT32_MAX;
        h->data[curSpace].value = INT32_MIN;
    }
    
    if ((h->data == NULL) || (h->state == NULL)) {
        free(h->state);
        free(h->data);
        free(h);

        return NULL;
    }
    
    return h;
}

int32_t findHT(struct hashT* hT, char* key) {
    assert(hT != NULL);

    for (uint64_t curPlace = H1(key, hT->capacity) % hT->capacity, increment = H2(key, hT->capacity), tries = 0; 
      tries != hT->capacity; 
      curPlace = (curPlace + increment) % hT->capacity, tries++) {
        switch (hT->state[curPlace]) {
            case BUSY: {
                if (strcmp(hT->data[curPlace].key, key) == 0) {
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

void insertHT(struct hashT* hT, char* key, uint32_t value, uint32_t time) {
    assert(hT != NULL);

    for (uint64_t curPlace = H1(key, hT->capacity) % hT->capacity, increment = H2(key, hT->capacity), tries = 0; 
      tries != hT->capacity; 
      curPlace = (curPlace + increment) % hT->capacity, tries++) {
          if (hT->state[curPlace] != BUSY) {
              hT->data[curPlace].key   = key;
              hT->data[curPlace].value = value;
              hT->data[curPlace].time  = time;

              hT->state[curPlace] = BUSY;
              
              return;
          }
    }
}

void eraseHT(struct hashT* hT, char* key) {
    assert(hT != NULL);

    for (uint64_t curPlace = H1(key, hT->capacity) % hT->capacity, increment = H2(key, hT->capacity), tries = 0; 
      tries != hT->capacity; 
      curPlace = (curPlace + increment) % hT->capacity, tries++) {
        switch (hT->state[curPlace]) {
            case BUSY: {
                if (strcmp(hT->data[curPlace].key, key) == 0) {
                    hT->state[curPlace] = DELETED;
                    free(hT->data[curPlace].key);
                    hT->data[curPlace].key = NULL;

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

int32_t pairCmp(const void* elem1, const void* elem2) {
    if (((struct pair*)elem1)->value > ((struct pair*)elem2)->value) {
        return -1;
    }
    else if (((struct pair*)elem1)->value < ((struct pair*)elem2)->value) {
        return 1;
    }
    else {
        return ((struct pair*)elem1)->time > ((struct pair*)elem2)->time;
    }
}

#define DEBUG
// #undef DEBUG
const size_t insert_num_target = 100000;
const size_t rand_str_len = 15;

struct Person {
    char* name;
    int64_t score;
    int64_t pos;
};


int compare(const void * x1, const void * x2)   // функция сравнения элементов массива
{
    if (((Person*)x2)->score - ((Person*)x1)->score  == 0) {
        return ((Person*)x1)->pos - ((Person*)x2)->pos;
    }

    return ( ((Person*)x2)->score - ((Person*)x1)->score );              // если результат вычитания равен 0, то числа равны, < 0: x1 < x2; > 0: x1 > x2
}

int main() {
    
    Hashmap* map = HashmapCreate(strHashCode);

    int64_t oper_cnt = 0, names_cnt = 0, cur_name_cnt = 0;
    scanf("%ld %ld", &names_cnt, &oper_cnt);
    
    char buff[50];
    Person* persons = (Person*) calloc(names_cnt, sizeof(Person));


    for (int64_t it = 0; it < oper_cnt; ++it) {
        int64_t score = 0;
        scanf("%48s %ld", buff, &score);

        int64_t pos = get(map, buff);
        if (pos == -1) {
            char* val = (char*) calloc(strlen(buff) + 1, sizeof(char));
            strcpy(val, buff);
            Hashmap_insert(&map, val, cur_name_cnt);
            persons[cur_name_cnt].name = val;
            persons[cur_name_cnt].score = score;
            persons[cur_name_cnt].pos = it;
            ++cur_name_cnt;
        } else {
            if (persons[pos].score < score) {
                persons[pos].score = score;
                persons[pos].pos = it;
            }
        }
    }


    qsort(persons, names_cnt, sizeof(Person), compare);

    for (int it = 0; it < names_cnt; ++it) {
        if (persons[it].name == NULL) {
            assert(0);
        }
        printf("%s\n", persons[it].name);
    }

    // destroyHashmap(&map);


    return 0;
} 