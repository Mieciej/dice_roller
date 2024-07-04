#include "evaluation.h"
#include "tokens.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void fail(const char *message) {
  fprintf(stderr, "%s\n", message);
  exit(EXIT_FAILURE);
}



int main(int argc, char *argv[]) {
  if (argc < 2) {
    fail("Too few arguments");
  }
  char token_stack[MAX_NUMBER_OF_TOKENS][MAX_TOKEN_LENGTH];
  size_t token_stack_size = 0;
  tokenize(argv[1], token_stack, &token_stack_size);
  for (size_t i = 0; i < token_stack_size; i++) {
    printf("%s\n", token_stack[i]);
  }
  printf("\n");
  parse_roll_tokens(token_stack, token_stack_size);
  for (size_t i = 0; i < token_stack_size; i++) {
    printf("%s\n", token_stack[i]);
  }
  printf("\n");
  char rpn[MAX_NUMBER_OF_TOKENS][MAX_TOKEN_LENGTH];
  size_t rpn_size = 0;
  shunting_yard(token_stack, token_stack_size, rpn, &rpn_size);
  for (size_t i = 0; i < rpn_size; i++) {
    printf("%s\n", rpn[i]);
  }
  printf("\n");
  int result =evaluate_rpn(rpn, rpn_size);
  printf("%d\n",result);
  return EXIT_SUCCESS;
}
