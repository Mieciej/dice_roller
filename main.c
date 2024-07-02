#include "dice.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void fail(const char *message) {
  fprintf(stderr, "%s\n", message);
  exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fail("Too few arguments");
  }
  char *d = strchr(argv[1], 'd');
  if (d == NULL) {
    fail("Incorrect roll syntax. Use \'d\' to specify number of dice sides");
  }
  size_t end = strlen(argv[1]);
  if (argv[1][end - 1] == 'd') {
    fail("Incorrect roll syntax");
  }
  *d = '\0';
  long long nRolls = atol(argv[1]);
  nRolls = nRolls > 0 ? nRolls : 1;
  long long nSides = atol(d + 1);
  nSides = nSides > 0 ? nSides : 1;
  unsigned int result = roll_dice(NULL, nRolls, nSides);
  printf("%u\n", result);
  return EXIT_SUCCESS;
}
