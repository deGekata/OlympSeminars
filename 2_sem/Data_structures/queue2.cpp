

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
const int base_size = 5;
const int extend_coef = 2;

// static void print_double(void const *st) {
//    printf("%d", *(int *)st);
// }

// void stack_print(struct stack const *st, void (*pf)(void const *st));

void fast_memswp(void* first, void* second, size_t size);

struct stack {
    char* data;
    size_t size, capacity, elem_size;
};

struct stack *stack_new(size_t elem_size) {
    struct stack* st = (struct stack*) calloc (1, sizeof(struct stack));
    st->elem_size = elem_size;
    st->capacity = base_size;
    st->size = 0;
    st->data = (char*) malloc(elem_size * base_size);

    return st;
}
//Создать новый стек, который будет хранить элементы размера elem_size и вернуть указатель на него.

int stack_push(struct stack *st, const void *elem) {
    if (st == NULL || elem == NULL || st->data == NULL) return 1;
    
    if (st->size < st->capacity)  {
        memcpy(st->data + st->size * st->elem_size, elem, st->elem_size);
        st->size++;
        // printf("[");
        // stack_print(st, print_double);
        // printf("unspecial\n");
        return 1;
    }

    char* s_ptr = (char*) realloc(st->data, st->capacity * extend_coef * st->elem_size);

    if (s_ptr == NULL || st->data == NULL) return 1;

    st->data = s_ptr;
    st->capacity *= extend_coef;

    memcpy(st->data + st->size * st->elem_size, elem, st->elem_size);
    st->size++;
    // printf("[");
    // stack_print(st, print_double);
    // printf("special\n");
    return 0;

}
/*Добавить в стек st элемент elem. Обратите внимание, что из elem должно быть 
извлечено для хранения ровно то количество байт, которой было специфицировано при создании данного стека.
Функция должна вернуть 0 при успехе и 1 при неуспехе любого рода.
Амортизированная сложность этой операции должна быть O(1).
После успешного исполнения данной операции стек должен содержать на один элемент больше.*/

int stack_pop (struct stack *st, void *elem) {
    if (st == NULL || st->size == 0 || elem == 0) return 1;
    memcpy(elem, st->data + (st->size - 1) * st->elem_size, st->elem_size);

    st->size--;
    return 0;
}
/*Извлечь из стека st элемент elem и продвинуть стек вниз. 
Обратите внимание, что в elem должно быть положено ровно то количество байт, 
которой было специфицировано при создании данного стека.
 Функция должна вернуть 0 при успехе и 1 при неуспехе любого рода. 
 Амортизированная сложность этой операции должна быть O(1).*/

int stack_top (struct stack *st, void *elem) {
    if (st == NULL || st->size == 0) return 1;
    
    memcpy(elem, st->data + (st->size - 1) * st->elem_size, st->elem_size);

    return 0;
}
/*Извлечь из стека st элемент elem и оставить стек в предыдущем состоянии.
 Обратите внимание, что в elem должно быть положено ровно то количество байт,
  которой было специфицировано при создании данного стека.
   Функция должна вернуть 0 при успехе и 1 при неуспехе любого рода. 
   Амортизированная сложность этой операции должна быть O(1).*/

int stack_empty(struct stack const *st) {
    if (st == NULL) return 0;
    return st->size == 0;
}
/*Функция-предикат. Она должна вернуть логическую истину (1), если стек пуст и логический ноль (0) в противном случае.*/

struct stack *stack_delete(struct stack *st) {
    free(st->data);
    free(st);
    return NULL;
}
/*Удалить объект st и вернуть NULL.*/

void stack_print(struct stack const *st, void (*pf)(void const *st)) {
    printf("[");
    
    if (st->size == 0) { printf("]\n"); return;}

    pf(st->data);

    for (size_t it = 1; it < st->size; ++it) {
        printf(", ");
        // printf("%d", *(int*)(st->data + it * st->elem_size) );
        pf(st->data + it * st->elem_size);
    }

    printf("]\n");

    return;
}


struct queue {
    struct stack* begin, *end;
    size_t size;
};


struct queue *queue_new(size_t elem_size) {
    struct queue* que = (struct queue*) calloc(1, sizeof(struct queue));
    que->begin = stack_new(elem_size);
    que->end   = stack_new(elem_size);
    que->size = 0;
    return que;
}
/*Создать новую очередь, которая способна хранить элементы размера elem_size, вернуть указатель на неё.*/

int queue_push(struct queue *q, const void *elem) {
    if (q == NULL || elem == NULL) return 1;
    stack_push(q->begin, elem);
    q->size++;
    return 0;
}
/*Добавить в голову очереди q элемент elem. Обратите внимание, что из elem должно быть извлечено для хранения 
ровно то количество байт, которой было специфицировано при создании данного стека. Функция должна вернуть 0 
при успехе и 1 при неуспехе любого рода. Амортизированная сложность этой операции должна быть O(1). 
После успешного исполнения данной операции в очереди должно оказаться на один элемент больше.*/


int queue_pop (struct queue *q, void *elem) {
    if (q == NULL || elem == NULL || q->size == 0) return 1;

    if (q->end->size != 0) {
        stack_pop(q->end, elem);
        q->size--;
        return 0;
    } else {

        size_t stop = q->begin->size;
        char* el = (char*) malloc(q->begin->elem_size);
        for (size_t it = 0; it < stop; ++it) {
            stack_pop(q->begin, el);
            stack_push(q->end, el);    
        }
        free(el);
        stack_pop(q->end, elem);
        q->size--;
        return 0;
        
    }

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

    stack_delete(q->begin);
    stack_delete(q->end);
    free(q);
    return NULL;
}
/*Удалить объект q и вернуть NULL.*/
void queue_print(struct queue const *q, void (*pf)(void const *data)) {
    printf("[");
    if (q->size == 0) { printf("]\n"); return; };
    if (q->begin->size != 0) {
        pf(q->begin->data + (q->begin->size - 1) * (q->begin->elem_size));
        
        for (size_t stop = q->begin->size - 1; stop >= 1; --stop) {
            printf(", ");
            pf(q->begin->data + (stop - 1) * (q->begin->elem_size));
        }
    }
    // printf("delim");
    if (q->end->size != 0) {
        pf(q->end->data);
        size_t stop = q->end->size;
        for (size_t it = 1; it < stop; ++it) {
            printf(", ");
            pf(q->end->data + it * (q->end->elem_size));
        }
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