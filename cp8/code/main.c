#include <stdio.h>
#include "list.h"
#include "iterator.h"

#define MENU "Меню:\n1. Добавить значение\n2. Удалить значение\n3. Длина списка\n4. Операция\n5. Вывести список\n6. Завершить\nВвод: "

int main()
{
    int val;
    List *l = list_create();
    long data;
    bool flag = true;
    Iterator *it;
    while (flag)
    {
        printf(MENU);
        scanf("%d", &val);
        switch (val)
        {
        case 1:
            printf("Введите значение, которое нужно добавить: ");
            scanf("%ld", &data);
            list_insert(l->head, abs(data));
            break;
        case 2:
            printf("Введите значение, которое нужно удалить: ");
            scanf("%ld", &data);
            it = iter_create(l);
            if (iter_get_next_node(it)->data == data)
            {
                list_delete_next(it->node);
                break;
            }
            while (iter_next(it) != NULL)
            {
                if (iter_has_next(it))
                {
                    if (iter_get_next_node(it)->data == data)
                    {
                        list_delete_next(it->node);
                        break;
                    }
                }
            }
            free(it);
            break;
        case 3:
            printf("Длина списка: ");
            it = iter_create(l);
            printf("%d\n", list_length(it));
            free(it);
            break;
        case 4:
            it = iter_create(l);
            if (list_length(it) == 0)
            {
                printf("Длина списка равна нулю");
                break;
            }
            free(it);
            it = iter_create(l);
            printf("List is ");
            if (!check_sort(it))
            {
                printf("not ");
            }
            printf("sorted\n");
            free(it);
            break;
        case 5:
            printf("Список: ");
            it = iter_create(l);
            print_list(it);
            printf("\n");
            free(it);
            break;
        case 6:
            flag = false;
            break;
        default:
            printf("Неизвестная команда\n");
        }
    }
    list_destroy(l);
    free(l);
    return 0;
}
//конец программы
