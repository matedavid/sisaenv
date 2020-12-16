#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <stdint.h>
#include "parser.h"
#include "utils.h"

struct Environment {
  uint8_t *memory;
  unsigned int PC;
  unsigned int data_offset; // To prevent overwriting code, and to signal end of code
  uint16_t *registers;
};

void add_instruction(uint8_t *parsed_instruction, struct Environment *env);
void execute_instruction(struct Environment *env);

#endif
