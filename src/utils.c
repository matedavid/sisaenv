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
uint8_t base_to_decimal(uint8_t *content, int size, int base) {
  uint8_t decimal = 0;
  for (int i = 0; i < size; ++i)
    decimal += ( content[i] * (uint8_t)pow(base, i) );
  return decimal;
}
