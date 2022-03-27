

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
const size_t base_size = 1 << 20;
const size_t mask = 1048575U;
const int extend_coef = 2;

// static void print_double(void const *st) {
//    printf("%d", *(int *)st);
// }

// void stack_print(struct stack const *st, void (*pf)(void const *st));

void fast_memswp(void* first, void* second, size_t size);

struct queue {
    char* data;
    size_t head, tail;
    size_t elem_size, size, capacity;
};


struct queue *queue_new(size_t elem_size) {
    struct queue* que = (struct queue*) calloc(1, sizeof(struct queue));
    que->head = que->tail = que->size = 0;
    que->capacity = base_size;
    que->data = (char*) malloc(elem_size * sizeof(char) * que->capacity);
    que->elem_size = elem_size;
    return que;
}
/*Создать новую очередь, которая способна хранить элементы размера elem_size, вернуть указатель на неё.*/

int queue_push(struct queue *q, const void *elem) {
    if (q == NULL || elem == NULL) return 1;

    if (q->size < q->capacity) {
        memcpy(q->data + q->elem_size * q->head, elem, q->elem_size);
        q->head = (q->head + 1) & mask;
        q->size++;
        return 0;
    }

    if (q->size == q->capacity) {
         //do some realloc shit
         assert(0);
    }
    return 0;
}
/*Добавить в голову очереди q элемент elem. Обратите внимание, что из elem должно быть извлечено для хранения 
ровно то количество байт, которой было специфицировано при создании данного стека. Функция должна вернуть 0 
при успехе и 1 при неуспехе любого рода. Амортизированная сложность этой операции должна быть O(1). 
После успешного исполнения данной операции в очереди должно оказаться на один элемент больше.*/


int queue_pop (struct queue *q, void *elem) {
    if (q == NULL || elem == NULL || q->size == 0) return 1;

    memcpy(elem, q->data + q->elem_size * q->tail, q->elem_size);
    q->tail = (q->tail + 1) & mask;
    q->size--;

    return 0;

}
/*Извлечь из хвоста очереди q элемент elem. Обратите внимание, что в elem должно быть положено ровно то 
количество байт, которой было специфицировано при создании данного стека. Функция должна вернуть 0 при успехе 
и 1 при неуспехе любого рода. Амортизированная сложность этой операции должна быть O(1).*/
int queue_empty(struct queue const *q) {
    if (q == NULL) return 0;

    return q->size == 0;
}
/*Функция-предикат. Она должна вернуть логическую истину (1), если очередь пуста и логический ноль (0) в 
противном случае.*/

struct queue *queue_delete(struct queue *q) {
    if (q == NULL) return NULL;

    free(q->data);
    free(q);
    return NULL;
}
/*Удалить объект q и вернуть NULL.*/

void queue_print(struct queue const *q, void (*pf)(void const *data)) {
    printf("[");
    if (q->size == 0) { printf("]\n"); return; };
    pf(q->data + q->elem_size * ((q->head  + q->capacity - 1) & mask));
    if (q->size == 1) { printf("]\n"); return; };
    for (size_t it = (q->head  + q->capacity - 2) & mask; ; it = (it + q->capacity - 1) & mask) {
        // printf("%lu it ", it);
        printf(", ");
        pf(q->data + q->elem_size * it);
        if (it == q->tail) break;
    }
    printf("]\n");

    return;
}
/*Так как очередь может содержать произвольные данные, но выводить информацию из неё необходимо, вторым 
аргументом функции является указатель на функцию, которая должна принимать указатель на данные, располагаемые 
в очереди и выводить их в соответствующем виде на стандартный вывод.
Общий формат должен быть такой: []\n — для пустой очереди. [3, 2, 1]\n — для очереди, 
в которую последовательно добавляли 1, 2, 3.*/

static void print_int(void const *st) {
   printf("%d", *(int *)st);
}

static void print_double(void const *st) {
   printf("%lf", *(double *)st);
}

int main() {
    struct queue *q = queue_new(sizeof (int));
    struct queue *q2 = queue_new(sizeof (double));
    for (int i = 0; i < 10; i++) {
        int tmp = i * i;
        double tmp2 = tmp;
        queue_push(q, &tmp);
        queue_push(q2, &tmp2);

    }

    queue_print(q, print_int);
    queue_print(q2, print_double);
    while (!queue_empty(q)) {
        int tmp;
        double tmp2;
        // printf("%d size\n", q->size);

        queue_pop(q, &tmp);
        // printf("%d int\n", tmp);
        queue_print(q, print_int);
        // printf("%d size\n", q->size);
        queue_pop(q2, &tmp2);
        // queue_print(q2, print_double);

        // printf("%lf double\n", tmp2);
    }                                                                                                                                                                                        
    queue_print(q, print_int);
    queue_print(q2, print_double);
    q = queue_delete(q);
    q2 = queue_delete(q2);
}
// Будут выведены все числа от 0 до 9 включительно.



// int main() {
//     struct queue *q = queue_new(sizeof (double));
//     for (int i = 0; i < 10; i++) {
//         double tmp = i * i;
//         queue_push(q, &tmp);
//     }
//     queue_print(q, print_double);
//     while (!queue_empty(q)) {
//         double tmp;
//         queue_pop(q, &tmp);
//         printf("%lf\n", tmp);
//         // printf("tail=%lu   head = %lu\n", q->tail, q->head);
//     queue_print(q, print_double);

//     }                                                                                                                                                                                        
 
//     q = queue_delete(q);
// }
// Будут выведены все числа от 0 до 9 включительно.