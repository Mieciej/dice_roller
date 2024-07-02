#include "dice.h"
#include <stdlib.h>
#include <sys/random.h>
unsigned int roll_dice(unsigned int *results, size_t numberDice,
              unsigned int numberSides) {

  
  unsigned int total = 0;
  for (size_t i = 0; i < numberDice; i++) {
    unsigned int result; 
    getrandom(&result, sizeof(unsigned int), 0);
    result = result%numberSides + 1;
    total +=result;
    if (results != NULL) {
      results[i] = result;
    }
  }
  return total;
}
