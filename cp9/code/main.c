#include <stdbool.h>
#include "functions.h"
#include "functions.c"

int main() {
    FILE *f = fopen("input", "r");
    FILE *k = fopen("key", "r");
    if (!(f) || !(k)) {
        printf("Error, can`t open files\n");
        return 0;
    }
    while (!feof(f)) {
        fgets(l[n].str, MAX_STRING_SIZE, f);
        fscanf(k, "%d", &l[n].key);
        ++n;
    }
    --n;
    int ans, c = 1;
    while (c) {
        printf("1. Print table\t 2. Sort\t 3. Random\t 4. Exit\n");
        scanf("%d", &ans);
        switch (ans) {
            case 1: {
                print_table();
                break;
            }
            case 2: {
                printf("Before:\n");
                print_table();
                sorting();
                printf("After:\n");
                print_table();
                break;
            }
            case 3: {
                random_table();
                break;
            }
            case 4: {
                c = 0;
                break;
            }
            default: {
                printf("Wrong answer\n");
            }
        }
    }
	fclose(f);
	fclose(k);
    return 0;
}
