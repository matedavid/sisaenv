#include "parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

enum MNEMONIC token_to_mnemonic(char *token) {
  enum MNEMONIC mnemonic;
  // 3-R type
  if (strcmp(token, "AND") == 0)
    mnemonic = AND; 
  else if (strcmp(token, "OR") == 0)
    mnemonic = OR;
  else if (strcmp(token, "XOR") == 0)
    mnemonic = XOR;
  else if (strcmp(token, "NOT") == 0)
    mnemonic = NOT;
  else if (strcmp(token, "ADD") == 0)
    mnemonic = ADD;
  else if (strcmp(token, "SUB") == 0)
    mnemonic = SUB;
  else if (strcmp(token, "SHA") == 0)
    mnemonic = SHA;
  else if (strcmp(token, "SHL") == 0)
    mnemonic = SHL;

  else if (strcmp(token, "CMPLT") == 0)
    mnemonic = CMPLT;
  else if (strcmp(token, "CMPLE") == 0)
    mnemonic = CMPLE;
  else if (strcmp(token, "CMPEQ") == 0)
    mnemonic = CMPEQ;
  else if (strcmp(token, "CMPLTU") == 0)
    mnemonic = CMPLTU;
  else if (strcmp(token, "CMPLEU") == 0)
    mnemonic = CMPLEU;
  
  // 2-R type
  else if (strcmp(token, "ADDI") == 0)
    mnemonic = ADDI;
  else if (strcmp(token, "LD") == 0)
    mnemonic = LD;
  else if (strcmp(token, "ST") == 0)
    mnemonic = ST;
  else if (strcmp(token, "LDB") == 0)
    mnemonic = LDB;
  else if (strcmp(token, "STB") == 0)
    mnemonic = STB;
  else if (strcmp(token, "JALR") == 0)
    mnemonic = JALR;
  
  // 1-R type
  else if (strcmp(token, "BZ") == 0)
    mnemonic = BZ;
  else if (strcmp(token, "BNZ") == 0)
    mnemonic = BNZ;
  else if (strcmp(token, "MOVI") == 0)
    mnemonic = MOVI;
  else if (strcmp(token, "MOVHI") == 0)
    mnemonic = MOVHI;
  else if (strcmp(token, "IN") == 0)
    mnemonic = IN;
  else if (strcmp(token, "OUT") == 0)
    mnemonic = OUT;
  else
    mnemonic = NOT_EXISTS;
  
  return mnemonic;
}

uint8_t mnemonic_to_code(enum MNEMONIC mnemonic_token) {
  uint8_t decimal_code;
  if (mnemonic_token >= AND && mnemonic_token <= SHL)
    decimal_code = 0;
  else if (mnemonic_token >= CMPLT && mnemonic_token <= CMPLEU)
    decimal_code = 1;
  else if (mnemonic_token >= ADDI && mnemonic_token <= JALR)
    decimal_code = (int)mnemonic_token - 14;
  else if (mnemonic_token == BZ || mnemonic_token == BNZ)
    decimal_code = 8;
  else if (mnemonic_token == MOVI || mnemonic_token == MOVHI) 
    decimal_code = 9;
  else if (mnemonic_token == IN || mnemonic_token == OUT) 
    decimal_code = 10;
  return decimal_code;
}

void convert_type_3(uint8_t decimal_code, enum MNEMONIC token, int rd, int ra, int rb, uint8_t *complete_code) {
  uint8_t rd_binary[3] = {0}, ra_binary[3]  = {0}, rb_binary[3] = {0};
  decimal_to_base(rd, 2, &rd_binary);
  decimal_to_base(ra, 2, &ra_binary);
  decimal_to_base(rb, 2, &rb_binary);

  uint8_t code_binary[4] = {0};
  decimal_to_base(decimal_code, 2, &code_binary);

  uint8_t specific_code_binary[3] = {0};
  decimal_to_base((int)token%8, 2, &specific_code_binary);

  // Copy code
  for (int i = 3; i >= 0; --i)
    complete_code[15-(3-i)] = code_binary[i];
  // Copy registers
  for (int i = 11; i >= 3; --i) {
    if (i <= 11 && i >= 9) complete_code[i] = ra_binary[2-(11-i)];
    else if (i <= 8 && i >= 6) complete_code[i] = rb_binary[2-(8-i)];
    else complete_code[i] = rd_binary[2-(5-i)];
  }
  // Copy specific operation code
  for (int i = 2; i >= 0; --i)
    complete_code[i] = specific_code_binary[i];

}

