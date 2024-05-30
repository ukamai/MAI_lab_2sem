#ifndef LAB_WORKS_2_STR_H
#define LAB_WORKS_2_STR_H

// Структура элемента строки с одним символом
typedef struct node {
    char chr;
    // Ссылка на следующий элемент
    struct node *next;
} StringNode;

// Структура строки
typedef struct {
    StringNode *head;
    StringNode *tail;
    int size;
    // Флаг, который будет отвечать за то, является ли данная строка операндом
    int is_operand;
} String;

// Структура итератора
typedef struct {
    StringNode *node;
} Iterator;

void add(char, String*);

void insert(char, String*);

String *string(void);

String *chr_string(char);

void print(String*);

void erase(String*);

int compare(String*, String*);

String *copy_string(String*);

#endif
