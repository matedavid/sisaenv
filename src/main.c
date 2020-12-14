#include <stdio.h>
#include <stdlib.h>

#include "parser.h"

int main(int argc, char **argv) {
  if (argc <= 1) {
    printf("You need to specify a path to the file\n");
    return -1;
  }

  FILE *fp;
  fp = fopen(argv[1], "r");

  char buff[255];
  while (fgets(buff, 255, fp)) {
    parse_mnemonic(buff);
  }
}
