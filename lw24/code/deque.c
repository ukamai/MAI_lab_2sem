/*
 * Операции, связанные с деком, используемом для первичной обработки выражения
 * Тип данных - строка, разработанная в str.c
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "deque.h"

// Удаление одного элемента дека
void delete(DequeNode *node, Deque *deq) {
    if (node->next != NULL && node->prev != NULL) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    } else if (node->next == NULL && node->prev != NULL) {
        node->prev->next = NULL;
        deq->tail = node->prev;
    }
    else if (node->next != NULL) {
        node->next->prev = NULL;
        deq->head = node->next;
    }
    deq->size--;
    if (deq->size == 0)
        deq->head = deq->tail = NULL;
    free(node);
}

// Создание пустого дека
Deque *deque_create(void) {
    Deque *list = (Deque*)malloc(sizeof(Deque));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

// Проверка на пустоту
bool deque_is_empty(Deque *deq) {
    return deq->size == 0;
}

// Добавление элемента в начало дека (слева)
void deque_push_front(String *value, Deque *deq) {
    DequeNode *element = (DequeNode*)malloc(sizeof(DequeNode));
    element->next = NULL;
    element->value = value;

    if (deq->head == NULL) {
        deq->head = deq->tail = element;
        element->prev = NULL;
        deq->size = 1;
        return;
    }

    deq->tail->next = element;
    element->prev = deq->tail;
    deq->tail = element;
    deq->size++;
}

// Добавление элемента в конец дека (справа)
void deque_push_back(String *value, Deque *deq) {
    DequeNode *element = (DequeNode*)malloc(sizeof(DequeNode));
    element->prev = NULL;
    element->value = value;

    if (deq->head == NULL) {
        deq->head = deq->tail = element;
        element->next = NULL;
        deq->size = 1;
        return;
    }

    deq->head->prev = element;
    element->next = deq->head;
    deq->head = element;
    deq->size++;
}

// Удаление элемента и возврат из начала дека
String *deque_pop_front(Deque *deq) {
    String *temp = deq->tail->value;
    delete(deq->tail, deq);
    return temp;
}

// Удаление элемента и возврат из конца дека
String *deque_pop_back(Deque *deq) {
    String *temp = deq->head->value;
    delete(deq->head, deq);
    return temp;
}

// Вывод содержимого дека в формате мат. выражения (с расстановкой пробелов)
void deque_print_expression(Deque *exp) {
    Deque *temp = deque_create();
    while (!deque_is_empty(exp)) {
        String *now = deque_pop_back(exp);
        if (deque_is_empty(temp) || (temp->tail->value->head->chr != '(' && now->head->chr != ')'))
            printf(" ");
        print(now);
        deque_push_front(now, temp);
    }
    while (!deque_is_empty(temp))
        deque_push_back(deque_pop_front(temp), exp);
    deque_erase(temp);
}

// Размер дека
int deque_size(Deque *deq) {
    return deq->size;
}

// Удаление дека
void deque_erase(Deque *deq) {
    while (!deque_is_empty(deq)) {
        String *temp = deque_pop_back(deq);
        erase(temp);
    }
    free(deq);
}

