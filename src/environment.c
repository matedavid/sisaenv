#include "environment.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "instructions.h"

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

void execute_instruction(struct Environment *env) {
  uint8_t decimal_byte_low = env->memory[env->PC];
  uint8_t decimal_byte_high = env->memory[env->PC+1];

  uint8_t byte_low[8] = {0}, byte_high[8] = {0};
  decimal_to_base(decimal_byte_low, 2, &byte_low);
  decimal_to_base(decimal_byte_high, 2, &byte_high);

  uint8_t complete_code[16] = {0};
  for (int i = 15; i >= 0; --i) {
    if (i >= 8) complete_code[i] = byte_high[i-8];
    else complete_code[i] = byte_low[i];
  }
  
  uint8_t instruction_code[4] = {0};
  for (int i = 3; i >= 0; --i)
    instruction_code[i] = byte_high[i+4];
  
  uint8_t decimal_instruction_code = base_to_decimal(&instruction_code, 4, 2);
  if (decimal_instruction_code == 0 || decimal_instruction_code == 1) {
    uint8_t ra_binary[3] = {0}, rb_binary[3] = {0}, rd_binary[3] = {0}, specific_code[3] = {0};
    for (int i = 11; i >= 0; --i) {
      if (i <= 11 && i >= 9) ra_binary[i-9] = complete_code[i];
      else if (i <= 8 && i >= 6 && decimal_instruction_code != NOT) rb_binary[i-6] = complete_code[i];
      else if (i <= 6 && i >= 3) rd_binary[i-3] = complete_code[i];
      else specific_code[i] = complete_code[i];
    }
    
    int rd = base_to_decimal(rd_binary, 3, 2);
    int ra = base_to_decimal(ra_binary, 3, 2);
    int specific_code_decimal = base_to_decimal(specific_code, 3, 2);
    int rb;
    if (decimal_instruction_code != NOT) rb = base_to_decimal(rb_binary, 3, 2);
    else rb = 0;

    printf("%d\n", specific_code_decimal);

    int token = 8*decimal_instruction_code + specific_code_decimal;
    switch (token) {
      case AND:
        AND_f(rd, ra, rb);
        break;
      case OR:
        OR_f(rd, ra, rb);
        break;
      case XOR:
        XOR_f(rd, ra, rb);
        break;
      case NOT:
        NOT_f(rd, ra);
        break;
      case ADD:
        ADD_f(rd, ra, rb);
        break;
      case SUB:
        SUB_f(rd, ra, rb);
        break;
      case SHA:
        SHA_f(rd, ra, rb);
        break;
      case SHL:
        SHL_f(rd, ra, rb);
        break;
      default:
        printf("Something wrong happened when unparsing instruction\n");
        exit(-1);
        break;
        
    }

  }

}
