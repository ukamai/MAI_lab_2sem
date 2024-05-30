#ifndef LAB_WORKS_LIB_H
#define LAB_WORKS_LIB_H

#include "str.h"

// Структура узла бинарного дерева
typedef struct tree_node {
    int is_brackets_minus;
    String *value;
    struct tree_node *left;
    struct tree_node *right;
    struct tree_node *parent;
} BNode;

BNode *new_node(String*);

void show(BNode*, int, int, const char[2]);

int equal_trees(BNode*, BNode*);

void erase_tree(BNode*);

BNode *copy_tree(BNode*);

#endif