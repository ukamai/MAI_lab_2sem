#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

line l[MAX_TEXT_SIZE];
int n = 0;

int random();

void print_table()
{
    printf("====================\n");
    for (int i = 0; i < n; ++i) {
        printf("%d  ", l[i].key);
        printf("%s", l[i].str);
    }
    printf("====================\n");
}

void sorting()
{
    int left = 0, right = n - 1;
    int flag = 1;
    while ((left < right) && flag) {
        flag = 0;
        for (int i = left; i < right; i++) {
            if (l[i].key > l[i+1].key) {
                line tmp = l[i];
                l[i] = l[i + 1];
                l[i + 1] = tmp;
                flag = 1;
            }
        }
        right--;
        for (int i = right; i > left; i--) {
            if (l[i].key < l[i-1].key) {
                line tmp = l[i];
                l[i] = l[i - 1];
                l[i - 1] = tmp;
                flag = 1;
            }
        }
        left++;
    }
}

void random_table()
{
    for (int i = 0; i < n; ++i) {
        int j = random() % n;
        line t = l[i];
        l[i] = l[j];
        l[j] = t;
    }
}