void convert_type_2(uint8_t decimal_code, int ra, int rother, int N6, uint8_t *complete_code) {
  uint8_t ra_binary[3] = {0}, rother_binary[3] = {0}, N6_binary[6] = {0};
  decimal_to_base(ra, 2, &ra_binary);
  decimal_to_base(rother, 2, &rother_binary);
  
  // TODO: Add support for negative -> binary conversion
  if (N6 < 0) { 
    N6 = -N6;
    printf("Support for negative constants is not supported currently. Converting to positive.\n"); 
  }
  decimal_to_base(N6, 2, &N6_binary);
  
  uint8_t code_binary[4] = {0};
  decimal_to_base(decimal_code, 2, &code_binary);
  
  // Copy code
  for (int i = 3; i >= 0; --i)
    complete_code[15-(3-i)] = code_binary[i];
  // Copy registers
  for (int i = 11; i >= 6; --i) {
    if (i <= 11 && i >= 9) complete_code[i] = ra_binary[2-(11-i)];
    else complete_code[i] = rother_binary[2-(8-i)];
  }
  // Copy N6 constant 
  for (int i = 5; i >= 0; --i)
    complete_code[i] = N6_binary[i];
}

void parse_options(enum MNEMONIC token, char *options, uint8_t *complete_code) {
  if (token >= AND && token <= CMPLEU) {
    // Type 3-R
    char *register_d = strtok(options, ",");
    char *register_a = strtok(NULL, ",");
    char *register_b = strtok(NULL, ",");

    if (register_d == NULL || register_a == NULL || register_b == NULL) {
      // printf("'%s' is not formatted properly. Format should be: Rd,Ra,Rb\n", options);
      exit(-1);
    }

    int rd = (int)register_d[1] - (int)'0';
    int ra = (int)register_a[1] - (int)'0';
    int rb = (int)register_b[1] - (int)'0';

    convert_type_3(mnemonic_to_code(token), token, rd, ra, rb, complete_code);
  } else if (token >= ADDI && token <= JALR) {
    // Type 2-R
    char *register_a, *other_register;
    int N6; 
    if (token == LD || token == LDB) {
      other_register = strtok(options, ",");
      N6 = atoi(strtok(NULL, "("));
      register_a = strtok(NULL, ")");
    } else if (token == ST || token == STB) {
      N6 = atoi(strtok(options, "("));
      register_a = strtok(NULL, ")");
      other_register = strtok(NULL, ","); 
    } else {
      other_register = strtok(options, ",");
      register_a = strtok(NULL, ",");
      N6 = 0;
    }

    int ra = (int)register_a[1] - (int)'0';
    int rother = (int)other_register[1] - (int)'0';
    convert_type_2(mnemonic_to_code(token), ra, rother, N6, complete_code);
  } else {
    // Type 1-R
  }
}

void parse_mnemonic(char *mnemonic, uint8_t *complete_code) {
  char *token = strtok(mnemonic, " ");
  char *options = strtok(NULL, " "); 
  
  enum MNEMONIC mnemonic_token = token_to_mnemonic(token);
  
  // Check if mnemonic is defined in SISA
  if (mnemonic_token == NOT_EXISTS) {
    printf("'%s' is not a recognized SISA command\n", token);
    exit(-1);
  }

  uint8_t decimal_code = mnemonic_to_code(mnemonic_token);
  parse_options(mnemonic_token, options, complete_code);

}

