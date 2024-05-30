#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdint.h>

#define MAX_STRING_SIZE 256
#define MAX_TEXT_SIZE 256

typedef struct {
    uint32_t key;
    char str[MAX_STRING_SIZE];
} line;

void print_table();
void shaker_sort();
void random_table();

#endif
