#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Convert decimal to base
void decimal_to_base(uint16_t number, int base, uint8_t *binary) {
  int idx = 0;
  while (number > 0) {
    binary[idx] = (uint8_t)number%base;
    number /= base;
    ++idx;
  }
}

// Convert base to decimal
int base_to_decimal(uint8_t *content, int size, int base) {
  int decimal = 0;
  for (int i = 0; i < size; ++i)
    decimal += ( content[i] * pow(base, i) );
  return decimal;
}
