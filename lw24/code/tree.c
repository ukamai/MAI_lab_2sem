/*
 * Операции с деревьями
 */

#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

// Создание узла бинарного дерева
BNode *new_node(String *data) {
    BNode *node = (BNode*)malloc(sizeof(BNode));
    node->is_brackets_minus = 0;
    node->value = data;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    return node;
}

// Печать дерева с поэлементным обходом
void show(BNode *tree, int level, int jump, const char mode[2]) {
    if (mode[0] == 'f' && tree->value->head->chr != '\t') {
        if (jump) {
            printf("\n");
            for (int i = 0; i < level * 8 + 2; i++)
                printf(" ");
            printf(".\n");
            for (int i = 0; i < level * 8 + 2; i++)
                printf(" ");
            jump = 0;
        }

        if (tree->right == NULL) {
            printf(" . . . .");
            print(tree->value);
            jump = 1;
        } else {
            printf(" . . . .");
            print(tree->value);
        }
    }
    if (mode[0] == 'f') {
        if (tree->right == NULL && tree->left == NULL && tree->parent != NULL) {
            if (mode[1] == 'r')
                show(tree->parent, level - 1, jump, "br");
            else
                show(tree->parent, level - 1, jump, "bl");
        } else if (tree->right != NULL)
            show(tree->right, level + 1, jump, "fr");
        else if (tree->left != NULL)
            show(tree->left, level + 1, jump, "fl");

    } else if (mode[0] == 'b') {
        if (mode[1] == 'r' && tree->left != NULL)
            show(tree->left, level + 1, jump, "fl");
        else if (tree->parent != NULL) {
            if (tree->parent->right == tree)
                show(tree->parent, level - 1, jump, "br");
            else if (tree->parent->left == tree)
                show(tree->parent, level - 1, jump, "bl");
        }
    }
}

// Сравнение деревьев на равенство
int equal_trees(BNode *first, BNode *second) {
    if (first == NULL && second == NULL)
        return 1;
    if (((first == NULL) + (second == NULL)) % 2)
        return 0;
    if (!compare(first->value, second->value))
        return equal_trees(first->left, second->left) && equal_trees(first->right,
                                                                     second->right);
    return 0;
}

// Удаление дерева
void erase_tree(BNode *tree) {
    if (tree == NULL)
        return;
    erase(tree->value);
    erase_tree(tree->left);
    erase_tree(tree->right);
    free(tree);
}

// Возврат копии данного дерева
BNode *copy_tree(BNode *tree) {
    if (tree == NULL)
        return NULL;
    BNode *new = new_node(NULL);
    new->value = copy_string(tree->value);
    new->left = copy_tree(tree->left);
    new->right = copy_tree(tree->right);
    new->is_brackets_minus = tree->is_brackets_minus;
    if (new->left != NULL)
        new->left->parent = new;
    if (new->right != NULL)
        new->right->parent = new;
    return new;
}
