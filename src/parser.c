#include <stdbool.h>
#include <string.h>

static const char* DELIM = " \n";
static const size_t DELIM_LEN = 2;

char *strtok_x(char *str, char **saveptr) {
  if (str == NULL) {
    str = *saveptr;
  }
  
  size_t length = strlen(str);
  bool quoted = false;

  for (size_t i = 0; i < length; i++) {
    if (str[i] == '\"')
      quoted = !quoted;

    if (quoted)
      continue;

    for (size_t j = 0; j < DELIM_LEN; j++) {
      if (str[i] == DELIM[j]) {
        str[i] = 0;
        *saveptr = str + i + 1;
        return str;
      }
    }
  }

  return NULL;
}