#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define PROGRAM_NAME "shell"

#define DELIM " \n"

int main(void) {
  bool running = true;
  size_t length;
  char *line = NULL, *line_copy = NULL, *token = NULL;
  int argc = 0;
  char **argv = NULL;

  while (running) {
    printf("$ ");

    if (getline(&line, &length, stdin) == -1)
      goto error;

    line_copy = strdup(line);

    token = strtok(line, DELIM);

    while (token) {
      token = strtok(NULL, DELIM);
      argc++;
    }

    argv = malloc(sizeof(token) * (argc + 1));

    argc = 0;

    token = strtok(line_copy, DELIM);

    int i = 0;

    for (; token; i++) {
      argv[i] = token;

      token = strtok(NULL, DELIM);
    }

    argv[i] = NULL;

    pid_t child = fork();

    if (child == 0) {
      if (execvp(argv[0], argv) == -1) {
        perror(PROGRAM_NAME);
      }
    } else if (child == -1) {
      perror(PROGRAM_NAME);
    } else {
      int status;
      waitpid(child, &status, 0);
      printf("(last status: %d)", status);
    }

    free(argv);
    argv = NULL;

    free(line_copy);
    line_copy = NULL;
  }

  free(line);

  return 0;

error:
  free(line);
  return 1;
}
