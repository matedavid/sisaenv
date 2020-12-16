#include "environment.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void add_instruction(uint16_t command, struct Environment *env) {
  // Convert decimal command to binary
  uint8_t binary[16];
  decimal_to_base(command, 2, &binary);
  
  // Separate 16 bit binary into two 8 bit parts 
  uint8_t low_byte[8];
  uint8_t high_byte[8];

  for (int i = 0; i  < 16; ++i) {
    if (i < 8) low_byte[i] = binary[i];
    else high_byte[i%8] = binary[i];
  }
  
  // Convert 8 bit binary into decimal 
  uint8_t low_decimal = base_to_decimal(&low_byte, 8, 2);
  uint8_t high_decimal = base_to_decimal(&high_byte, 8, 2);

  // Adding with little endian (smaller byte first in memory) into memory
  env->memory[env->data_offset] = low_decimal;
  env->memory[env->data_offset+1] = high_decimal;

  env->data_offset += 2;
}

