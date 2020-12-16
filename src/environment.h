#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <stdint.h>
#include "utils.h"

struct Environment {
  uint8_t *memory;
  unsigned int PC;
  unsigned int data_offset;
};

void add_instruction(uint16_t command, struct Environment *env);

#endif
