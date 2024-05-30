#ifndef LAB_WORKS_2_TOOLS_H
#define LAB_WORKS_2_TOOLS_H

// Перечисление с обозначениями видов операторов
typedef enum {
    PLUS_MINUS,
    MUL_DIV,
    POWER,
    NONE
} Type;

int read_expression(Deque*);

int parse_expression(Deque*, BNode*);

void transform(BNode*);

Deque *from_tree(BNode*);

#endif
