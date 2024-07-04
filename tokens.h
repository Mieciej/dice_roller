#ifndef INCLUDE_DICE_ROLLER_TOKENS_H_
#define INCLUDE_DICE_ROLLER_TOKENS_H_
#include "defs.h"
#include <stdlib.h>
unsigned int token_roll(const char *token_source);
void tokenize(const char *source_equation, char stack[][MAX_TOKEN_LENGTH],
              size_t *stack_size);
void parse_roll_tokens(char stack[][MAX_TOKEN_LENGTH], size_t stack_size);

#endif // INCLUDE_DICE-ROLLER_TOKENS_H_
