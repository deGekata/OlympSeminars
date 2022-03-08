#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <inttypes.h>
#include <string.h>
#include <ctype.h>

/*
У нас задача проще. В единственной строке входного файла, длиной до 102400 символов, 
присутствуют только упомянутые выше символы.
*/


const int base_size = 5;
const int extend_coef = 2;

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

int stack_push(struct stack *st, const void *elem) {
    if (st == NULL || elem == NULL || st->data == NULL) return 1;
    
    if (st->size < st->capacity)  {
        memcpy(st->data + st->size * st->elem_size, elem, st->elem_size);
        st->size++;
        return 1;
    }

    char* s_ptr = (char*) realloc(st->data, st->capacity * extend_coef * st->elem_size);

    if (s_ptr == NULL || st->data == NULL) return 1;

    st->data = s_ptr;
    st->capacity *= extend_coef;

    memcpy(st->data + st->size * st->elem_size, elem, st->elem_size);
    st->size++;

    return 0;

}

int stack_pop (struct stack *st, void *elem) {
    if (st == NULL || st->size == 0 || elem == 0) return 1;
    memcpy(elem, st->data + (st->size - 1) * st->elem_size, st->elem_size);

    st->size--;
    return 0;
}

int stack_top (struct stack *st, void *elem) {
    if (st == NULL || st->size == 0) return 1;
    
    memcpy(elem, st->data + (st->size - 1) * st->elem_size, st->elem_size);

    return 0;
}


int stack_empty(struct stack const *st) {
    if (st == NULL) return 0;
    return st->size == 0;
}

struct stack *stack_delete(struct stack *st) {
    free(st->data);
    free(st);
    return NULL;
}

int main() {
    struct stack* st = stack_new(sizeof(char));

    char* arr = (char*) malloc(102400 * sizeof(char));
    scanf("%s", arr);
    int N = strlen(arr);

    for (int it = 0; it < N; ++it) {

        if (arr[it] == '<' || arr[it] == '[' || arr[it] == '(' || arr[it] == '{') {
            stack_push(st, &arr[it]);
        } else {
            if (stack_empty(st)) {
                printf("NO");
                return 0;
            }
            char tmp;
            stack_pop(st, &tmp);
            if ((tmp == '(' && arr[it] == ')') ||
                (tmp == '[' && arr[it] == ']') ||
                (tmp == '<' && arr[it] == '>') ||
                (tmp == '{' && arr[it] == '}')) {
                    continue;
            }
            stack_delete(st);
            printf("NO");
            return 0;
        }
    }
    if (stack_empty(st))
        printf("YES");
    else
        printf("NO");

    stack_delete(st);
    return 0;
}

/*
Память: O(N), Время: O(N);
*/