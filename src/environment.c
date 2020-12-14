#include "environment.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void decimal_to_binary(uint16_t number, uint8_t *binary) {
  int idx = 0;
  while (number > 0) {
    binary[idx] = (uint8_t)number%2;
    number /= 2;
    ++idx;
  }
}

uint8_t binary_to_decimal(uint8_t *binary, int size) {
  uint8_t decimal = 0;
  for (int i = 0; i < size; ++i)
    decimal += ( binary[i] * (uint8_t)pow(2, i) );
  return decimal;
}

// Adding with little endian (smaller byte first in memory) 
void add_instruction(uint16_t command, struct Environment *env) {
  // Convert to 2 byte binary
  uint8_t binary[16];
  decimal_to_binary(command, &binary);
  
  uint8_t low_byte[8];
  uint8_t high_byte[8];

  for (int i = 0; i  < 16; ++i) {
    if (i < 8) low_byte[i] = binary[i];
    else high_byte[i%8] = binary[i];
  }

  uint8_t low_decimal = binary_to_decimal(&low_byte, 8);
  uint8_t high_decimal = binary_to_decimal(&high_byte, 8);

  env->memory[env->data_offset] = low_decimal;
  env->memory[env->data_offset+1] = high_decimal;

  env->data_offset += 2;
}

