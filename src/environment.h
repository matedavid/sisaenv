#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <stdint.h>
#include "parser.h"
#include "utils.h"

struct Environment {
  int *memory;
  unsigned int PC;
  unsigned int data_offset; // To prevent overwriting code, and to signal end of code
  int *registers;
};

void add_instruction(int *parsed_instruction, struct Environment *env);
void execute_instruction(struct Environment *env);

#endif
