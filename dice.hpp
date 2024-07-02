#include <random>
#include <vector>
#ifndef INCLUDE_DICE_ROLLER_DICE_HPP_
#define INCLUDE_DICE_ROLLER_DICE_HPP_

class DiceRoller{
private:
  static std::default_random_engine u;
  static std::random_device rd;
  static std::uniform_int_distribution<> d;
  std::default_random_engine &global_urng();
  void randomize();
public:
  std::vector<int> roll(int n_dice, int n_sides);
};

#endif  // INCLUDE_DICE_ROLLER_DICE_HPP_
