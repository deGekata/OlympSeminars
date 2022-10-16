#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <inttypes.h>
#include <string.h>
#include <assert.h>
#include <time.h>

typedef struct FastRandom_s {
    unsigned long long rnd;
} FastRandom;

FastRandom *FastRandom_create(unsigned long long seed) {
  FastRandom *t = (FastRandom *)malloc(sizeof (FastRandom));
  t->rnd = seed;
  return t;
}

unsigned long long 
FastRandom_rand(FastRandom *t) {
  t->rnd ^= t->rnd << 21;
  t->rnd ^= t->rnd >> 35;
  t->rnd ^= t->rnd << 4;
  return t->rnd;                                                                                      
}

void FastRandom_delete(FastRandom *r) {
  free(r);
}


int main() {
    size_t cnt = 0;
    srand(time(NULL));;
    long long seed= rand();
    seed = 1;
    printf("%lld  \n", seed);
    FastRandom* turt = FastRandom_create(seed);
    FastRandom* speedy = FastRandom_create(seed);
    FastRandom_rand(speedy), FastRandom_rand(speedy);
    while (speedy->rnd != turt->rnd) {
        cnt += 1;
        FastRandom_rand(speedy), FastRandom_rand(speedy);
        FastRandom_rand(turt);
    }
    printf("%lu", cnt);
    // cookie_close_function_t
    return 0;
}