#ifndef LAB_WORKS_2_DEQUE_H
#define LAB_WORKS_2_DEQUE_H

#include <stdbool.h>
#include "str.h"

// Структура элемента дека
typedef struct deque_node {
    // Строка - значение
    String *value;
    // Ссылка на пред. элемент
    struct deque_node *prev;
    // Ссылка на след. элемент
    struct deque_node *next;
} DequeNode;

// Структура дека
typedef struct {
    // Ссылка на первый элемент
    DequeNode *head;
    // Ссылка на последний элемент
    DequeNode *tail;
    // Размер
    int size;
} Deque;

Deque *deque_create(void);

bool deque_is_empty(Deque*);

void deque_push_front(String*, Deque*);

void deque_push_back(String*, Deque*);

String *deque_pop_front(Deque*);

String *deque_pop_back(Deque*);

int deque_size(Deque*);

void deque_print_expression(Deque*);

void deque_erase(Deque*);

#endif
