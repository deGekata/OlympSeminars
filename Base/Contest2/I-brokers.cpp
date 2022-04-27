#include <inttypes.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

typedef int64_t heap_type;

struct binHeap {
    int64_t size;
    int64_t capacity;
    heap_type* data;
    bool (*cmp_func)(heap_type, heap_type);
};




binHeap* createHeap(heap_type* data, int64_t size);

inline int64_t heapLeftSon(int64_t index);

inline int64_t heapRightSon(int64_t index);

void heapSiftUp(binHeap* heap, int64_t index);

void heapSiftDown(binHeap* heap, int64_t index);

void heapInsert(binHeap* heap, heap_type elem);

heap_type heapGetTop(binHeap* heap);

heap_type heapExtractTop(binHeap* heap);



void swap(int16_t* lft, int16_t* rht) {
    int16_t temp = *lft;
    *lft = *rht;
    *rht = temp;
    return;
}

void swap(int32_t* lft, int32_t* rht) {
    int32_t temp = *lft;
    *lft = *rht;
    *rht = temp;
    return;
}

void swap(int64_t* lft, int64_t* rht) {
    int64_t temp = *lft;
    *lft = *rht;
    *rht = temp;
    return;
}

void swap(float* lft, float* rht) {
    float temp = *lft;
    *lft = *rht;
    *rht = temp;
    return;
}

void swap(double* lft, double* rht) {
    double temp = *lft;
    *lft = *rht;
    *rht = temp;
    return;
}

binHeap* createHeap(heap_type* data, int64_t size, bool (*cmp_func)(heap_type, heap_type)) {
    binHeap* heap = (binHeap*) malloc(sizeof(binHeap));
    heap->cmp_func = cmp_func;
    int binpw = 1;
    while (binpw < size) binpw <<= 1;
    binpw++;

    heap->size = size;
    heap->capacity = binpw;

    heap->data = (heap_type*) malloc(sizeof(heap_type) * binpw);
    memcpy(heap->data + 1, data, sizeof(heap_type) * size);

    for (int i = size/2; i >= 1; --i) {
        // printf("lol %ld\n", i);
        heapSiftDown(heap, i);
    }
    
    return heap;
}

binHeap* createHeap(int64_t size, bool (*cmp_func)(heap_type, heap_type)) {
    binHeap* heap = (binHeap*) malloc(sizeof(binHeap));
    heap->cmp_func = cmp_func;
    int binpw = 1;
    while (binpw < size) binpw <<= 1;
    binpw++;

    heap->size = 0;
    heap->capacity = binpw;

    heap->data = (heap_type*) malloc(sizeof(heap_type) * binpw);
    
    return heap;
}

inline int64_t heapLeftSon(int64_t index) {
    return index * 2;
}

inline int64_t heapRightSon(int64_t index) {
    return index * 2 + 1;
}


void heapSiftUp(binHeap* heap, int64_t index) {
    assert(heap && "heap ptr must not be NULL");
    assert(index <= heap->size);
    while (index > 1 && heap->cmp_func(heap->data[index / 2], heap->data[index])) {
        swap(heap->data + index, heap->data + index / 2);
        index /= 2;
    }
    
}

void heapSiftDown(binHeap* heap, int64_t index) {
    assert(heap && "heap ptr must not be NULL");
    assert(index <= heap->size);

    while (2 * index <= heap->size) {
        int64_t left = heapLeftSon(index);
        int64_t right = heapRightSon(index);
        
        int64_t dest = (right <= heap->size && heap->cmp_func(heap->data[left], heap->data[right]) ? right : left);

        if (heap->cmp_func(heap->data[dest], heap->data[index]) || heap->data[dest] == heap->data[index])
            break;
        
        swap(heap->data + index, heap->data + dest);
        index = dest;
    }
    
    return;
}

void heapInsert(binHeap* heap, heap_type elem) {
    assert(heap && "heap ptr must not be NULL");

    heap->data[++heap->size] = elem;
    heapSiftUp(heap, heap->size);

}

heap_type heapGetTop(binHeap* heap) {
    assert(heap && "heap ptr must not be NULL");
    
    return heap->data[1];
}

heap_type heapExtractTop(binHeap* heap) {
    assert(heap->size > 0);

    heap_type ret_val = heap->data[1];
    if (heap->size == 1) {
        heap->size--;
        return ret_val;
    }
    swap(heap->data + 1, heap->data + heap->size);
    heap->size--;
    heapSiftDown(heap, 1);
    return ret_val;
}

int64_t heapSize(binHeap* heap) {
    return heap->size;
}

void heapPrint(binHeap* heap) {
    printf("[");
    for (size_t it = 1; it <= heap->size; ++it) {
        printf("\t%ld ", it);
    }
    printf("]\n");
    printf("{");
    for (size_t it = 1; it <= heap->size; ++it) {
        printf("\t%ld ", heap->data[it]);
    }
    printf("}\n");
}

bool cmp_max(heap_type lft, heap_type rht) {
    return lft < rht;
}

bool cmp_min(heap_type lft, heap_type rht) {
    return lft > rht;
}


int main() {
    size_t n;
    scanf("%lu", &n);

    binHeap* heap = createHeap(n, cmp_min);
    // printf("%d\n", __LINE__);
    for (size_t it = 0; it < n; ++it) {
        int64_t tmp;
        scanf("%ld", &tmp);
        heapInsert(heap, tmp);
    }
    // printf("%d\n", __LINE__);

    double ans = 0;
    for (size_t it = 0; it < n - 1; ++it) {
        // printf("----------------bef\n");
        // heapPrint(heap);
        int64_t tmp1 = heapExtractTop(heap);
        int64_t tmp2 = heapExtractTop(heap);
        // printf("%ld %ld\n", tmp1, tmp2);
        ans += tmp1 + tmp2;
        heapInsert(heap, tmp1 + tmp2);
        // heapPrint(heap);
        // printf("----------------af\n");

    }


    printf("%.21f\n", ans / 100);
    return 0;
}