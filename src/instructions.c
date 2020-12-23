#include "instructions.h"

#include <stdio.h>
#include <math.h>

#include "utils.h"

/* A/L Instructions */

void AND_f(int rd, int ra, int rb, struct Environment *env) {
  int value_ra = env->registers[ra];
  int value_rb = env->registers[rb];

  int res = value_ra&value_rb;
  env->registers[rd] = res;
}

void OR_f(int rd, int ra, int rb, struct Environment *env) {
  int value_ra = env->registers[ra];
  int value_rb = env->registers[rb];

  int res = value_ra|value_rb;
  env->registers[rd] = res;
}

void XOR_f(int rd, int ra, int rb, struct Environment *env) {
  int value_ra = env->registers[ra];
  int value_rb = env->registers[rb];

  int res = value_ra^value_rb;
  env->registers[rd] = res;
}

void NOT_f(int rd, int ra, struct Environment *env) {
  int value_ra = env->registers[ra];

  int res = ~value_ra;
  env->registers[rd] = res;
}

void ADD_f(int rd, int ra, int rb, struct Environment *env) {
  int value_ra = env->registers[ra];
  int value_rb = env->registers[rb];

  int res = value_ra + value_rb;
  env->registers[rd] = res;
}

void SUB_f(int rd, int ra, int rb, struct Environment *env) {
  int value_ra = env->registers[ra];
  int value_rb = env->registers[rb];

  int res = value_ra - value_rb;
  env->registers[rd] = res;
}

void SHA_f(int rd, int ra, int rb, struct Environment *env) {
  printf("'SHA' not implemented\n");
}

void SHL_f(int rd, int ra, int rb, struct Environment *env) {
  int value_ra = env->registers[ra];
  int value_rb = env->registers[rb];
  
  int res;
  if (value_rb >= 0) {
    res = value_ra << value_rb;
  } else {
    res = value_ra >> -value_rb;
  }

  env->registers[rd] = res;
}

/* CMP Instructions */

void CMPLT_f(int rd, int ra, int rb, struct Environment *env) {
  int value_ra = env->registers[ra];
  int value_rb = env->registers[rb];

  int value_ra_binary[16] = {0}, value_rb_binary[16] = {0};
  decimal_to_base(value_ra, 2, &value_ra_binary);
  decimal_to_base(value_rb, 2, &value_rb_binary);
    
  int value_ra_ca2 = base_to_decimal_ca2(&value_ra_binary, 16, 2);
  int value_rb_ca2 = base_to_decimal_ca2(&value_rb_binary, 16, 2);

  int res = value_ra_ca2 < value_rb_ca2;
  env->registers[rd] = res;
}

void CMPLE_f(int rd, int ra, int rb, struct Environment *env) {
  int value_ra = env->registers[ra];
  int value_rb = env->registers[rb];

  int value_ra_binary[16] = {0}, value_rb_binary[16] = {0};
  decimal_to_base(value_ra, 2, &value_ra_binary);
  decimal_to_base(value_rb, 2, &value_rb_binary);
    
  int value_ra_ca2 = base_to_decimal_ca2(&value_ra_binary, 16, 2);
  int value_rb_ca2 = base_to_decimal_ca2(&value_rb_binary, 16, 2);

  int res = value_ra_ca2 <= value_rb_ca2;
  env->registers[rd] = res;
}

void CMPEQ_f(int rd, int ra, int rb, struct Environment *env) {
  int value_ra = env->registers[ra];
  int value_rb = env->registers[rb];

  int res = value_ra == value_rb;
  env->registers[rd] = res;
}

void CMPLTU_f(int rd, int ra, int rb, struct Environment *env) {
  int value_ra = env->registers[ra];
  int value_rb = env->registers[rb];

  int res = value_ra < value_rb;
  env->registers[rd] = res;
}

void CMPLEU_f(int rd, int ra, int rb, struct Environment *env) {
  int value_ra = env->registers[ra];
  int value_rb = env->registers[rb];

  int res = value_ra <= value_rb;
  env->registers[rd] = res;
}

/* ADDI */

void ADDI_f(int ra, int rother, int N6, struct Environment *env) { 
  int value_ra = env->registers[ra];

  int res = value_ra + N6;
  env->registers[rother] = res;
} 

