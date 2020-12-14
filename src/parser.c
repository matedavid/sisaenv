#include "parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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


void parse_mnemonic(char *mnemonic, enum MNEMONIC, char) {
  char *token = strtok(mnemonic, " ");
  char *options = strtok(NULL, " "); 
  
  enum MNEMONIC mnemonic_token = token_to_mnemonic(token);
  
  // Check if mnemonic is defined in SISA
  if (mnemonic_token == NOT_EXISTS) {
    printf("'%s' is not a recognized SISA command\n", token);
    exit(-1);
  }
  printf("%d %s", mnemonic_token, options);
}
