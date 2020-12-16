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
  env.PC = 0;
  env.data_offset = 0;
  
  FILE *fp;
  fp = fopen(argv[1], "r");

  char buff[255];
  while (fgets(buff, 255, fp)) {
    // TODO: Create separate function to trim in utils
    int size = strlen(buff);
    while (buff[size-1] == '\n' || buff[size-1] == ' ') {
      buff[size-1] = 0;
      --size;
    }

    uint8_t complete_code[16] = {0};
    parse_mnemonic(buff, &complete_code);
    
    for (int i = 15; i >= 0; --i)
      printf("%d", complete_code[i]);
    printf("\n");

  }

  free(env.memory);
}
