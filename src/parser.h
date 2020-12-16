#ifndef PARSER_H
#define PARSER_H

#include <stdint.h>

enum MNEMONIC {
  // 0 - 15: 3-R type
  AND, OR, XOR, NOT,
  ADD, SUB, SHA, SHL,
  CMPLT, CMPLE, EMPTY_1, CMPEQ, 
  CMPLTU, CMPLEU, EMPTY_2, EMPTY_3,

  // 16 - 21: 2-R type
  ADDI,
  LD,
  ST,
  LDB,
  STB,
  JALR,

  // 22 - 27: 1-R type
  BZ,
  BNZ,
  MOVI,
  MOVHI,
  IN,
  OUT,

  // Empty
  NOT_EXISTS
};

void parse_mnemonic(char *mnemonic, uint8_t *complete_code);

#endif
