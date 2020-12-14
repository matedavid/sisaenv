#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "parser.h"
#include "environment.h"

int main(int argc, char **argv) {
  if (argc <= 1) {
    printf("You need to specify a path to the file\n");
    return -1;
  }

  struct Environment env;
  int mem_size = 1000;
  env.memory = (uint8_t*)malloc(mem_size);
  env.PC = 0;
  env.data_offset = 0;

  uint16_t b = 0x0152;
  add_instruction(b, &env);
  
  /*
  FILE *fp;
  fp = fopen(argv[1], "r");

  char buff[255];
  while (fgets(buff, 255, fp)) {
    parse_mnemonic(buff);
  }
  */

  free(env.memory);
}
