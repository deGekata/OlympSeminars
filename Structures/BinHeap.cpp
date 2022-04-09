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
    int (*cmp_func)(heap_type, heap_type);
};

typedef struct binHeap binHeap;


// binHeap* createHeap(heap_type* data, int64_t size);

inline int64_t heapLeftSon(int64_t index);

inline int64_t heapRightSon(int64_t index);

void heapSiftUp(binHeap* heap, int64_t index);

void heapSiftDown(binHeap* heap, int64_t index);

void heapInsert(binHeap* heap, heap_type elem);

heap_type heapGetTop(binHeap* heap);

heap_type heapExtractTop(binHeap* heap);



void swap16(int16_t* lft, int16_t* rht) {
    int16_t temp = *lft;
    *lft = *rht;
    *rht = temp;
    return;
}

void swap32(int32_t* lft, int32_t* rht) {
    int32_t temp = *lft;
    *lft = *rht;
    *rht = temp;
    return;
}

void swap64(int64_t* lft, int64_t* rht) {
    int64_t temp = *lft;
    *lft = *rht;
    *rht = temp;
    return;
}

void swapfl(float* lft, float* rht) {
    float temp = *lft;
    *lft = *rht;
    *rht = temp;
    return;
}

void swapdb(double* lft, double* rht) {
    double temp = *lft;
    *lft = *rht;
    *rht = temp;
    return;
}

binHeap* createHeapWithData(heap_type* data, int64_t size, int (*cmp_func)(heap_type, heap_type)) {
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

binHeap* createHeap(int64_t size, int (*cmp_func)(heap_type, heap_type)) {
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

void heapDtor(binHeap* heap) {
    free(heap->data);
    heap->size = 0;
    heap->capacity = 0;
    return;
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
        swap64(heap->data + index, heap->data + index / 2);
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
        
        swap64(heap->data + index, heap->data + dest);
        index = dest;
    }
    
    return;
}

size_t heapGetSize(binHeap* heap) {
    return heap->size;
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
    swap64(heap->data + 1, heap->data + heap->size);
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

int cmpl(heap_type lft, heap_type rht) {
    return lft < rht;
}

int cmpg(heap_type lft, heap_type rht) {
    return lft > rht;
}

int main() {
    binHeap** heaps = (binHeap**) calloc(5, sizeof(binHeap*));
    int heaps_cnt;
    scanf("%d", &heaps_cnt);

    int oper_num, is_ok;
    is_ok = scanf("%d", &oper_num);
    
    while (is_ok != -1) {
        switch (oper_num) {
        case 0: {
            int num, size, type;
            scanf("%d %d %d", &num, &size, &type);
            if (!type) {
                heaps[num] = createHeap(size, cmpg);
            } else {
                heaps[num] = createHeap(size, cmpl);
            }
            break;
        }
        case 1: {
            int num, elem;
            scanf("%d %d", &num, &elem);
            heapInsert(heaps[num], elem);
            break;
        }
        case 2:{
            int num;
            scanf("%d", &num);
            printf("%ld\n", heapGetTop(heaps[num]));
            break;
        }
        case 3:{
            int num;
            scanf("%d", &num);
            heapExtractTop(heaps[num]);
            break;
        }
        case 4:{
            int num;
            scanf("%d", &num);
            printf("%ld\n", heapGetSize(heaps[num]));
            break;
        }
        case 5:{
            int num1, num2;
            scanf("%d %d", &num1, &num2);
            while (heapGetSize(heaps[num2])) {
                heapInsert(heaps[num1], heapExtractTop(heaps[num2]));
            }
            
            break;
        }
        case 6:{
            int num;
            scanf("%d", &num);
            heapDtor(heaps[num]);
            free(heaps[num]);
            break;
        }
        default:
            break;
        }
        is_ok = scanf("%d", &oper_num);
        /* code */
    }
    
    free(heaps);

    return 0;
}





