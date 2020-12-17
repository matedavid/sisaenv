#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "environment.h"
#include "utils.h"

// A/L instructions
void AND_f(int rd, int ra, int rb, struct Environment *env);
void OR_f(int rd, int ra, int rb, struct Environment *env);
void XOR_f(int rd, int ra, int rb, struct Environment *env);
void NOT_f(int rd, int ra, struct Environment *env);
void ADD_f(int rd, int ra, int rb, struct Environment *env);
void SUB_f(int rd, int ra, int rb, struct Environment *env);
void SHA_f(int rd, int ra, int rb, struct Environment *env);
void SHL_f(int rd, int ra, int rb, struct Environment *env);

// Cmp instructions
void CMPLT_f(int rd, int ra, int rb, struct Environment *env);
void CMPLE_f(int rd, int ra, int rb, struct Environment *env);
void CMPEQ_f(int rd, int ra, int rb, struct Environment *env);
void CMPLTU_f(int rd, int ra, int rb, struct Environment *env);
void CMPLEU_f(int rd, int ra, int rb, struct Environment *env);

// ADDI
void ADDI_f(int ra, int rother, int N6, struct Environment *env);

// Memory Access
void LD_f(int ra, int rother, int N6, struct Environment *env);
void ST_f(int ra, int rother, int N6, struct Environment *env);
void LDB_f(int ra, int rother, int N6, struct Environment *env);
void STB_f(int ra, int rother, int N6, struct Environment *env);

// JALR
void JALR_f(int ra, int rother, struct Environment *env);

// Jump instructions
void BZ_f(int reg, int N8, struct Environment *env);
void BNZ_f(int reg, int N8, struct Environment *env);

// Move instructions
void MOVI_f(int reg, int N8, struct Environment *env);
void MOVHI_f(int reg, int N8, struct Environment *env);

// IO instructions
void IN_f(int reg, int N8, struct Environment *env);
void OUT_f(int reg, int N8, struct Environment *env);

#endif
