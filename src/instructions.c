#include "instructions.h"

#include <stdio.h>
#include <math.h>

/* A/L Instructions */

void AND_f(int rd, int ra, int rb, struct Environment *env) {
  uint16_t value_ra = env->registers[ra];
  uint16_t value_rb = env->registers[rb];

  uint16_t res = value_ra&value_rb;
  env->registers[rd] = res;
}

void OR_f(int rd, int ra, int rb, struct Environment *env) {
  uint16_t value_ra = env->registers[ra];
  uint16_t value_rb = env->registers[rb];

  uint16_t res = value_ra|value_rb;
  env->registers[rd] = res;
}

void XOR_f(int rd, int ra, int rb, struct Environment *env) {
  uint16_t value_ra = env->registers[ra];
  uint16_t value_rb = env->registers[rb];

  uint16_t res = value_ra^value_rb;
  env->registers[rd] = res;
}

void NOT_f(int rd, int ra, struct Environment *env) {
  uint16_t value_ra = env->registers[ra];

  uint16_t res = ~value_ra;
  env->registers[rd] = res;
}

void ADD_f(int rd, int ra, int rb, struct Environment *env) {
  uint16_t value_ra = env->registers[ra];
  uint16_t value_rb = env->registers[rb];

  uint16_t res = value_ra + value_rb;
  env->registers[rd] = res;
}

void SUB_f(int rd, int ra, int rb, struct Environment *env) {
  uint16_t value_ra = env->registers[ra];
  uint16_t value_rb = env->registers[rb];

  uint16_t res = value_ra - value_rb;
  env->registers[rd] = res;
}

void SHA_f(int rd, int ra, int rb, struct Environment *env) {
  printf("'SHA' not implemented\n");
}

void SHL_f(int rd, int ra, int rb, struct Environment *env) {
  printf("'SHL' not implemented\n");
}

/* CMP Instructions */

void CMPLT_f(int rd, int ra, int rb, struct Environment *env) {

}

void CMPLE_f(int rd, int ra, int rb, struct Environment *env) {

}

void CMPEQ_f(int rd, int ra, int rb, struct Environment *env) {

}

void CMPLTU_f(int rd, int ra, int rb, struct Environment *env) {

}

void CMPLEU_f(int rd, int ra, int rb, struct Environment *env) {

}

/* ADDI */

void ADDI_f(int ra, int rother, int N6, struct Environment *env) { 
  uint16_t value_ra = env->registers[ra];

  uint16_t res = value_ra + N6;
  env->registers[rother] = res;
} 

/* Memory Access */

void LD_f(int ra, int rother, int N6, struct Environment *env) {
  int value_ra = env->registers[ra];
  int mem_pos = value_ra+N6;
  
  int low_byte_decimal = env->memory[mem_pos];
  int high_byte_decimal = env->memory[mem_pos+1];

  uint8_t low_byte[8] = {0}, high_byte[8] = {0};
  decimal_to_base(low_byte_decimal, 2, &low_byte);
  decimal_to_base(high_byte_decimal, 2, &high_byte);

  uint8_t complete_byte[16] = {0};
  for (int i = 15; i >= 0; --i) {
    if (i >= 8) complete_byte[i] = high_byte[i-8];
    else complete_byte[i] = low_byte[i];
  }

  int res = base_to_decimal(&complete_byte, 16, 2);
  env->registers[rother] = res;
}

void ST_f(int ra, int rother, int N6, struct Environment *env) {

}

void LDB_f(int ra, int rother, int N6, struct Environment *env) {
  int value_ra = env->registers[ra];
  int mem_pos = value_ra+N6;
  
  // env->registers[rother] = env->memory[mem_pos];
  int low_byte_decimal = env->memory[mem_pos];

  uint8_t low_byte[8] = {0};
  decimal_to_base(low_byte_decimal, 2, &low_byte);

  uint16_t complete_byte[16] = {0};
  for (int i = 15; i >= 0; --i) {
    if (i >= 8) complete_byte[i] = low_byte[7];
    else complete_byte[i] = low_byte[i];
  }

  int res = base_to_decimal(&complete_byte, 16, 2);
  env->registers[rother] = res;
}

void STB_f(int ra, int rother, int N6, struct Environment *env) {

}

/* JALR */

void JALR_f(int ra, int rother, struct Environment *env) { }


