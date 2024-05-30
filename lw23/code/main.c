#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include <ctype.h>
#define MAXINPUT 100


void print_menu() {
    printf("1. Добавить вершину\n");
    printf("2. Удалить вершину\n");
    printf("3. Распечатать дерево\n");
    printf("4. Определить число вершин двоичного дерева\n");
    printf("5. Закончить работу программы\n");
}

int count_nodes(Tree* root) {
    if (root == NULL)
        return 0;

    int count = 0;
    count++;

    count += count_nodes(root->left); // Рекурсивный вызов для левого поддерева
    count += count_nodes(root->right); // Рекурсивный вызов для правого поддерева

    return count;
}

int main() {
    Tree* root = NULL;
    int value;
    int choice = 0;
    char input1[100];

    while (1) {
        print_menu();

        printf("Введите номер команды: ");

        fgets(input1, sizeof(input1), stdin);
        if (sscanf(input1, "%d", &choice) != 1) {
            printf("Некорректный ввод. Попробуйте еще раз.\n");
            continue;
        }

        switch (choice) {
                case 1:
                        printf("Введите значение элемента: ");
                        scanf("%d", &value);
                        root = insert(root, value);
                        break;
                case 2:
                        printf("Введите значение элемента для удаления: ");
                                scanf("%d", &value);
                                root = remove_Tree(root, value);
                        break;
                case 3:
                        printf("\nБинарное дерево: ");
                                printf("\n----------------------------------------\n");
                                print_tree(root, 1);
                                printf("\n----------------------------------------\n");
                        break;
                case 4:
                        printf("Число вершин: %d\n", count_nodes(root));
                        break;
                case 5:
                        free_tree(root);
                                return 0;
                        break;
                default:
                        printf("Ошибка: неправильный ввод. Попробуйте еще раз.\n");
                        break;
                }
        }
    free_tree(root);

    return 0;
}
