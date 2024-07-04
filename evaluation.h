#ifndef INCLUDE_DICE_ROLLER_RPN_H_
#define INCLUDE_DICE_ROLLER_RPN_H_
#include "defs.h"
#include <stdlib.h>
int evaluate_rpn(const char rpn[][MAX_TOKEN_LENGTH], size_t len);
void shunting_yard(const char input_stack[][MAX_TOKEN_LENGTH],
                   size_t input_size, char output_stack[][MAX_TOKEN_LENGTH],
                   size_t *output_size);
#endif // INCLUDE_DICE-ROLLER_RPN_H_
