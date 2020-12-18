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

  int decimal_instruction_code = base_to_decimal(&instruction_code, 4, 2);
  // if (decimal_instruction_code > 1) decimal_instruction_code += 14;

  // TODO: Create different functions for each type
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

    int token = 8*decimal_instruction_code + specific_code_decimal;
    switch (token) {
      // A/L instructions
      case AND:
        AND_f(rd, ra, rb, env);
        break;
      case OR:
        OR_f(rd, ra, rb, env);
        break;
      case XOR:
        XOR_f(rd, ra, rb, env);
        break;
      case NOT:
        NOT_f(rd, ra, env);
        break;
      case ADD:
        ADD_f(rd, ra, rb, env);
        break;
      case SUB:
        SUB_f(rd, ra, rb, env);
        break;
      case SHA:
        SHA_f(rd, ra, rb, env);
        break;
      case SHL:
        SHL_f(rd, ra, rb, env);
        break;
      // Cmp instructions
      case CMPLT:
        CMPLT_f(rd, ra, rb, env);
        break;
      case CMPLE:
        CMPLE_f(rd, ra, rb, env);
        break;
      case CMPEQ:
        CMPEQ_f(rd, ra, rb, env);
        break;
      case CMPLTU:
        CMPLTU_f(rd, ra, rb, env);
        break;
      case CMPLEU:
        CMPLEU_f(rd, ra, rb, env);
        break;
      default:
        printf("Something wrong happened when unparsing instruction\n");
        exit(-1);
        break;
        
    }

  } else if (decimal_instruction_code >= 3 && decimal_instruction_code <= 7) {

    uint8_t ra_binary[3] = {0}, other_r_binary[3] = {0}, N6_binary[6] = {0};
    for (int i = 11; i >= 0; --i) {
      if (i >= 9) ra_binary[i-9] = complete_code[i];
      else if (i <= 8 && i >= 6 && decimal_instruction_code != NOT) other_r_binary[i-6] = complete_code[i];
      else N6_binary[i] = complete_code[i];
    }
    
    int ra = base_to_decimal(ra_binary, 3, 2);
    int other_r = base_to_decimal(other_r_binary, 3, 2);
    int N6 = base_to_decimal(N6_binary, 6, 2);

    switch (decimal_instruction_code) {
      case 2:
        ADDI_f(ra, other_r, N6, env);
        break;
      case 3:
        LD_f(ra, other_r, N6, env);
        break;
      case 4:
        ST_f(ra, other_r, N6, env);
        break;
      case 5:
        LDB_f(ra, other_r, N6, env);
        break;
      case 6:
        STB_f(ra, other_r, N6, env);
        break;
      case 7:
        JALR_f(ra, other_r, env);
        break;
      default:
        printf("Something wrong happened when unparsing instruction: Instruction not recognized\n");
        exit(-1);
        break;
    }
  } else {
    uint8_t reg_binary[3] = {0}, N8_binary[8] = {0};
    uint8_t e_constant;
    for (int i = 11; i >= 0; --i) {
      if (i >= 9) reg_binary[i-9] = complete_code[i];
      else if (i == 8) e_constant = complete_code[i];
      else N8_binary[i] = complete_code[i];
    }

    int reg = base_to_decimal(reg_binary, 3, 2);
    int N8 = base_to_decimal(N8_binary, 8, 2);

    if (decimal_instruction_code == 8) {
      if (e_constant == 0) BZ_f(reg, N8, env);
      else BNZ_f(reg, N8, env);
    } else if (decimal_instruction_code == 9) {
      if (e_constant == 0) MOVI_f(reg, N8, env);
      else MOVHI_f(reg, N8, env);
    } else if (decimal_instruction_code == 10) {
      if (e_constant == 0) IN_f(reg, N8, env);
      else OUT_f(reg, N8, env);
    }
  }

}
