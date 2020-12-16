#include "environment.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void add_instruction(uint8_t *parsed_instruction, struct Environment *env) {
  uint8_t low_byte[8] = {0};
  uint8_t high_byte[8] = {0};
  memcpy(&low_byte, parsed_instruction, 8);
  memcpy(&high_byte, parsed_instruction+8, 8);

  uint8_t decimal_low_byte = base_to_decimal(&low_byte, 8, 2);
  uint8_t decimal_high_byte = base_to_decimal(&high_byte, 8, 2);

  env->memory[env->data_offset] = decimal_low_byte;
  env->memory[env->data_offset+1] = decimal_high_byte;
  env->data_offset += 2;
}

