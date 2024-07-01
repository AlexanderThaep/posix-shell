#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <errno.h>
#include "parser.h"

#define PROGRAM_NAME "shell"

#define DELIM " \n"

int main(int argc, char** argv) {
  bool interactive = false;
  FILE* fp;
  
  if (argc == 2) {
    fp = fopen(argv[1], "r");
  } else if (argc == 1) {
    interactive = true;
    fp = stdin;
  } else {
    return 1;
  }

  char* line = NULL;
  size_t length = 0;
  int old_errno = errno;

  while (getline(&line, &length, fp) != -1) {
    printf("%lu\n", length);
  }

  if (errno != old_errno) {
    perror(PROGRAM_NAME);
    free(line);
    return 1;
  }

  free(line);

  return 0;
}
