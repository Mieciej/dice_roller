#include "dice.hpp"
#include <random>
#include <vector>

std::default_random_engine DiceRoller::u = {};
std::random_device DiceRoller::rd = {};
std::uniform_int_distribution<> DiceRoller::d = {};
std::default_random_engine &DiceRoller::global_urng() { return DiceRoller::u; }

void DiceRoller::randomize(){
  global_urng().seed(rd());
}

std::vector<int> DiceRoller::roll(int n_dice, int n_sides){
  randomize();
  using param_t = decltype(d)::param_type;
  param_t p{1,n_sides};
  std::vector<int> ret{};
  for (size_t i = 0; i < n_dice; i++) {
    ret.push_back(d(global_urng(),p)); 
  }
  return ret;
}
