#include "dice.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void fail(const char *message) {
  fprintf(stderr, "%s\n", message);
  exit(EXIT_FAILURE);
}

unsigned int token_roll(char *token) {

  char *d = strchr(token, 'd');
  if (d == NULL) {
    fail("Incorrect roll syntax. Use \'d\' to specify number of dice sides");
  }
  size_t end = strlen(token);
  if (token[end - 1] == 'd') {
    fail("Incorrect roll syntax");
  }
  *d = '\0';
  long long nRolls = atol(token);
  nRolls = nRolls > 0 ? nRolls : 1;
  long long nSides = atol(d + 1);
  nSides = nSides > 0 ? nSides : 1;
  *d = 'd';
  return roll_dice(NULL, nRolls, nSides);
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fail("Too few arguments");
  }
  unsigned int result = token_roll(argv[1]);
  printf("%u\n", result);
  return EXIT_SUCCESS;
}
