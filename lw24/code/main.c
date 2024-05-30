#include <stdio.h>
#include <string.h>

#include "deque.h"
#include "tree.h"
#include "tools.h"

int main(void) {
    char chr[15];
    BNode *tree = NULL;
    printf("Type 'help' to take info\n\n ");

    while (1) {
        printf("expression> ");
        scanf("%s", chr);
        // Задание преобразуемого выражения
        if (!strcmp(chr, "set")) {
            erase_tree(tree);
            scanf(" ");
            Deque *input = deque_create();
            tree = new_node(NULL);
            // Считывание выражения и проверка на корректность
            int ok1 = read_expression(input), ok2 = parse_expression(input, tree);
            if (!ok1 || !ok2) {
                erase_tree(tree);
                tree = NULL;
                printf("\n Incorrect!\n\n ");
            }
            else {
                printf("\n");
                // Перевод выражения в дерево
                deque_print_expression(from_tree(tree));
                printf("\n OK\n\n ");
            }
            deque_erase(input);
        } else if (!strcmp(chr, "print")) {
            // Печать выражения
            if (tree == NULL)
                printf("\n NULL\n\n ");
            else {
                printf("\n");
                deque_print_expression(from_tree(tree));
                printf("\n\n ");
            }
        } else if (!strcmp(chr, "tree")) {
            // Печать дерева
            if (tree == NULL)
                printf("\n NULL\n\n ");
            else {
                printf("\n ");
                show(tree, 0, 1, "fr");
                printf("\n ");
            }
        } else if (!strcmp(chr, "trans")) {
            // Преобразование
            if (tree == NULL)
                printf("\n Expression is now NULL\n\n ");
            else {
                while (1) {
                    // Применятся, пока не будут преобразованы все подлежащие участки
                    BNode *temp = copy_tree(tree);
                    transform(tree);
                    if (equal_trees(tree, temp)) {
                        erase_tree(temp);
                        break;
                    }
                }
                printf("\n");
                deque_print_expression(from_tree(tree));
                printf("\n OK\n\n ");
            }
        } else if (!strcmp(chr, "exit")) return 0;
        else if (!strcmp(chr, "help")) {
            printf("\n set : set expression\n");
            printf(" print : print expression\n");
            printf(" tree : print expression tree\n");
            printf(" trans : replace ai to i in polynomial\n");
            printf(" exit : complete the work\n\n ");
        } else
            printf("\n Command not found!\n\n ");
    }
}
