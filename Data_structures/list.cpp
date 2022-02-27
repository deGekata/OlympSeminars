#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

struct list {
    struct list* next;
    int elem;
};

struct list *list_new(int elem) {
    struct list* lst = (struct list*) malloc (sizeof(struct list));
    lst->next = NULL;
    lst->elem = elem;
    return lst;
}
/*Создать новый узел со значением elem и вернуть указатель на него.*/

struct list *list_insert(struct list *head, int elem) {
    if (head == NULL) return list_new(elem);

    struct list* cur = head;
    while (cur->next != NULL) cur = cur->next;
    cur->next = list_new(elem);

    return head;
}
/*Вставить в конец списка с головой head узел со значением elem. 
Если голова списка пуста — создать новый список. Вернуть голову нового списка.*/


struct list *list_find(struct list *head, int elem) {
    while (head != NULL && head->elem != elem) head = head->next;

    if (head == NULL) return NULL;

    return head;
} 
/*Найти узел, начиная с головы списка, в котором значение будет 
равно elem и вернуть указатель на него. Если таких значений в 
списке нет, вернуть NULL.*/

struct list *list_erase(struct list *head, int elem) {
    if (head == NULL) return NULL;
    
    if (head->elem == elem) { struct list* cur = head->next; free(head); return cur;}

    struct list* cur = head;
    


    while (cur->next != NULL && cur->next->elem != elem) cur = cur->next;
    // printf("foudn");

    if (cur->next == NULL) return head;
    // printf("foudn");
    struct list* cur2 = cur->next;
    cur->next = cur->next->next;
    free(cur2);

    return head;
}
/*Найти узел, начиная с головы списка, в котором значение будет равно 
elem и удалить его из списка. Вернуть указатель на голову вновь получившегося списка.*/

struct list *list_insert_after(struct list *head, struct list *where, struct list *what) {
    if (head == NULL) {
        what->next = NULL;
        return what;
    }

    if (where == NULL || what == NULL) return head;

    what->next = where->next;
    where->next = what;

    return head;
}
/*Вставить узел what после узла where в списке, готова которого 
находится в head. Вернуть указатель на голову нового списка. 
Вставка в пустой список приводит к созданию непустого. 
Вставка NULL или после NULL есть пустая операция.*/

struct list *list_insert_before(struct list *head, struct list *where, struct list *what) {
    if (head == NULL) {
        what->next = NULL;
        return what;
    }

    if (where == NULL || what == NULL) return head;

    if (where == head) {
        what->next = head;
        return what;
    }

    struct list* cur = head;
    while (cur->next != NULL && cur->next != where) cur = cur->next;

    if (cur->next == NULL) return head;

    what->next = where;
    cur->next = what;

    return head;
}
/*Вставить узел what перед узлом where в списке, готова 
которого находится в head. Вернуть указатель на голову 
нового списка. Вставка в пустой список приводит к созданию 
непустого. Вставка NULL или после NULL есть пустая операция.*/

struct list *list_delete(struct list *head) {
    if (head == NULL) return NULL;

    struct list* cur = head;
    while (cur != NULL) {
        head = cur;
        cur = cur->next;
        free(head);
    }
    return NULL;
}
/*Удалить весь список, начинающийся с head. Вернуть NULL.*/

struct list *list_next(struct list *curr) {
    if (curr == NULL) return NULL;

    return curr->next;
}
/*Вернуть указатель на следующий элемент списка. Если curr пустой — вернуть NULL.*/

void list_print(struct list const *head) {
    printf("[");
    if (head == NULL) { printf("]\n"); return;}

    if (head != NULL) printf("%d", head->elem);
    head = head->next;
    while (head != NULL) {
        printf(", %d", head->elem);
        head = head->next;
    }
    printf("]\n");
    return;   
}
/*Вывести на стандартный вывод содержимое списка в формате по образцу: []\n или [1, 2, 3]\n.*/


int main() {
    struct list *head = list_new(0);
    head = list_insert(head, 1);
    head = list_insert(head, 2);
    head = list_insert(head, 3);
    head = list_erase(head, 2);
    list_print(head);
    head = list_delete(head);
    list_print(head);
}