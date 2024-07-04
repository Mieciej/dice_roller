#include "operator.h"
#include <assert.h>
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
