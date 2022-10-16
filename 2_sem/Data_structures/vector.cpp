#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
const int base_size = 5;
const int extend_coef = 2;

struct vector {
    char* data;
    size_t size, capacity, elem_size;
};

struct vector *vector_new(size_t elems, size_t elem_size) {
    struct vector* st = (struct vector*) calloc (1, sizeof(struct vector));
    st->elem_size = elem_size;
    st->capacity = elems;
    st->size = elems;
    st->data = (char*) malloc(elem_size * elems);
    return st;
}
/*Создать новый вектор, который будет содержать elems элементов размера elem_size. 
Элементы не инициализированы.*/

int vector_push(struct vector *v, void const *elem) {
    if (v == NULL || elem == NULL || v->data == NULL) return 1;
    
    if (v->size < v->capacity)  {
        memcpy(v->data + v->size * v->elem_size, elem, v->elem_size);
        v->size++;
        // printf("[");
        // stack_print(st, print_double);
        // printf("unspecial\n");
        return 1;
    }

    v->data = (char*) realloc(v->data, (v->capacity * extend_coef + 1) * v->elem_size);

    // if (s_ptr == NULL || v->data == NULL) return 1;

    // v->data = s_ptr;
    v->capacity = v->capacity * extend_coef + 1;

    memcpy(v->data + v->size * v->elem_size, elem, v->elem_size);
    v->size++;

    return 0;
}
/*Добавить ещё один элемент elem к вектору v. Функция должна вернуть 0 при успехе и 1 
при неуспехе любого рода. Амортизированная сложность этой операции должна быть O(1). 
После успешного исполнения данной операции размер вектора должен увеличиться на единицу.*/

int vector_pop (struct vector *v, void *elem) {
    if (v == NULL || v->size == 0 || elem == 0) return 1;
    memcpy(elem, v->data + (v->size - 1) * v->elem_size, v->elem_size);

    v->size--;
    return 0;
}
/*Убрать из вектора v последний элемент, если он существует, и положить его значение по 
адресу elem. Функция должна вернуть 0 при успехе и 1 при неуспехе любого рода. 
Амортизированная сложность этой операции должна быть O(1).*/

int vector_empty(struct vector const *st) {
    if (st == NULL) return 0;
    return st->size == 0;
}
/*Функция-предикат. Она должна вернуть логическую истину (1), если вектор пуст и 
логический ноль (0) в противном случае.*/

struct vector *vector_delete(struct vector *v) {
    if (v == NULL) return NULL;
    if (v->data != NULL) free(v->data);
    free(v);
    return NULL;
}
/*Удалить объект st и вернуть NULL.*/

void vector_print(struct vector const *v, void (*pf)(void const *data)) {
    if (v == NULL) { printf("[]\n"); return;}
    printf("[");
    
    if (v->size == 0) { printf("]\n"); return;}

    pf(v->data);

    for (size_t it = 1; it < v->size; ++it) {
        printf(", ");
        // printf("%d", *(int*)(st->data + it * st->elem_size) );
        pf(v->data + it * v->elem_size);
    }

    printf("]\n");

    return;
}
/*Вывести на стандартный вывод содержимое вектора v. Второй аргумент — указатель на функцию, 
которая должна принимать указатель на одиночный элемент данных, хранимый в векторе и вывести 
его в соответствующем виде на стандартный вывод.*/
int vector_set(struct vector *v, size_t index, void const *elem) {
    if (v == NULL || elem == NULL || v->size <= index) return 1;

    memcpy(v->data + index * v->elem_size, elem, v->elem_size);


    return 0;
}
/*Присвоить элементу index вектора v значение elem. Вернуть 0, если операция успешна или 
1 в противном случае.*/
int vector_get(struct vector const *v, size_t index, void *elem) {
    if (v == NULL || elem == NULL || v->size <= index) return 1;
    
    memcpy(elem, v->data + index * v->elem_size, v->elem_size);


    return 0;
}
/*Присвоить elem значение элемента index вектора v. Вернуть 0, если операция успешна или 
1 в противном случае.*/

int vector_resize(struct vector *v, size_t new_size) {
    if (v == NULL || v->data == NULL) return 1;

    if (new_size <= v->capacity) {
        v->size = new_size;
        return 0;
    }

    v->data = (char*) realloc(v->data, (new_size + 1)  * v->elem_size);

    // if (s_ptr == NULL || v->data == NULL) return 1;

    
    v->size = new_size;

    v->capacity = (new_size + 1);
    
    
    return 0;
}
/*Изменить размер вектора v на new_size. Значение старых элементов вектора не должны измениться. 
Остальные элементы остаются неинициализированными. Вернуть 0, если операция успешна или 1 в противном случае.*/

size_t vector_size(struct vector const *v) {
    if (v == NULL) return 0;
    return v->size;
}
/*Возвратить количество элементов, которым владеет вектор v.*/



static void print_int(void const *data) {
   printf("%d", *(int *)data);
}

int main() {
    struct vector *v = vector_new(10, sizeof (int));
    printf("%ld size\n", v->capacity);
    
    for (int i = 0; i < 10; i++) {
        vector_set(v, i, &i);
        printf("%ld size\n", v->size);
    }
    printf("%ld size\n", v->size);
    vector_print(v, print_int);
    vector_resize(v, 5);
    vector_print(v, print_int);
    printf("%ld size\n", v->size);
    vector_resize(v, 30);
    vector_print(v, print_int);
    printf("%ld size\n", v->size);
    v = vector_delete(v);
}