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
/*Так как стек может содержать произвольные данные, но выводить информацию из него необходимо, 
вторым аргументом функции является указатель на пользовательскую функцию, 
которая должна принимать указатель на элемент данных, располагающийся в стеке, 
и вывести его в соответствующем виде на стандартный вывод.
Вывод должен начитаться с открывающей квадратной скобки [, завершаться закрывающей квадратной скобкой 
с переходом на новую строку ]\n. После каждого элемента, кроме последнего, должна быть запятая.*/


static void print_double(void const *st) {
   printf("%d", *(int *)st);
}


int main() {
    struct stack *st = stack_new(sizeof (int));
    for (int i = 0; i < 10; i++) {
        int tmp = i * i;
        // printf("%d = tmp\n", tmp);
        stack_push(st, &tmp);
        // stack_print(st, print_double);
    }
    // stack_print(st, print_double);
    // printf("[");
    for (int i = 0; i < 11; i++) {
        int tmp;
        stack_pop(st, &tmp);
        printf("%d, tmp out\n", tmp);
    }
    stack_print(st, print_double);
    st = stack_delete(st);
    return 0;
}