#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

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
  env.registers = (uint16_t*)malloc(7); // 7 registers
  env.PC = 0;
  env.data_offset = 0;
  
  FILE *fp;
  fp = fopen(argv[1], "r");

  char buff[255];
  while (fgets(buff, 255, fp)) {
    // TODO: Create separate function to trim / sanitize input on utils file
    int size = strlen(buff);
    while (buff[size-1] == '\n' || buff[size-1] == ' ') {
      buff[size-1] = 0;
      --size;
    }

    uint8_t complete_code[16] = {0};
    parse_instruction(buff, &complete_code);

    add_instruction(&complete_code, &env);
  }
  
  while (env.PC != env.data_offset) {
    execute_instruction(&env);
    env.PC += 2;
  }

  free(env.memory);
  free(env.registers);
}