/* Memory Access */

void LD_f(int ra, int rother, int N6, struct Environment *env) {
  int value_ra = env->registers[ra];
  int mem_pos = value_ra+N6;
  
  int low_byte_decimal = env->memory[mem_pos];
  int high_byte_decimal = env->memory[mem_pos+1];

  int low_byte[8] = {0}, high_byte[8] = {0};
  decimal_to_base_ca2(low_byte_decimal, 2, 8, &low_byte);
  decimal_to_base_ca2(high_byte_decimal, 2, 8, &high_byte);

  int complete_byte[16] = {0};
  for (int i = 15; i >= 0; --i) {
    if (i >= 8) complete_byte[i] = high_byte[i-8];
    else complete_byte[i] = low_byte[i];
  }

  int res = base_to_decimal_ca2(&complete_byte, 16, 2);
  env->registers[rother] = res;
}

void ST_f(int ra, int rother, int N6, struct Environment *env) {
  int ra_value = env->registers[ra];
  int mem_pos = ra_value + N6;

  int rother_value = env->registers[rother];
  int complete_byte[16] = {0};
  decimal_to_base_ca2(rother_value, 2, 16, &complete_byte);

  int low_byte[8] = {0}, high_byte[8] = {0};
  for (int i = 15; i >= 0; --i) {
    if (i >= 8) high_byte[i-8] = complete_byte[i];
    else low_byte[i] = complete_byte[i];
  }

  int low_byte_decimal = base_to_decimal_ca2(&low_byte, 8, 2);
  int high_byte_decimal = base_to_decimal_ca2(&high_byte, 8, 2);

  env->memory[mem_pos] = low_byte_decimal;
  env->memory[mem_pos+1] = high_byte_decimal;
}

void LDB_f(int ra, int rother, int N6, struct Environment *env) {
  int value_ra = env->registers[ra];
  int mem_pos = value_ra+N6;
  
  // env->registers[rother] = env->memory[mem_pos];
  int low_byte_decimal = env->memory[mem_pos];

  int low_byte[8] = {0};
  decimal_to_base_ca2(low_byte_decimal, 2, 8, &low_byte);

  int complete_byte[16] = {0};
  for (int i = 15; i >= 0; --i) {
    if (i >= 8) complete_byte[i] = low_byte[7];
    else complete_byte[i] = low_byte[i];
  }

  int res = base_to_decimal_ca2(&complete_byte, 16, 2);
  env->registers[rother] = res;
}


// TODO: Make sure STB is implemented correclty
void STB_f(int ra, int rother, int N6, struct Environment *env) {
  int ra_value = env->registers[ra];
  int mem_pos = ra_value + N6;

  int rother_value = env->registers[rother];
  int complete_byte[16] = {0};
  decimal_to_base_ca2(rother_value, 2, 8, &complete_byte);

  int low_byte[8] = {0};
  for (int i = 7; i >= 0; --i)
    low_byte[i] = complete_byte[i];

  int low_byte_decimal = base_to_decimal_ca2(&low_byte, 8, 2);
  env->memory[mem_pos] = low_byte_decimal;
}

/* JALR */

void JALR_f(int ra, int rother, struct Environment *env) {

}

/* BZ / BNZ */

void BZ_f(int reg, int N8, struct Environment *env) {
  int value_reg = env->registers[reg];
  if (value_reg == 0)
    env->PC += N8*2;
}

void BNZ_f(int reg, int N8, struct Environment *env) {
  int value_reg = env->registers[reg];
  if (value_reg != 0)
    env->PC += N8*2;
}

/* MOVI / MOVHI */

void MOVI_f(int reg, int N8, struct Environment *env) {
  env->registers[reg] = N8;
}

void MOVHI_f(int reg, int N8, struct Environment *env) {
   
}

/* IN / OUT */

void IN_f(int reg, int N8, struct Environment *env) {
  printf("IN: ");
  int input;
  scanf("%hd", &input);
  
  env->registers[reg] = input;
}

void OUT_f(int reg, int N8, struct Environment *env) {
  int val = env->registers[reg];
  printf("OUT: %d\n", val);
}

