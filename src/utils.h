#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>

void decimal_to_base(int number, int base, int *binary);
int base_to_decimal(int *content, int size, int base);

// Convert decimal <--> binary in 2's complement 
void decimal_to_base_ca2(int number, int base, int size, int *binary);
int base_to_decimal_ca2(int *content, int size, int base);

void print_binary(int *binary, int size);

#endif
