#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Convert decimal to base
void decimal_to_base(int number, int base, int *binary) {
  int idx = 0;
  while (number > 0) {
    binary[idx] = number%base;
    number /= base;
    ++idx;
  }
}

// Convert base to decimal
int base_to_decimal(int *content, int size, int base) {
  int decimal = 0;
  for (int i = 0; i < size; ++i) {
    int power_value = pow(base, i);
    decimal += content[i] * power_value;
  }
  return decimal;
}

void decimal_to_base_ca2(int number, int base, int *binary) {

}

int base_to_decimal_ca2(int *content, int size, int base) {
  int xs = 0;
  xs += -content[size-1]*(int)pow(base, size-1);
  
  for (int i = size-2; i >= 0; --i)
    xs += content[i] * (int)pow(base, i);
  return xs;
}

void print_binary(int *binary, int size) {
  for (int i = size-1; i >= 0; --i)
    printf("%d", binary[i]);
  printf("\n");
}
