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
  assert(token!=NULL&&"Buy more RAM");
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

void tokenize(const char *source_equation, char stack[][MAX_TOKEN_LENGTH],
              size_t *stack_size) {
  size_t len = strlen(source_equation);
  char *equation = malloc(sizeof(char) * (len + 1));
  strcpy(equation, source_equation);
  char *token = equation;
  for (size_t i = 0; i < len + 1; i++) {
    if (equation[i] == '+' || equation[i] == '-' || equation[i] == '*' ||
        equation[i] == '/' || equation[i] == '\0' || equation[i] == ' ') {
      char op = equation[i];
      equation[i] = '\0';
      if (&equation[i] - token > 0) {
        strcpy(stack[*stack_size], token);
        *stack_size = *stack_size + 1;
      }
      token = &equation[i] + 1;
      if (op != '\0' && op != ' ') {
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
    if(d!=NULL) {
      unsigned int result = token_roll(stack[i]);
      sprintf(stack[i],"%u",result);
    }
  }
}

typedef struct node {
  int value;
  char is_character;
  struct node *next;
} node_t;

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fail("Too few arguments");
  }
  char token_stack[1024][MAX_TOKEN_LENGTH];
  size_t token_stack_size = 0;
  tokenize(argv[1], token_stack, &token_stack_size);
  for (size_t i = 0; i < token_stack_size; i++) {
    printf("%s\n", token_stack[i]);
  }
  printf("\n");
  parse_roll_tokens(token_stack,token_stack_size);
  for (size_t i = 0; i < token_stack_size; i++) {
    printf("%s\n", token_stack[i]);
  }
  return EXIT_SUCCESS;
}
