#include "dice.hpp"
#include <iostream>
#include <numeric>


int main(int argc, char *argv[]) { 
  DiceRoller dice;
  unsigned int n_rolls;
  unsigned int n_sides;
  std::cout << "N: ";
  std::cin >> n_rolls;
  std::cout << "d: ";
  std::cin >> n_sides;
  auto v = dice.roll(n_rolls, n_sides);
  for(auto var : v) {
    std::cout << var << std::endl;
  }
  std::cout << "Total: " <<std::accumulate(v.begin(),v.end(),0) << std::endl;
  return 0;
}
