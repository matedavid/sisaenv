#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>

void decimal_to_base(int number, int base, int *binary);
int base_to_decimal(int *content, int size, int base);

void print_binary(int *binary, int size);

#endif
