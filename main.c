#include "dice.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_TOKEN_LENGTH 64
void fail(const char *message) {
  fprintf(stderr, "%s\n", message);
  exit(EXIT_FAILURE);
}

unsigned int token_roll(const char *token_source) {

  size_t len = strlen(token_source);
  char *token = malloc(sizeof(char) * len + 1);
  assert(token != NULL && "Buy more RAM");
  strcpy(token, token_source);
  char *d = strchr(token, 'd');
  assert(d != NULL &&
         "Incorrect roll syntax. Use \'d\' to specify number of dice sides");
  size_t end = strlen(token);
  assert(token[end - 1] != 'd' && "Incorrect roll syntax");
  *d = '\0';
  long long nRolls = atol(token);
  nRolls = nRolls > 0 ? nRolls : 1;
  long long nSides = atol(d + 1);
  nSides = nSides > 0 ? nSides : 1;
  free(token);
  return roll_dice(NULL, nRolls, nSides);
}

unsigned char is_operator(char op) {
  return op == '+' || op == '-' || op == '*' || op == '/';
}
unsigned char operator_precedence(char op) {
  switch (op) {
  case '+':
    return 2;
    break;
  case '-':
    return 2;
    break;
  case '*':
    return 3;
    break;
  case '/':
    return 3;
    break;
  default:
    assert("WRONG OPERATOR");
  }
  return -1;
}

void tokenize(const char *source_equation, char stack[][MAX_TOKEN_LENGTH],
              size_t *stack_size) {
  size_t len = strlen(source_equation);
  char *equation = malloc(sizeof(char) * (len + 1));
  strcpy(equation, source_equation);
  char *token = equation;
  for (size_t i = 0; i < len + 1; i++) {
    if (is_operator(equation[i]) || equation[i] == '\0' || equation[i] == ' ') {
      char op = equation[i];
      equation[i] = '\0';
      if (&equation[i] - token > 0) {
        strcpy(stack[*stack_size], token);
        *stack_size = *stack_size + 1;
      }
      token = &equation[i] + 1;
      if (is_operator(op)) {
        stack[*stack_size][0] = op;
        stack[*stack_size][1] = '\0';
        *stack_size = *stack_size + 1;
      }
    }
  }
  free(equation);
}

void parse_roll_tokens(char stack[][MAX_TOKEN_LENGTH], size_t stack_size) {
  for (size_t i = 0; i < stack_size; i++) {
    char *d = strchr(stack[i], 'd');
    if (d != NULL) {
      unsigned int result = token_roll(stack[i]);
      sprintf(stack[i], "%u", result);
    }
  }
}
void shunting_yard(const char input_stack[][MAX_TOKEN_LENGTH],
                   size_t input_size, char output_stack[][MAX_TOKEN_LENGTH],
                   size_t *output_size) {

  assert(*output_size == 0);
  char operator_stack[256];
  size_t operator_stack_size = 0;
  for (size_t i = 0; i < input_size; i++) {
    if (is_operator(input_stack[i][0])) {
      while (operator_stack_size > 0 &&
             operator_precedence(operator_stack[operator_stack_size - 1]) >=
                                 operator_precedence(input_stack[i][0])) {

        char op[2];
        op[0] = operator_stack[--operator_stack_size];
        op[1] = '\0';
        strcpy(output_stack[*output_size], op);
        *output_size = *output_size + 1;
      }
      operator_stack[operator_stack_size++] = input_stack[i][0];
    } else {
      strcpy(output_stack[*output_size], input_stack[i]);
      *output_size = *output_size + 1;
    }
  }
  for (int i = operator_stack_size - 1; i >= 0; i--) {
    char op[2];
    op[0] = operator_stack[i];
    op[1] = '\0';
    strcpy(output_stack[*output_size], op);
    *output_size = *output_size + 1;
  }
}


int main(int argc, char *argv[]) {
  if (argc < 2) {
    fail("Too few arguments");
  }
  char token_stack[256][MAX_TOKEN_LENGTH];
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
  char rpn[256][MAX_TOKEN_LENGTH];
  size_t rpn_size = 0;
  shunting_yard(token_stack, token_stack_size,rpn, &rpn_size);
  for (size_t i = 0; i < rpn_size; i++) {
    printf("%s\n", rpn[i]);
  }
  return EXIT_SUCCESS;
}
