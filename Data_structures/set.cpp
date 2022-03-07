#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

struct set {
    int* data;
    size_t size, capacity;
};

struct set *set_new(size_t capacity) {
    struct set* st = (struct set*) malloc(sizeof(struct set));
    st->data = (int*) calloc(capacity, sizeof(int));
    st->size = 0;
    st->capacity = capacity;
    
    return st;
 }
/*Создать новое пустое множество, значения элементов которого могут лежать в 
границах от 0 до capacity-1 включительно. Вернуть указатель на него.*/

int set_insert(struct set *s, size_t elem) {
    if (s == NULL || s->capacity <= elem) { return 1; }

    if (s->data[elem] == 0) {
        s->size++;
        s->data[elem] = 1;
    }

    return 0;
}
/*Добавить во множество s элемент elem. Если элемент существовал, множество не 
изменится. Вернуть 0, если операция корректна, т.е. elem < capacity, иначе вернуть 1.*/

int set_erase(struct set *s, size_t elem) {
    if (s == NULL || s->capacity <= elem) { return 1; }

    if (s->data[elem] == 1) {
        s->size--;
        s->data[elem] = 0;
    }

    return 0;
}

/*Удалить элемент из множества. Если элемент не существовал, множество не изменится. 
Вернуть 0, если операция корректна, т.е. elem < capacity, иначе вернуть 1.*/

int set_find(struct set const *s, size_t elem) {
    if (s == NULL || s->capacity <= elem) { return 0; }

    return s->data[elem];
}
/*Вернуть 1, если элемент присутствует в множестве и 0 в противном случае.*/

struct set *set_delete(struct set *s) {
    if (s == NULL) return NULL;
    free(s->data);
    free(s);
    return NULL;
}
/*Удалить объект множество и вернуть NULL*/

int set_empty(struct set const *s) {
    if (s == NULL) return 0;
    return s->size != 0;
}
/*Предикат: вернуть единицу, если в множестве есть хотя бы один элемент и ноль в противном случае.*/

ssize_t set_findfirst(struct set const *s, size_t start) {
    if (s == NULL || s->capacity <= start) return -1;

    for (size_t st = start; st < s->capacity; ++st) {
        if (s->data[st] == 1) return st;
    }
    return -1;
}
/*Вернуть наименьший из элементов множества, не меньших start. Если таких элементов нет 
(например, множество пустое), то вернуть -1.*/

size_t set_size(struct set const *s) {
    if (s == NULL) return 0;
    return s->size;
}
/*Вернуть количество элементов множества.*/
void set_print(struct set const *s) {
    if (s == NULL || s->size == 0) { printf("[]\n"); return; }

    size_t st = 0;
    while (st < s->capacity && s->data[st] == 0) st++;

    if (st == s->capacity) {printf("[]\n"); return;}

    printf("[%ld", st);
    st++;
    while (st < s->capacity) {
        if (s->data[st] != 0) {
            printf(", %ld", st);
        } 
        st++;
    }
    printf("]\n");

    return;
}
/*Вывести на стандартный вывод содержимое множества в формате по образцу: []\n или [1, 2, 3]\n.*/


int main() {
    struct set *s = set_new(10);
    assert(set_insert(s, 1) == 0);
    assert(set_insert(s, 2) == 0);
    assert(set_insert(s, 100) != 0);
    assert(set_size(s) == 2);
    set_print(s);            
    assert(set_find(s,1) != 0);
    assert(set_find(s,100) == 0);
    assert(set_insert(s, 5) == 0);
    assert(set_erase(s,2) == 0);
    assert(set_findfirst(s, 2) == 5);
    assert(set_findfirst(s, 10) == -1);
    assert(set_delete(s) == NULL);
}
     