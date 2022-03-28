#include <inttypes.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef int64_t heap_type;

struct binHeap {
    int64_t size;
    int64_t capacity;
    heap_type* data;
};

#include <stdio.h>



binHeap* createHeap(heap_type* data, int64_t size);

inline int64_t heapLeftSon(int64_t index);

inline int64_t heapRightSon(int64_t index);

void heapSiftUp(binHeap* heap, int64_t index);

void heapSiftDown(binHeap* heap, int64_t index);

void heapInsert(binHeap* heap, heap_type elem);

heap_type heapGetMin(binHeap* heap);

heap_type heapExtractMIn(binHeap* heap);



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

binHeap* createHeap(heap_type* data, int64_t size) {
    binHeap* heap = (binHeap*) malloc(sizeof(binHeap));
    int binpw = 1;
    while (binpw < size) binpw <<= 1;
    binpw++;

    heap->size = size;
    heap->capacity = binpw;

    heap->data = (heap_type*) malloc(sizeof(heap_type) * binpw);
    memcpy(heap->data + 1, data, sizeof(heap_type) * size);

    for (int i = size/2; i >= 1; --i) {
        printf("lol %ld\n", i);
        heapSiftDown(heap, i);
    }
    
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
    while (index > 1 && heap->data[index] > heap->data[index / 2]) {
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

        int64_t dest = (right <= heap->size && heap->data[right] > heap->data[left] ? right : left);

        if (heap->data[index] >= heap->data[dest])
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

heap_type heapGetMin(binHeap* heap) {
    assert(heap && "heap ptr must not be NULL");
    
    return heap->data[1];
}

heap_type heapExtractMIn(binHeap* heap) {
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



int main() {
    heap_type arr[10] = {5, 2, 3, 1, 4};
    binHeap* heap = createHeap(arr, 5);
    printf("heap size :%ld\n", heap->size);
    heapPrint(heap);
    while (heapSize(heap) != 0) {
        printf("extracted min: %lu\n", heapExtractMIn(heap));
        heapPrint(heap);
        printf("------------------------\n");
    }

    heapInsert(heap, 1);
    heapPrint(heap);
    // printf("%%");
    return 0;
}





