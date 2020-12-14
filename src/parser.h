#ifndef PARSER_H
#define PARSER_H

enum MNEMONIC {
  // 0 - 12: 3-R type
  AND, OR, XOR, NOT,
  ADD, SUB, SHA, SHL,
  CMPLT, CMPLE, CMPLEQ, 
  CMPLTU, CMPLEU,

  // 13 - 18: 2-R type
  ADDI,
  LD,
  ST,
  LDB,
  STB,
  JALR,

  // 19 - 24: 1-R type
  BZ,
  BNZ,
  MOVI,
  MOVHI,
  IN,
  OUT,

  // Empty
  NOT_EXISTS
};

void parse_mnemonic(char *mnemonic);

#endif
