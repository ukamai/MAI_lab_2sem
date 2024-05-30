/*
 * Операции работы со строками
 */

#include <stdlib.h>
#include <stdio.h>

#include "str.h"

// Создание нового итератора
Iterator *iterator(StringNode *node) {
    Iterator *iter = (Iterator*)malloc(sizeof(Iterator));
    iter->node = node;
    return iter;
}

// Переход к очередному значению итератора
void next(Iterator *iter) {
    iter->node = iter->node->next;
}

// Добавление символа к концу строки
void add(char chr, String *str) {
    StringNode *node = (StringNode*)malloc(sizeof(StringNode));
    node->chr = chr;
    node->next = NULL;
    if (!str->size)
        str->head = str->tail = node;
    else {
        str->tail->next = node;
        str->tail = node;
    }
    str->size++;
}

// Добавление символа в начало строки
void insert(char chr, String *str) {
    StringNode *node = (StringNode*)malloc(sizeof(StringNode));
    node->chr = chr;
    node->next = NULL;
    if (!str->size)
        str->head = str->tail = node;
    else {
        node->next = str->head;
        str->head = node;
    }
    str->size++;
}

// Создание пустой строки
String *string(void) {
    String *res = (String*)malloc(sizeof(String));
    res->head = res->tail = NULL;
    res->size = 0;
    res->is_operand = 0;
    return res;
}

// Создание строки из одного символа
String *chr_string(char chr) {
    String *res = string();
    add(chr, res);
    return res;
}

// Печать строки
void print(String *str) {
    Iterator *iter = iterator(str->head);
    while (iter->node != NULL) {
        printf("%c", iter->node->chr);
        next(iter);
    }
    free(iter);
}

// Удаление строки
void erase(String *str) {
    if (str == NULL)
        return;
    Iterator *iter = iterator(str->head);
    while (iter->node != NULL) {
        StringNode *temp = iter->node;
        next(iter);
        free(temp);
    }
    free(str);
    free(iter);
}

// Сравнение двух строк (0 - равны, -1 - первая лексикографически меньше, 1 - больше)
int compare(String *first, String *second) {
    if (first->size == second->size) {
        Iterator *f_iter = iterator(first->head);
        Iterator *s_iter = iterator(second->head);
        while (s_iter->node != NULL) {
            if (f_iter->node == NULL){
                free(f_iter);
                free(s_iter);
                return -1;
            }
            if (f_iter->node->chr > s_iter->node->chr) {
                free(f_iter);
                free(s_iter);
                return 1;
            }
            if (f_iter->node->chr < s_iter->node->chr) {
                free(f_iter);
                free(s_iter);
                return -1;
            }
            next(f_iter);
            next(s_iter);
        }
        free(f_iter);
        free(s_iter);
        return 0;
    }
    return 1;
}

// Возвращает копию данной строки
String *copy_string(String* str) {
    String *new = string();
    Iterator *iter = iterator(str->head);
    while (iter->node != NULL) {
        add(iter->node->chr, new);
        next(iter);
    }
    return new;
}