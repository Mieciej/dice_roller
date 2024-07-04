#include "defs.h"
#include "operator.h"
#include "evaluation.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

int evaluate_rpn(const char rpn[][MAX_TOKEN_LENGTH], size_t len) {
  int number_stack[MAX_NUMBER_OF_TOKENS];
  int stack_size = 0, a, b;
  for (size_t i = 0; i < len; i++) {
    if (is_operator(rpn[i][0])) {
      b = number_stack[--stack_size];
      a = number_stack[--stack_size];
      switch (rpn[i][0]) {
      case '*':
        number_stack[stack_size++] = a * b;
        break;
      case '/':
        number_stack[stack_size++] = a / b;
        break;
      case '-':
        number_stack[stack_size++] = a - b;
        break;
      case '+':
        number_stack[stack_size++] = a + b;
        break;
      default:
        assert("Incorrect operator while processing RPN");
      }
    } else {
      number_stack[stack_size++] = atoi(rpn[i]);
    }
  }
  assert(stack_size == 1 && "Incorrect rpn solution");
  return number_stack[0];
}

void shunting_yard(const char input_stack[][MAX_TOKEN_LENGTH],
                   size_t input_size, char output_stack[][MAX_TOKEN_LENGTH],
                   size_t *output_size) {

  assert(*output_size == 0);
  char operator_stack[MAX_NUMBER_OF_TOKENS];
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
